/*
 * TDC7200.c
 *
 *  Created on: Oct 10, 2018
 *      Author: 19546
 */

#include "F28x_Project.h"
#include "Spi.h"

/**************Address************************/

#define CONFIG1                 0x00
#define CONFIG2                 0x01
#define INT_STATUS              0x02
#define INT_MASK                0x03
#define COARSE_CNTR_OVF_H       0x04
#define COARSE_CNTR_OVF_L       0x05
#define CLOCK_CNTR_OVF_H        0x06
#define CLOCK_CNTR_OVF_L        0x07
#define CLOCK_CNTR_STOP_MASK_H  0x08
#define CLOCK_CNTR_STOP_MASK_L  0x09
#define TIME1                   0x10
#define CLOCK_COUNT1            0x11
#define TIME2                   0x12
#define CLOCK_COUNT2            0x13
#define TIME3                   0x14
#define CLOCK_COUNT3            0x15
#define TIME4                   0x16
#define CLOCK_COUNT4            0x17
#define TIME5                   0x18
#define CLOCK_COUNT5            0x19
#define TIME6                   0x1A
#define CALIBRATION1            0X1B
#define CALIBRATION2            0X1C

/**************Address Options*****************/
#define Auto_Increment          (1<<7)
#define Dont_Increment          (0<<7)
#define TDC_Read                    (0<<6)
#define TDC_Write                   (1<<6)

/*********************CONFIG1*****************/
//FORCE_CAL
#define Calib_Dis       (0<<7)
#define Calib_En        (1<<7)
//PARITY_EN
#define Parity_Dis      (0<<6)
#define Parity_En       (0<<6)
//TRIGG_EDGE
#define Trig_Rising_Edge    (0<<5)
#define Trig_Falling_Edge   (1<<5)
//STOP_EDGE
#define Stop_Rising_Edge    (0<<4)
#define Stop_Falling_Edge   (1<<4)
//START_EDGE
#define Start_Rising_Edge   (0<<3)
#define Start_Falling_Edge  (1<<3)
//MEAS_MODE
#define Mode1       (0b00<<1)
#define Mode2       (0b01<<1)
//START_MEAS
#define Start_Meas  (1<<0)
/*********************CONFIG2*****************/
//CALIBRATION2_PERIODS
#define Cal_Every_2_Per  (0b00<<6)
#define Cal_Every_10_Per (0b01<<6)
#define Cal_Every_20_Per (0b10<<6)
#define Cal_Every_40_Per (0b11<<6)
//AVG_CYCLES
#define No_Multi_Cycle_Avg (0b000<<3)
//NUM_STOP
#define Single_Stop (0b000<<0)
#define Two_Stop    (0b001<<0)
#define Three_Stop  (0b010<<0)
#define Four_Stop   (0b011<<0)
#define Five_Stop   (0b100<<0)

/********************INT_MASK*****************/
//CLOCK_CNTR_OVF_MASK
#define Counter_Overflow_Inter_Dis  (0<<2)
#define Counter_Overflow_Inter_En   (1<<2)
//COARSE_CNTR_OVF_MASK
#define Coarse_Overflow_Inter_Dis   (0<<1)
#define Coarse_Overflow_Inter_En    (1<<1)
//NEW_MEAS_MASK
#define New_Measurement_Inter_Dis   (0<<0)
#define New_Measurement_Inter_En    (1<<0)


//=====================TDC1==================//
void TDC1_Config1(void)
{
    Uint16 address  =   CONFIG1;                    //Address of register
    address         |=  TDC_Write;
    address         |=  Dont_Increment;

    Uint16 settings =   Calib_Dis;                  //Settings of register
    settings        |=  Parity_Dis;
    settings        |=  Trig_Rising_Edge;
    settings        |=  Stop_Falling_Edge;
    settings        |=  Mode2;

    SPI_RW_TDC1_Full((address << 8)|(settings));    //Send data over SPI

}

void TDC1_Config2(void)
{
    Uint16 address  =   CONFIG2;        //Address of register
    address         |=  TDC_Write;
    address         |=  Dont_Increment;

    Uint16 settings =   0b0;            //Settings of register

    SPI_RW_TDC1_Full((address << 8)|(settings));    //Send data over SPI
}

void TDC1_Mask(void)
{
    Uint16 address  =   INT_MASK;        //Address of register
    address         |=  TDC_Write;
    address         |=  Dont_Increment;

    Uint16 settings =   0b0;            //Settings of register

    SPI_RW_TDC1_Full((address << 8)|(settings));    //Send data over SPI
}

void TDC1_SetUp(void)
{
    TDC1_Config1();
    TDC1_Config2();
    TDC1_Mask();
}

//=====================TDC2==================//
void TDC2_Config1(void)
{
    Uint16 address  =   CONFIG1;                    //Address of register
    address         |=  TDC_Write;
    address         |=  Dont_Increment;

    Uint16 settings =   Calib_Dis;                  //Settings of register
    settings        |=  Parity_Dis;
    settings        |=  Trig_Rising_Edge;
    settings        |=  Stop_Falling_Edge;
    settings        |=  Mode2;

    SPI_RW_TDC2_Full((address << 8)|(settings));    //Send data over SPI

}

void TDC2_Config2(void)
{
    Uint16 address  =   CONFIG2;        //Address of register
    address         |=  TDC_Write;
    address         |=  Dont_Increment;

    Uint16 settings =   0b0;            //Settings of register

    SPI_RW_TDC2_Full((address << 8)|(settings));    //Send data over SPI
}

void TDC2_Mask(void)
{
    Uint16 address  =   INT_MASK;        //Address of register
    address         |=  TDC_Write;
    address         |=  Dont_Increment;

    Uint16 settings =   0b0;            //Settings of register

    SPI_RW_TDC2_Full((address << 8)|(settings));    //Send data over SPI
}

void TDC2_SetUp(void)
{
    TDC2_Config1();
    TDC2_Config2();
    TDC2_Mask();
}

//=====================TDC3==================//
void TDC3_Config1(void)
{
    Uint16 address  =   CONFIG1;                    //Address of register
    address         |=  TDC_Write;
    address         |=  Dont_Increment;

    Uint16 settings =   Calib_Dis;                  //Settings of register
    settings        |=  Parity_Dis;
    settings        |=  Trig_Rising_Edge;
    settings        |=  Stop_Falling_Edge;
    settings        |=  Mode2;

    SPI_RW_TDC3_Full((address << 8)|(settings));    //Send data over SPI

}

void TDC3_Config2(void)
{
    Uint16 address  =   CONFIG2;        //Address of register
    address         |=  TDC_Write;
    address         |=  Dont_Increment;

    Uint16 settings =   0b0;            //Settings of register

    SPI_RW_TDC3_Full((address << 8)|(settings));    //Send data over SPI
}

void TDC3_Mask(void)
{
    Uint16 address  =   INT_MASK;        //Address of register
    address         |=  TDC_Write;
    address         |=  Dont_Increment;

    Uint16 settings =   0b0;            //Settings of register

    SPI_RW_TDC3_Full((address << 8)|(settings));    //Send data over SPI
}

void TDC3_SetUp(void)
{
    TDC3_Config1();
    TDC3_Config2();
    TDC3_Mask();
}

//=====================TDC All================//
void TDC_All_Setup(void)
{
    TDC1_SetUp();
    TDC2_SetUp();
    TDC3_SetUp();
}
