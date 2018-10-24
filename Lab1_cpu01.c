#include "F28x_Project.h"
#include "Spi.h"
#include "Sci.h"
#include "AD5142.h"
#include "Clk_Settings.h"
#include "TDC7200.h"

/*
void main(void)
{
    //SPI_Setup();
    scia_setup();
    while(1)
    {
        //SPI_RW_TDC1_Full(0xAAAA); // Outputs all 1's
        //SPI_RW_TDC2_Full(0xAAAA); // Outputs a pattern of 1010
        //SPI_RW_TDC3_Full(0xAAAA); // Outputs all 0's
        //TDC1_Threshold_Voltage(100);
        //TDC2_Threshold_Voltage(100);
        //TDC3_Threshold_Voltage(100);
        //TDC4_Threshold_Voltage(100);
        //SPI_RW(0x5555); // Outputs a pattern of 0101
        scia_msg(" ns");
    }
}
*/
void main(void)
{
    //EALLOW;
    //ClkCfgRegs.SYSPLLCTL1.bit.PLLEN =0;
    //EDIS;
    Clk_Setup_IntoSC2();
    scib_setup();
    scia_setup();
    SPI_Setup();


    //SPI_RW_TDC1_Full(((Dont_Increment|TDC_Write|CONFIG2)<<8)|(Cal_Every_20_Per|Three_Stop));

    for(;;)
    {
        SCIB_Send('U');
        SCIA_Send('A');

        //SCIB_Send('U');
        SPI_RW_TDC1(0xAAAA);
        //SCIA_Send('*');
        //SPI_RW_TDC1_Full(((Dont_Increment|Write|CONFIG2)<<8)|(Cal_Every_20_Per|Three_Stop));
        //SPI_RW_TDC1_Full(((Dont_Increment|TDC_Read|CONFIG2)<<8)|(0));
        //DC1_Config1();
        //scia_msg("time of flght= "); //you can send message here
        //float a=9999.999;
        //send_number(a);// you can send number here
        //scia_msg(" ns"); //you can send message here
        //scia_msg("\n"); //you can send message here
    }
}

//
// End of file
//
