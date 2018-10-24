/*
 * AD5142.c
 *
 *  Created on: Oct 12, 2018
 *      Author: 19546
 */
#include "F28x_Project.h"
#include "Spi.h"

#define Write_2_RDAC (1<<4)  //Address bit that sets AD5142 to write to RDAC mode

//Sets TDC1 Threshold Voltage by inputing a value from 0 to 255
void TDC1_Threshold_Voltage(Uint16 value)
{
    Uint16 Control_Address = (0<<0);        //Selects RDAC1
    Control_Address |= Write_2_RDAC;        //bit OR's write mode address bit
    Control_Address = (Control_Address<<8); //bit shifts 8 to make space for byte of data

    SPI_RW_POT1_Full(Control_Address + value);  //Sends Control & Address & Data to POT
}

//Sets TDC2 Threshold Voltage by inputing a value from 0 to 255
void TDC2_Threshold_Voltage(Uint16 value)
{
    Uint16 Control_Address = (0<<1);        //Selects RDAC2
    Control_Address |= Write_2_RDAC;        //bit OR's write mode address bit
    Control_Address = (Control_Address<<8); //bit shifts 8 to make space for byte of data

    SPI_RW_POT1_Full(Control_Address + value);  //Sends Control & Address & Data to POT
}

//Sets TDC3 Threshold Voltage by inputing a value from 0 to 255
void TDC3_Threshold_Voltage(Uint16 value)
{
    Uint16 Control_Address = (0<<0);        //Selects RDAC1
    Control_Address |= Write_2_RDAC;        //bit OR's write mode address bit
    Control_Address = (Control_Address<<8); //bit shifts 8 to make space for byte of data

    SPI_RW_POT2_Full(Control_Address + value);  //Sends Control & Address & Data to POT
}

//Sets TDC4 Threshold Voltage by inputing a value from 0 to 255
void TDC4_Threshold_Voltage(Uint16 value)
{
    Uint16 Control_Address = (0<<1);        //Selects RDAC2
    Control_Address |= Write_2_RDAC;        //bit OR's write mode address bit
    Control_Address = (Control_Address<<8); //bit shifts 8 to make space for byte of data

    SPI_RW_POT2_Full(Control_Address + value);  //Sends Control & Address & Data to POT
}
