#include <8052.h>
#include "dispatcher/dispatcher.h"


void main(void)
{
    initProcesses();
    initTimer();
    while (1);
}
