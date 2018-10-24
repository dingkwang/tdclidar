/*
 * Clk_Settings.h
 *
 *  Created on: Oct 13, 2018
 *      Author: 19546
 */

#ifndef CLK_SETTINGS_CLK_SETTINGS_H_
#define CLK_SETTINGS_CLK_SETTINGS_H_

void Set_Clk_IntoSC2_PPL(void);
void Clk_Setup_XTL(void);
void Clk_Setup_IntoSC2(void);
void Set_Clk_XTL(void);

//Gives you the system clock frequency in Hz
Uint32 PLL_System_CLK_Frequency(void);

//Gives you the Low_Speed peripheral clock frequency in Hz
Uint32 Low_Speed_Peripheral_CLK_Frequency(void);

#endif /* CLK_SETTINGS_CLK_SETTINGS_H_ */
