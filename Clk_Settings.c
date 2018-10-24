/*
 * Clk_Settings.c
 *
 *  Created on: Oct 14, 2018
 *      Author: 19546
 */
#include "F28x_Project.h"


// Phase-lock-loop output value NOTE:
// 400 MHz >= IntroSC2_CLK_Frequency*(PPL_System_Integer_Multiplier+(PPL_System_Fractional_Multiplier/4)) >= 120 MHz
// NOTE: 194MHz >= PLL_System_CLK_Frequency >= 2MHz

#define PLL_System_Integer_Multiplier       14  //The PLL integer multiplier value      x   (max value of 127)
#define PLL_System_Fractional_Multiplier    0   //The PPL fractional multiplier value  x/4 (max value of 3)
// Example x = 3 -> multiplier_value = 3/4 = 0.75


#define PLL_System_CLK_Divide           8   //The phase-lock-loop system clock divider value   /x  (max value of 126 & Multiple of 2)
#define Low_Speed_Peripheral_CLK_Divide 1   //The low speed peripheral clock divider value     /x  (max value of 14 & Multiple of 2)
#define EMIF2_CLK_Divide                2   //The EMIF2 clock divider value                     /x  (max value of 2 & Multiple of 2)
#define EMIF1_CLK_Divide                2   //The EMIF1 clock divider value                     /x  (max value of 2 & Multiple of 2)
#define EPWM_CLK_Divide                 2   //The EPWM clock divider value                      /x  (max value of 2 & Multiple of 2)     NOTE: must be /2 if 100MHz < PLL_CLK_Fre
#define X_CLK_Output_Divide             8   //The external clock Output clock divider value     /x  (max value of 8 & Multiple of 2)

#define IntroSC2_CLK_Frequency      10000000    //10MHz internal Oscillator frequency (DO NOT CHANGE)

//Sets up the PPL to the desired frequency using IntoSC2 oscillator
void Set_Clk_IntoSC2_PPL(void)
{
    EALLOW;

    //Select the reference clock source (OSCCLK) by writing to CLKSRCCTL1.OSCCLKSRCSEL
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0b00;

    //a.    Bypass the PLL by clearing SYSPLLCTL1[PLLCLKEN].
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;

    //b.    Set the system clock divider to /1 to ensure the fastest PLL configuration by clearing
    //      SYSCLKDIVSEL[ PLLSYSCLKDIV].
    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0;

    //c.    Set the integral and fractional multipliers by simultaneously writing them both to SYSPLLMULT.
    //      This will automatically enable the PLL. Be sure that the product of OSCCLK and the multiplier is in
    //      the range specified in the data manual.
    ClkCfgRegs.SYSPLLMULT.all = (PLL_System_Fractional_Multiplier << 8) + (PLL_System_Integer_Multiplier << 0);

    //d.    Lock the PLL five times (see your device errata for details). This number can be increased
    //      depending on application requirements. A higher number of lock attempts helps to ensure a
    //      successful PLL start
    Uint16 i;
    //Test PLL 10 times
    for(i=0;i<10;i++)
    {
        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0;        //Disables PLL

        //PLL values lost after every PLL disable
        ClkCfgRegs.SYSPLLMULT.all = (PLL_System_Fractional_Multiplier << 8) + (PLL_System_Integer_Multiplier << 0);

        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1;        //Enables PPL
        while(ClkCfgRegs.SYSPLLSTS.bit.LOCKS !=1);  //waits until PLL locks
    }

    //e.    Set the system clock divider one setting higher than the final desired value. For example
    //      ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel + 1. This limits the current increase
    //      when switching to the PLL.
    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV    = (PLL_System_CLK_Divide >> 1) + 1;

    //f.    Set up the watchdog to reset the device. Note that the SCRS[WDOVERRIDE] bit should not be
    //      cleared prior to locking the PLL.

    /*~~~~~~~~~~~~~~~~~~~TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    //g.    Set the SYSDBGCTL[BIT_0] bit. This bit is only reset by a POR reset. If the watchdog has to reset
    //      the device due to an issue with switching to the PLL, this bit can be checked in the reset handler to
    //      determine the reset was caused by a PLL error.
    DevCfgRegs.SYSDBGCTL.bit.BIT_0 = 1;

    //h.    Switch to the PLL as the system clock by setting SYSPLLCTL1[PLLCLKEN].
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;

    //i.    Clear the SYSDBGCTL[BIT_0] bit.
    DevCfgRegs.SYSDBGCTL.bit.BIT_0 = 0;

    //j.    Change the divider to the appropriate value.

    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV    = (PLL_System_CLK_Divide >> 1);             //Sets system PPL clock divide

    //*******************************NOTE***********************//
    // You have to set all the DIV here or else it will they dont go into effect
    // Reason why is unknown and could not find out why in Data-Sheet
    ClkCfgRegs.LOSPCP.bit.LSPCLKDIV             = (Low_Speed_Peripheral_CLK_Divide >> 1);   //Sets low speed peripheral clock divide
    ClkCfgRegs.PERCLKDIVSEL.bit.EMIF1CLKDIV     = (EMIF2_CLK_Divide >> 1);                  //Sets EMIF2 clock divide
    ClkCfgRegs.PERCLKDIVSEL.bit.EMIF2CLKDIV     = (EMIF1_CLK_Divide >> 1);                  //Sets EMIF1 clock divide
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV      = (EPWM_CLK_Divide >> 1);                   //Sets EPWM clock divide
    ClkCfgRegs.XCLKOUTDIVSEL.bit.XCLKOUTDIV     = (X_CLK_Output_Divide >> 1);               //Sets external clock Output clock divide

    //k.    Reconfigure the watchdog as needed for the application.

    /*~~~~~~~~~~~~~~~~~~~TODO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    EDIS;
}

//Sets up PPL to pass through external clock source
void Set_Clk_XTL(void)
{
    EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF       = 0;    //Turns external oscillator ON

    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0b01;  //Select external clock as reference source

    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;         //Bypass the PLL
    EDIS;
}


//Sets up All the clocks using INTOSC2 reference clock
void Clk_Setup_IntoSC2(void)
{
    Set_Clk_IntoSC2_PPL();
}

//Sets up All the clocks using XTL reference clock
void Clk_Setup_XTL(void)
{
    Set_Clk_XTL();
}

//Gives you the system clock frequency in Hz
Uint32 PLL_System_CLK_Frequency(void)
{
    return (IntroSC2_CLK_Frequency*(PLL_System_Integer_Multiplier+(PLL_System_Fractional_Multiplier/4))/PLL_System_CLK_Divide);
}

//Gives you the Low_Speed peripheral clock frequency in Hz
Uint32 Low_Speed_Peripheral_CLK_Frequency(void)
{
    return (PLL_System_CLK_Frequency()/Low_Speed_Peripheral_CLK_Divide);
}
