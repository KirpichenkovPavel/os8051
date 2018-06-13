#include "workers.h"
#include <8052.h>

void commonJob(unsigned char k) {
    unsigned char i, j;

    while (1) {
        for (i = 0; i < 255; i++)
            for (j = 0; j < 255; j++)
                switch (k) {
                    case 0:
                        P0 = i;
                        break;
                    case 1:
                        P1 = i;
                        break;
                    case 2:
                        P2 = i;
                        break;
                    case 3:
                        P3 = i;
                        break;
                    default:
                        P0 = i;
                        break;
                }
    }
}

void worker1() {
    commonJob(0);
}

void worker2() {
    commonJob(1);
}

void worker3() {
    commonJob(2);
}

void worker4() {
    commonJob(3);
}

void worker5() {
    commonJob(2);
}

void worker6() {
    commonJob(1);
}

void worker7() {
    commonJob(0);
}

void worker8() {
    commonJob(1);
}

void worker9() {
    commonJob(2);
}

void worker10() {
    commonJob(3);
}
