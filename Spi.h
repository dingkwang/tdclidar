/*
 * Spi.h
 *
 *  Created on: Oct 9, 2018
 *      Author: 19546
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_

//  SOMI:           GPIO59  (LaunchPad #14)
//  SIMO:           GPIO58  (LaunchPad #15)
//  SPI CLK:        GPIO60  (LaunchPad #7 )
//  CS:TDC LASER    GPIO124 (LaunchPad #13)
//  CS:Pot1         GPIO125 (LaunchPad #12)
//  CS:Pot2         GPIO29  (LaunchPad #11)

//  SOMI:           GPIO64  (LaunchPad #54)
//  SIMO:           GPIO63  (LaunchPad #55)
//  SPI CLK:        GPIO65  (LaunchPad #47)
//  CS: TDC STOP2   GPIO26  (LaunchPad #53)

//  SOMI:           GPIO101  (LaunchPad #FFC10)
//  SIMO:           GPIO100  (LaunchPad #FFC11)
//  SPI CLK:        GPIO102  (LaunchPad #FFC12)
//  CS:TDC STOP3    GPIO77   (LaunchPad #FFC13)

void SPI_Setup(void);

void SPIA_Setup(void);
void SPIB_Setup(void);
void SPIC_Setup(void);

void SPI_POT1_Start(void);
void SPI_POT1_End(void);
Uint16 SPI_RW_POT1(Uint16 data);
Uint16 SPI_RW_POT1_Full(Uint16 data);

void SPI_POT2_Start(void);
void SPI_POT2_End(void);
Uint16 SPI_RW_POT2(Uint16 data);
Uint16 SPI_RW_POT2_Full(Uint16 data);

void SPI_TDC1_Start(void);
void SPI_TDC1_End(void);
Uint16 SPI_RW_TDC1(Uint16 data);
Uint16 SPI_RW_TDC1_Full(Uint16 data);

void SPI_TDC2_Start(void);
void SPI_TDC2_End(void);
Uint16 SPI_RW_TDC2(Uint16 data);
Uint16 SPI_RW_TDC2_Full(Uint16 data);

void SPI_TDC3_Start(void);
void SPI_TDC3_End(void);
Uint16 SPI_RW_TDC3(Uint16 data);
Uint16 SPI_RW_TDC3_Full(Uint16 data);

void SPI_TDC_Start(void);
void SPI_TDC_End(void);
void SPI_RW_TDC(Uint16 TDC_data1, Uint16 TDC_data2, Uint16 TDC_data3, Uint16* TDC_data);

#endif /* SPI_SPI_H_ */
