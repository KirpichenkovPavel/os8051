#include <8052.h>
#include "dispatcher/dispatcher.h"

void delay(void);

void main(void)
{
    initProcesses();
    initTimer();
    while (1) {
//        P0 = var;
    }
}

void delay(void)
{
    int i,j;
    for(i=0;i<0xff;i++)
        for(j=0;j<0xff;j++);
}
