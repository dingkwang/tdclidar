/*
 * Sci.h
 *
 *  Created on: Oct 9, 2018
 *      Author: 19546
 */

#ifndef SCI_SCI_H_
#define SCI_SCI_H_

void scia_echoback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_msg(char *msg);
void scia_setup();
void scib_setup();
void send_value(int a);
void send_number(float a);
void SCIA_Send(Uint16 data);
void SCIB_Send(Uint16 data);

#endif /* SCI_SCI_H_ */
