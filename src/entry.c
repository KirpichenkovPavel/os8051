#include <8052.h>
#include "dispatcher/dispatcher.h"

void delay(void);

void main(void)
{
//    initProcesses();
    TMOD = 0x3;        // Timer mode.
    TL0 = 0;        // Clear
    TH0 = 0;        // Reg's.
    TR0 = 1;        // Set timer to run.
    ET0 = 1;        // Set interrupt.
    EA = 1;
    while (1) {
        P0 = var;
    }
    // Set global interrupt.
    /*
     *
    while(1)
    {
        P1 = 0xFF; // Turn ON all LED's connected to Port1
        delay();
        P1 = 0x00; // Turn OFF all LED's connected to Port1
        delay();
    }
     */
}

void delay(void)
{
    int i,j;
    for(i=0;i<0xff;i++)
        for(j=0;j<0xff;j++);
}
