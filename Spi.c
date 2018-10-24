/*
 * Spi.c
 *
 *  Created on: Oct 9, 2018
 *      Author: 19546
 */

#include "F28x_Project.h"

//  CS:TDC LASER    GPIO124 (LaunchPad #13)
//  CS:Pot1         GPIO125 (LaunchPad #12)
//  CS:Pot2         GPIO29  (LaunchPad #11)
//  CS: TDC STOP2   GPIO26  (LaunchPad #53)
//  CS:TDC STOP3    GPIO77   (LaunchPad #FFC13)


void SPIA_Setup(void)
{
    //  SOMI:           GPIO59  (LaunchPad #14)
    //  SIMO:           GPIO58  (LaunchPad #15)
    //  SPI CLK:        GPIO60  (LaunchPad #7 )
    //  CS:TDC LASER    GPIO124 (LaunchPad #13)
    //  CS:Pot1         GPIO125 (LaunchPad #12)
    //  CS:Pot2         GPIO29  (LaunchPad #11)

    EALLOW;                             //Allows you to write to a protected registers
    CpuSysRegs.PCLKCR8.bit.SPI_A = 1;   //Turn on SPI_A clock

    /*=========================GPIO SETUP=========================================*/

    // Enable internal pull-up for the selected pins
    //
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;  // Enable pull-up on GPIO58 (SPISIMOA)
    GpioCtrlRegs.GPBPUD.bit.GPIO59 = 0;  // Enable pull-up on GPIO59 (SPISOMIA)
    GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0;  // Enable pull-up on GPIO60 (SPICLKA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO19 = 0;  // Enable pull-up on GPIO19 (SPISTEA)

    //
    // Set qualification for selected pins to asynch only
    //
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3; // Asynch input GPIO58 (SPISIMOA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO59 = 3; // Asynch input GPIO59 (SPISOMIA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO60 = 3; // Asynch input GPIO60 (SPICLKA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

    //
    //Configure SPI-A pins using GPIO regs
    //
    // This specifies which of the possible GPIO pins will be SPI functional pins.
    // Consult Table 7-7 in "TMS320F2837xD Technical Reference Manual" (Literature Number: SPRUHM8G)
    // for details.
    //
    GpioCtrlRegs.GPBMUX2.bit.GPIO58     =   0b11; // Configure GPIO58 as SPISIMOA
    GpioCtrlRegs.GPBGMUX2.bit.GPIO58    =   0b11;
    GpioCtrlRegs.GPBMUX2.bit.GPIO59     =   0b11; // Configure GPIO59 as SPISOMIA
    GpioCtrlRegs.GPBGMUX2.bit.GPIO59    =   0b11;
    GpioCtrlRegs.GPBMUX2.bit.GPIO60     =   0b11; // Configure GPIO60 as SPICLKA
    GpioCtrlRegs.GPBGMUX2.bit.GPIO60    =   0b11;
    //GpioCtrlRegs.GPBMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

    EDIS;   //Stops you from writing to a protected registers


    /*=========================SPI REG SETUP=========================================*/
    // For details consult with chapter 18 from "TMS320F2837xD Technical Reference Manual"
    // (Literature Number: SPRUHM8G)

    SpiaRegs.SPICCR.bit.SPISWRESET  =   0;  // clear software reset bit
    SpiaRegs.SPICCR.bit.CLKPOLARITY =   0;  // Set clock polarity
    SpiaRegs.SPICCR.bit.HS_MODE     =   0;  // High speed mode disabled
    SpiaRegs.SPICCR.bit.SPILBK      =   0;  // SPI loopback mode disabled
    SpiaRegs.SPICCR.bit.SPICHAR     =   0xF;// 16 bit word



    SpiaRegs.SPICTL.bit.OVERRUNINTENA   =   0;  // Receiver overrun interrupt disabled
    SpiaRegs.SPICTL.bit.CLK_PHASE       =   1;  // Dependent on CLK Polarity
    SpiaRegs.SPICTL.bit.MASTER_SLAVE    =   1;  // SPI Master mode
    SpiaRegs.SPICTL.bit.TALK            =   1;  // Enables Transmission for 4 wire SPI
    SpiaRegs.SPICTL.bit.SPIINTENA       =   0;  // Disables interrupt for TX/RX

    SpiaRegs.SPIBRR.bit.SPI_BIT_RATE    =   0;  // SPI CLk = LSPCLK/4

    SpiaRegs.SPICCR.bit.SPISWRESET      =   1;  // Enable SPI

    /*============================Chip Select SETUP==================================*/
    // Set up all the different GPIO pins you will be using for CS (Chip Select)
    // on the SpiA peripheral

    EALLOW; //Allows you to write to a protected registers

    //  CS:TDC LASER    GPIO124 (LaunchPad #13)
    //  CS:Pot1         GPIO125 (LaunchPad #12)
    //  CS:Pot2         GPIO29  (LaunchPad #11)
    GpioDataRegs.GPDDAT.bit.GPIO124 =   1;  //Set default value as HIGH
    GpioCtrlRegs.GPDDIR.bit.GPIO124 =   1;  //Sets sets GPIO 124 as OUT

    GpioDataRegs.GPDDAT.bit.GPIO125 =   1;  //Set default value as HIGH
    GpioCtrlRegs.GPDDIR.bit.GPIO125 =   1;  //Sets sets GPIO 125 as OUT

    GpioDataRegs.GPADAT.bit.GPIO29 =   1;  //Set default value as HIGH
    GpioCtrlRegs.GPADIR.bit.GPIO29 =   1;  //Sets sets GPIO 29 as OUT

    EDIS;   //Stops you from writing to a protected registers
}

void SPIB_Setup(void)
{
    //  SOMI:           GPIO64  (LaunchPad #54)
    //  SIMO:           GPIO63  (LaunchPad #55)
    //  SPI CLK:        GPIO65  (LaunchPad #47)
    //  CS: TDC STOP2   GPIO26  (LaunchPad #53)

    EALLOW;                             //Allows you to write to a protected registers
    CpuSysRegs.PCLKCR8.bit.SPI_B = 1;   //Turn on SPI_A clock

    /*=========================GPIO SETUP=========================================*/

    // Enable internal pull-up for the selected pins
    //
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;  // Enable pull-up on GPIO63 (SPISIMOA)
    GpioCtrlRegs.GPCPUD.bit.GPIO64 = 0;  // Enable pull-up on GPIO64 (SPISOMIA)
    GpioCtrlRegs.GPCPUD.bit.GPIO65 = 0;  // Enable pull-up on GPIO65 (SPICLKA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO19 = 0;  // Enable pull-up on GPIO19 (SPISTEA)

    //
    // Set qualification for selected pins to asynch only
    //
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPBQSEL2.bit.GPIO63 = 3; // Asynch input GPIO63 (SPISIMOA)
    GpioCtrlRegs.GPCQSEL1.bit.GPIO64 = 3; // Asynch input GPIO64 (SPISOMIA)
    GpioCtrlRegs.GPCQSEL1.bit.GPIO65 = 3; // Asynch input GPIO65 (SPICLKA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

    //
    //Configure SPI-A pins using GPIO regs
    //
    // This specifies which of the possible GPIO pins will be SPI functional pins.
    // Consult Table 7-7 in "TMS320F2837xD Technical Reference Manual" (Literature Number: SPRUHM8G)
    // for details.
    //
    GpioCtrlRegs.GPBMUX2.bit.GPIO63     =   0b11; // Configure GPIO63 as SPISIMOA
    GpioCtrlRegs.GPBGMUX2.bit.GPIO63    =   0b11;
    GpioCtrlRegs.GPCMUX1.bit.GPIO64     =   0b11; // Configure GPIO64 as SPISOMIA
    GpioCtrlRegs.GPCGMUX1.bit.GPIO64    =   0b11;
    GpioCtrlRegs.GPCMUX1.bit.GPIO65     =   0b11; // Configure GPIO65 as SPICLKA
    GpioCtrlRegs.GPCGMUX1.bit.GPIO65    =   0b11;
    //GpioCtrlRegs.GPBMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

    EDIS;   //Stops you from writing to a protected registers


    /*=========================SPI REG SETUP=========================================*/
    // For details consult with chapter 18 from "TMS320F2837xD Technical Reference Manual"
    // (Literature Number: SPRUHM8G)

    SpibRegs.SPICCR.bit.SPISWRESET  =   0;  // clear software reset bit
    SpibRegs.SPICCR.bit.CLKPOLARITY =   0;  // Set clock polarity
    SpibRegs.SPICCR.bit.HS_MODE     =   0;  // High speed mode disabled
    SpibRegs.SPICCR.bit.SPILBK      =   0;  // SPI loopback mode disabled
    SpibRegs.SPICCR.bit.SPICHAR     =   0xF;// 16 bit word



    SpibRegs.SPICTL.bit.OVERRUNINTENA   =   0;  // Receiver overrun interrupt disabled
    SpibRegs.SPICTL.bit.CLK_PHASE       =   1;  // Dependent on CLK Polarity
    SpibRegs.SPICTL.bit.MASTER_SLAVE    =   1;  // SPI Master mode
    SpibRegs.SPICTL.bit.TALK            =   1;  // Enables Transmission for 4 wire SPI
    SpibRegs.SPICTL.bit.SPIINTENA       =   0;  // Disables interrupt for TX/RX

    SpibRegs.SPIBRR.bit.SPI_BIT_RATE    =   0;  // SPI CLk = LSPCLK/4

    SpibRegs.SPICCR.bit.SPISWRESET      =   1;  // Enable SPI

    /*============================Chip Select SETUP==================================*/
    // Set up all the different GPIO pins you will be using for CS (Chip Select)
    // on the SpiA peripheral

    EALLOW; //Allows you to write to a protected registers

    // Sets up CS at GPIO 26
    GpioDataRegs.GPADAT.bit.GPIO26 =   1;  //Set default value as HIGH
    GpioCtrlRegs.GPADIR.bit.GPIO26 =   1;  //Sets sets GPIO 26 as OUT

    EDIS;   //Stops you from writing to a protected registers
}

void SPIC_Setup(void)
{
    //  SOMI:           GPIO101  (LaunchPad #FFC10)
    //  SIMO:           GPIO100  (LaunchPad #FFC11)
    //  SPI CLK:        GPIO102  (LaunchPad #FFC12)
    //  CS:TDC STOP3    GPIO77   (LaunchPad #FFC13)

    EALLOW;                             //Allows you to write to a protected registers
    CpuSysRegs.PCLKCR8.bit.SPI_C = 1;   //Turn on SPI_C clock

    /*=========================GPIO SETUP=========================================*/

    // Enable internal pull-up for the selected pins
    //
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPDPUD.bit.GPIO100 = 0;  // Enable pull-up on GPIO100 (SPISIMOA)
    GpioCtrlRegs.GPDPUD.bit.GPIO101 = 0;  // Enable pull-up on GPIO101 (SPISOMIA)
    GpioCtrlRegs.GPDPUD.bit.GPIO102 = 0;  // Enable pull-up on GPIO102 (SPICLKA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO19 = 0;  // Enable pull-up on GPIO19 (SPISTEA)

    //
    // Set qualification for selected pins to asynch only
    //
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPDQSEL1.bit.GPIO100 = 3; // Asynch input GPIO100 (SPISIMOA)
    GpioCtrlRegs.GPDQSEL1.bit.GPIO101 = 3; // Asynch input GPIO101 (SPISOMIA)
    GpioCtrlRegs.GPDQSEL1.bit.GPIO102 = 3; // Asynch input GPIO102 (SPICLKA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

    //
    //Configure SPI-C pins using GPIO regs
    //
    // This specifies which of the possible GPIO pins will be SPI functional pins.
    // Consult Table 7-7 in "TMS320F2837xD Technical Reference Manual" (Literature Number: SPRUHM8G)
    // for details.
    //
    GpioCtrlRegs.GPDMUX1.bit.GPIO100     =   0b10; // Configure GPIO100 as SPISIMOA
    GpioCtrlRegs.GPDGMUX1.bit.GPIO100    =   0b01;
    GpioCtrlRegs.GPDMUX1.bit.GPIO101     =   0b10; // Configure GPIO101 as SPISOMIA
    GpioCtrlRegs.GPDGMUX1.bit.GPIO101    =   0b01;
    GpioCtrlRegs.GPDMUX1.bit.GPIO102     =   0b10; // Configure GPIO102 as SPICLKA
    GpioCtrlRegs.GPDGMUX1.bit.GPIO102    =   0b01;
    //GpioCtrlRegs.GPBMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

    EDIS;   //Stops you from writing to a protected registers


    /*=========================SPI REG SETUP=========================================*/
    // For details consult with chapter 18 from "TMS320F2837xD Technical Reference Manual"
    // (Literature Number: SPRUHM8G)

    SpicRegs.SPICCR.bit.SPISWRESET  =   0;  // clear software reset bit
    SpicRegs.SPICCR.bit.CLKPOLARITY =   0;  // Set clock polarity
    SpicRegs.SPICCR.bit.HS_MODE     =   0;  // High speed mode disabled
    SpicRegs.SPICCR.bit.SPILBK      =   0;  // SPI loopback mode disabled
    SpicRegs.SPICCR.bit.SPICHAR     =   0xF;// 16 bit word



    SpicRegs.SPICTL.bit.OVERRUNINTENA   =   0;  // Receiver overrun interrupt disabled
    SpicRegs.SPICTL.bit.CLK_PHASE       =   1;  // Dependent on CLK Polarity
    SpicRegs.SPICTL.bit.MASTER_SLAVE    =   1;  // SPI Master mode
    SpicRegs.SPICTL.bit.TALK            =   1;  // Enables Transmission for 4 wire SPI
    SpicRegs.SPICTL.bit.SPIINTENA       =   0;  // Disables interrupt for TX/RX

    SpicRegs.SPIBRR.bit.SPI_BIT_RATE    =   0;  // SPI CLk = LSPCLK/4

    SpicRegs.SPICCR.bit.SPISWRESET      =   1;  // Enable SPI

    /*============================Chip Select SETUP==================================*/
    // Set up all the different GPIO pins you will be using for CS (Chip Select)
    // on the SpiA peripheral

    EALLOW; //Allows you to write to a protected registers

    // Sets up CS at GPIO 77
    GpioDataRegs.GPCDAT.bit.GPIO77 =   1;  //Set default value as HIGH
    GpioCtrlRegs.GPCDIR.bit.GPIO77 =   1;  //Sets sets GPIO 77 as OUT

    EDIS;   //Stops you from writing to a protected registers
}

void SPI_Setup(void)
{
    SPIA_Setup();
    SPIB_Setup();
    SPIC_Setup();
}

/***********************POT1 SPI Functions**********************/
//Starts SPI transaction
void SPI_POT1_Start(void)
{
    // CS is assumed to be GPIO125

    GpioDataRegs.GPDDAT.bit.GPIO125 =   0;      //Set CS LOW
}

//Ends SPI transaction
void SPI_POT1_End(void)
{
    // CS is assumed to be GPIO125

    GpioDataRegs.GPDDAT.bit.GPIO125 =   1;      //Set CS HIGH
}

//16bits of SPI transaction
Uint16 SPI_RW_POT1(Uint16 data)
{
    // This function reads and writes data over SPI

    EALLOW;
    SpiaRegs.SPICCR.bit.SPISWRESET      =   0;  // Disable SPI

    SpiaRegs.SPICCR.bit.CLKPOLARITY     =   0;  // Set clock polarity
    SpiaRegs.SPICTL.bit.CLK_PHASE       =   0;  // Dependent on CLK Polarity

    SpiaRegs.SPICCR.bit.SPISWRESET      =   1;  // Enable SPI
    EDIS;

    SpiaRegs.SPITXBUF   =   data;               //Output Data
    while(0 == SpiaRegs.SPISTS.bit.INT_FLAG);   //Waits until Transmit or Receive complete
    return SpiaRegs.SPIRXBUF;                   //Reads and returns the SPI input DATA
}

//Start to end 16bit SPI Transaction
Uint16 SPI_RW_POT1_Full(Uint16 data)
{
    SPI_POT1_Start();
    data = SPI_RW_POT1(data);
    SPI_POT1_End();
    return data;
}

/***********************POT2 SPI Functions*********************/
//Starts SPI transaction
void SPI_POT2_Start(void)
{
    // CS is assumed to be GPIO29
    GpioDataRegs.GPADAT.bit.GPIO29 =   0;      //Set CS LOW
}

//Ends SPI transaction
void SPI_POT2_End(void)
{
    GpioDataRegs.GPADAT.bit.GPIO29 =   1;      //Set CS HIGH
}

//16bits of SPI transaction
Uint16 SPI_RW_POT2(Uint16 data)
{
    // This function reads and writes data over SPI
    return SPI_RW_POT1(data);
}

//Start to end 16bit SPI Transaction
Uint16 SPI_RW_POT2_Full(Uint16 data)
{
    SPI_POT2_Start();
    data = SPI_RW_POT2(data);
    SPI_POT2_End();
    return data;
}

/***********************TDC1 SPI Functions*********************/
//Starts SPI transaction
void SPI_TDC1_Start(void)
{
    // CS is assumed to be GPIO124
    GpioDataRegs.GPDDAT.bit.GPIO124 =   0;      //Set CS LOW
}

//Ends SPI transaction
void SPI_TDC1_End(void)
{
    GpioDataRegs.GPDDAT.bit.GPIO124 =   1;      //Set CS HIGH
}

//16bits of SPI transaction
Uint16 SPI_RW_TDC1(Uint16 data)
{
    // This function reads and writes data over SPI
    SpiaRegs.SPITXBUF   =   data;               //Output Data
    while(0 == SpiaRegs.SPISTS.bit.INT_FLAG);   //Waits until Transmit or Receive complete
    return SpiaRegs.SPIRXBUF;                   //Reads and returns the SPI input DATA
}

//Start to end 16bit SPI Transaction
Uint16 SPI_RW_TDC1_Full(Uint16 data)
{
    SPI_TDC1_Start();
    data = SPI_RW_TDC1(data);
    SPI_TDC1_End();
    return data;
}

/***********************TDC2 SPI Functions*********************/
//Starts SPI transaction
void SPI_TDC2_Start(void)
{
    // CS is assumed to be GPIO26
    GpioDataRegs.GPADAT.bit.GPIO26 =   0;      //Set CS LOW
}

//Ends SPI transaction
void SPI_TDC2_End(void)
{
    GpioDataRegs.GPADAT.bit.GPIO26 =   1;      //Set CS HIGH
}

//16bits of SPI transaction
Uint16 SPI_RW_TDC2(Uint16 data)
{
    // This function reads and writes data over SPI
    SpibRegs.SPITXBUF   =   data;               //Output Data
    while(0 == SpibRegs.SPISTS.bit.INT_FLAG);   //Waits until Transmit or Receive complete
    return SpibRegs.SPIRXBUF;                   //Reads and returns the SPI input DATA
}

//Start to end 16bit SPI Transaction
Uint16 SPI_RW_TDC2_Full(Uint16 data)
{
    SPI_TDC2_Start();
    data = SPI_RW_TDC2(data);
    SPI_TDC2_End();
    return data;
}

/***********************TDC3 SPI Functions*********************/
//Starts SPI transaction
void SPI_TDC3_Start(void)
{
    // CS is assumed to be GPIO77
    GpioDataRegs.GPCDAT.bit.GPIO77 =   0;      //Set CS LOW
}

//Ends SPI transaction
void SPI_TDC3_End(void)
{
    GpioDataRegs.GPCDAT.bit.GPIO77 =   1;      //Set CS HIGH
}

//16bits of SPI transaction
Uint16 SPI_RW_TDC3(Uint16 data)
{
    // This function reads and writes data over SPI
    SpicRegs.SPITXBUF   =   data;               //Output Data
    while(0 == SpicRegs.SPISTS.bit.INT_FLAG);   //Waits until Transmit or Receive complete
    return SpicRegs.SPIRXBUF;                   //Reads and returns the SPI input DATA
}

//Start to end 16bit SPI Transaction
Uint16 SPI_RW_TDC3_Full(Uint16 data)
{
    SPI_TDC3_Start();
    data = SPI_RW_TDC3(data);
    SPI_TDC3_End();
    return data;
}


/***********************All TDC SPI Functions*******************/
//Starts SPI transaction for ALL TDC
void SPI_TDC_Start(void)
{
    SPI_TDC1_Start();
    SPI_TDC2_Start();
    SPI_TDC3_Start();
}

//Stops SPI transaction for ALL TDC
void SPI_TDC_End(void)
{
    SPI_TDC1_End();
    SPI_TDC2_End();
    SPI_TDC3_End();
}

//16bits of SPI transaction for ALL TDC and returns data in TDC_data array
void SPI_RW_TDC(Uint16 TDC_data1, Uint16 TDC_data2,Uint16 TDC_data3, Uint16* TDC_data)
{
    SpiaRegs.SPITXBUF   =   TDC_data1;               //Output Data SPI A
    SpibRegs.SPITXBUF   =   TDC_data2;               //Output Data SPI B
    SpicRegs.SPITXBUF   =   TDC_data3;               //Output Data SPI C

    //Waits until Transmit or Receive complete
    while(0 == SpiaRegs.SPISTS.bit.INT_FLAG && 0 == SpibRegs.SPISTS.bit.INT_FLAG && 0 == SpicRegs.SPISTS.bit.INT_FLAG);

    //Stores data from all SPI channels in a array
    TDC_data[0] = SpiaRegs.SPIRXBUF;
    TDC_data[1] = SpibRegs.SPIRXBUF;
    TDC_data[2] = SpicRegs.SPIRXBUF;

}
