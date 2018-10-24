/*
 * Sci.c
 *
 *  Created on: Oct 9, 2018
 *      Author: 19546
 */

#include "F28x_Project.h"
#include "Clk_Settings.h"

const Uint32 SCI_Asynchronous_BaudRate   = 128000;    //Define desired baud rate for UART

Uint16 LoopCount;

void scia_echoback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_msg(char *msg);

void scib_setup()
{
    EALLOW;

    /*=========================GPIO SETUP===========================================*/
    CpuSysRegs.PCLKCR7.bit.SCI_B        = 1;    //Turn on SCI_A Clk

    GpioCtrlRegs.GPBQSEL1.bit.GPIO43    = 3;    // Asynch input GPIO43 (SCIRXDA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO42    = 3;    // Asynch input GPIO42 (SCITXDA)

    GpioCtrlRegs.GPBPUD.bit.GPIO43      = 0;    // Enable pull-up on GPIO43 (SCIRXDA)
    GpioCtrlRegs.GPBPUD.bit.GPIO42      = 0;    // Enable pull-up on GPIO42 (SCITXDA)

    GpioCtrlRegs.GPBGMUX1.bit.GPIO43    = 0b11; // Configure GPIO43 as SCIRXDA (I)
    GpioCtrlRegs.GPBMUX1.bit.GPIO43     = 0b11;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO42    = 0b11; // Configure GPIO42 as SCITXDA (O)
    GpioCtrlRegs.GPBMUX1.bit.GPIO42     = 0b11;

    GpioCtrlRegs.GPAQSEL2.bit.GPIO19    = 3;    // Asynch input GPIO43 (SCIRXDA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18    = 3;    // Asynch input GPIO42 (SCITXDA)

    GpioCtrlRegs.GPAPUD.bit.GPIO19      = 0;    // Enable pull-up on GPIO43 (SCIRXDA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18      = 0;    // Enable pull-up on GPIO42 (SCITXDA)

    GpioCtrlRegs.GPAGMUX2.bit.GPIO19    = 0b00; // Configure GPIO43 as SCIRXDA (I)
    GpioCtrlRegs.GPAMUX2.bit.GPIO19     = 0b10;
    GpioCtrlRegs.GPAGMUX2.bit.GPIO18    = 0b00; // Configure GPIO42 as SCITXDA (O)
    GpioCtrlRegs.GPAMUX2.bit.GPIO18     = 0b10;

    /*=========================SCI REG SETUP=========================================*/
    ScibRegs.SCICCR.bit.STOPBITS    = 0;    //1 StopBit
    ScibRegs.SCICCR.bit.PARITY      = 0;    // Odd parity
    ScibRegs.SCICCR.bit.PARITYENA   = 0;    //Parity Disabled
    ScibRegs.SCICCR.bit.LOOPBKENA   = 0;    //Loop Back disabled
    ScibRegs.SCICCR.bit.ADDRIDLE_MODE = 0;  //Idle-line mode protocol selected
    ScibRegs.SCICCR.bit.SCICHAR     = 0x7;  //8 bit mode

    ScibRegs.SCICTL1.bit.RXERRINTENA = 0;   //Receive error interrupt disabled
    ScibRegs.SCICTL1.bit.SWRESET    = 1;    //After a system reset, re-enable the SCI
    ScibRegs.SCICTL1.bit.TXWAKE     = 0;    //Transmit feature is not selected. In idle-line mode: write a
                                            //1 to TXWAKE, then write data to register SCITXBUF to generate an
                                            //idle period of 11 data bits In address-bit mode: write a 1 to
                                            //TXWAKE, then write data to SCITXBUF to set the address bit for
                                            //that frame to 1
    ScibRegs.SCICTL1.bit.SLEEP      = 0;    //Sleep mode disabled
    ScibRegs.SCICTL1.bit.TXENA      = 1;    //Transmitter enabled
    ScibRegs.SCICTL1.bit.RXENA      = 1;    //Send received characters to SCIRXEMU and SCIRXBUF

    //Check "19.14.2.3 SCIHBAUD Register" section in MCU Technical Reference Manual for more information
    // BRR: Baud Rate Register value
    Uint32 BBR;
    //Low Speed Peripheral clk is divided by 2 before SCI (Have not seen mention of this in MCU Technical Reference Manual)
    Uint32 Sci_Real_Clk_Frq         = Low_Speed_Peripheral_CLK_Frequency();
    BBR = (Sci_Real_Clk_Frq/(SCI_Asynchronous_BaudRate*8))-1;

    ScibRegs.SCIHBAUD.bit.BAUD      = BBR>>8;//High Byte of Baud rate
    ScibRegs.SCILBAUD.bit.BAUD      = BBR;   //Low Byte of Baud rate

    ScibRegs.SCICTL2.bit.RXBKINTENA = 0;    //Disable RXRDY/BRKDT interrupt
    ScibRegs.SCICTL2.bit.TXINTENA   = 0;    //Disable TXRDY interrupt

    ScibRegs.SCIFFTX.bit.SCIRST     = 1;    //SCI FIFO can resume transmit or receive
    ScibRegs.SCIFFTX.bit.SCIFFENA   = 0;    //SCI FIFO enhancements are disabled
    ScibRegs.SCIFFTX.bit.TXFIFORESET = 0;   //Reset the FIFO pointer to zero and hold in reset
    ScibRegs.SCIFFTX.bit.TXFFIENA   = 0;    //TX FIFO interrupt based on TXFFIL match (less than or equal to) is disabled

    EDIS;
}

void scia_setup()
{
    EALLOW;

    /*=========================GPIO SETUP===========================================*/
    CpuSysRegs.PCLKCR7.bit.SCI_A        = 1;    //Turn on SCI_A Clk

    GpioCtrlRegs.GPBQSEL1.bit.GPIO43    = 3;    // Asynch input GPIO43 (SCIRXDA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO42    = 3;    // Asynch input GPIO42 (SCITXDA)

    GpioCtrlRegs.GPBPUD.bit.GPIO43      = 0;    // Enable pull-up on GPIO43 (SCIRXDA)
    GpioCtrlRegs.GPBPUD.bit.GPIO42      = 0;    // Enable pull-up on GPIO42 (SCITXDA)

    GpioCtrlRegs.GPBGMUX1.bit.GPIO43    = 0b11; // Configure GPIO43 as SCIRXDA (I)
    GpioCtrlRegs.GPBMUX1.bit.GPIO43     = 0b11;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO42    = 0b11; // Configure GPIO42 as SCITXDA (O)
    GpioCtrlRegs.GPBMUX1.bit.GPIO42     = 0b11;

    GpioCtrlRegs.GPBQSEL1.bit.GPIO43    = 3;    // Asynch input GPIO43 (SCIRXDA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO42    = 3;    // Asynch input GPIO42 (SCITXDA)

    GpioCtrlRegs.GPBPUD.bit.GPIO43      = 0;    // Enable pull-up on GPIO43 (SCIRXDA)
    GpioCtrlRegs.GPBPUD.bit.GPIO42      = 0;    // Enable pull-up on GPIO42 (SCITXDA)

    GpioCtrlRegs.GPBGMUX1.bit.GPIO43    = 0b11; // Configure GPIO43 as SCIRXDA (I)
    GpioCtrlRegs.GPBMUX1.bit.GPIO43     = 0b11;
    GpioCtrlRegs.GPBGMUX1.bit.GPIO42    = 0b11; // Configure GPIO42 as SCITXDA (O)
    GpioCtrlRegs.GPBMUX1.bit.GPIO42     = 0b11;

    /*=========================SCI REG SETUP=========================================*/
    SciaRegs.SCICCR.bit.STOPBITS    = 0;    //1 StopBit
    SciaRegs.SCICCR.bit.PARITY      = 0;    // Odd parity
    SciaRegs.SCICCR.bit.PARITYENA   = 0;    //Parity Disabled
    SciaRegs.SCICCR.bit.LOOPBKENA   = 0;    //Loop Back disabled
    SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0;  //Idle-line mode protocol selected
    SciaRegs.SCICCR.bit.SCICHAR     = 0x7;  //8 bit mode

    SciaRegs.SCICTL1.bit.RXERRINTENA = 0;   //Receive error interrupt disabled
    SciaRegs.SCICTL1.bit.SWRESET    = 1;    //After a system reset, re-enable the SCI
    SciaRegs.SCICTL1.bit.TXWAKE     = 0;    //Transmit feature is not selected. In idle-line mode: write a
                                            //1 to TXWAKE, then write data to register SCITXBUF to generate an
                                            //idle period of 11 data bits In address-bit mode: write a 1 to
                                            //TXWAKE, then write data to SCITXBUF to set the address bit for
                                            //that frame to 1
    SciaRegs.SCICTL1.bit.SLEEP      = 0;    //Sleep mode disabled
    SciaRegs.SCICTL1.bit.TXENA      = 1;    //Transmitter enabled
    SciaRegs.SCICTL1.bit.RXENA      = 1;    //Send received characters to SCIRXEMU and SCIRXBUF

    //Check "19.14.2.3 SCIHBAUD Register" section in MCU Technical Reference Manual for more information
    // BRR: Baud Rate Register value
    Uint32 BBR;
    //Low Speed Peripheral clk is divided by 2 before SCI (Have not seen mention of this in MCU Technical Reference Manual)
    Uint32 Sci_Real_Clk_Frq         = Low_Speed_Peripheral_CLK_Frequency();
    BBR = (Sci_Real_Clk_Frq/(SCI_Asynchronous_BaudRate*8))-1;

    SciaRegs.SCIHBAUD.bit.BAUD      = BBR>>8;//High Byte of Baud rate
    SciaRegs.SCILBAUD.bit.BAUD      = BBR;   //Low Byte of Baud rate

    SciaRegs.SCICTL2.bit.RXBKINTENA = 0;    //Disable RXRDY/BRKDT interrupt
    SciaRegs.SCICTL2.bit.TXINTENA   = 0;    //Disable TXRDY interrupt

    SciaRegs.SCIFFTX.bit.SCIRST     = 1;    //SCI FIFO can resume transmit or receive
    SciaRegs.SCIFFTX.bit.SCIFFENA   = 0;    //SCI FIFO enhancements are disabled
    SciaRegs.SCIFFTX.bit.TXFIFORESET = 0;   //Reset the FIFO pointer to zero and hold in reset
    SciaRegs.SCIFFTX.bit.TXFFIENA   = 0;    //TX FIFO interrupt based on TXFFIL match (less than or equal to) is disabled

    EDIS;
}

void SCIA_Send(Uint16 data)
{
    while(SciaRegs.SCICTL2.bit.TXRDY == 0); //Waits while SCITXBUF is full

    SciaRegs.SCITXBUF.bit.TXDT  = data;     //Inputs data into transmit buffer

    while(SciaRegs.SCICTL2.bit.TXEMPTY == 0);
}

void SCIB_Send(Uint16 data)
{
    while(ScibRegs.SCICTL2.bit.TXRDY == 0); //Waits while SCITXBUF is full

    ScibRegs.SCITXBUF.bit.TXDT  = data;     //Inputs data into transmit buffer

    while(ScibRegs.SCICTL2.bit.TXEMPTY == 0);
}

void scia_echoback_init()
{
    SciaRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    SciaRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all = 0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

    //SciaRegs.SCIHBAUD.all = 0x0002;
    //SciaRegs.SCILBAUD.all = 0x008A;
    SciaRegs.SCIHBAUD.all = 0x00;
    SciaRegs.SCILBAUD.all = 0x40;


    SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset
}


void scia_xmit(int a)
{

    //while (SciaRegs.SCIFFTX.bit.TXFFST != 0)
    //    SciaRegs.SCITXBUF.all =a;
    while (SciaRegs.SCICTL2.bit.TXRDY == 0);
    SciaRegs.SCITXBUF.all =a;
}


void scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}


void scia_fifo_init()
{
    //SciaRegs.SCIFFTX.all = 0xE040;
    //SciaRegs.SCIFFRX.all = 0x2044;
    SciaRegs.SCIFFTX.bit.SCIFFENA=0;    //disables fifo
    SciaRegs.SCIFFRX.bit.RXFFIENA=0;    //disables fifo
    SciaRegs.SCIFFCT.all = 0x0;
}
void send_value(int a)
{
 switch(a)
 {
 case 0: SciaRegs.SCITXBUF.all =0x30; break;
 case 1: SciaRegs.SCITXBUF.all =0x31; break;
 case 2: SciaRegs.SCITXBUF.all =0x32; break;
 case 3: SciaRegs.SCITXBUF.all =0x33; break;
 case 4: SciaRegs.SCITXBUF.all =0x34; break;
 case 5: SciaRegs.SCITXBUF.all =0x35; break;
 case 6: SciaRegs.SCITXBUF.all =0x36; break;
 case 7: SciaRegs.SCITXBUF.all =0x37; break;
 case 8: SciaRegs.SCITXBUF.all =0x38; break;
 case 9: SciaRegs.SCITXBUF.all =0x39; break;
 default: scia_msg("out of range"); break;

 }
}

void send_number(float a)
{
   float a1= a;
   int a2= (int)a1;
   a1=a1-a2;
   float b= a/10000;
   int c=(int)b;
   int d=0; //for first bit number
   if(c!=0)
   {
       send_value(c);
       a= a-c*10000;
       d=1;
   }
   else
   {
       d=0;

   }


   b=a/1000;
   c=(int)b;
   if(c!=0)
   {
       send_value(c);
       a= a-c*1000;
       d=1;
   }
   else if(c==0&&d!=0)
   {
   send_value(0);
   }
   else
   {

   };



   b=a/100;
   c=(int)b;
   if(c!=0)
   {
   send_value(c);
   a= a-c*100;
   d=1;
   }
   else if(c==0&&d!=0)
   {
   send_value(0);
   }
   else
     {

     };



   b=a/10;
   c=(int)b;
   if(c!=0)
   {
   send_value(c);
   a= a-c*10;
   d=1;
   }
   else if(c==0&&d!=0)
   {
   send_value(0);
   }
   else
   {

   };




   b=a/1;
   c=(int)b;
   if(c!=0)
   {
   send_value(c);
   a= a-c*1;
   d=1;
   }
   else if(c==0&&d!=0)
   {
   send_value(0);
   }
   else
   {

   };




    a=a1*1000;
    if(a>0)
    {
        scia_msg(".");
    }
    int b1; int b2; int b3;
    b1= (int)(a/100);
    a=a-b1*100;
    b2= (int)(a/10);
    a=a-b2*10;
    b3= (int)(a/1);
    a=a-b3*1;
    if(b3!=0)
    {
        send_value(b1);
        send_value(b2);
        send_value(b3);
    }
    else if(b3==0&&b2!=0)
    {
        send_value(b1);
        send_value(b2);
        send_value(b3);
    }
    else if(b3==0&&b2==0&&b1!=0)
    {
        send_value(b1);
        send_value(b2);
        send_value(b3);
    }

    else {

    }

}

