#include <8052.h>

// Выделили место под стек во внешней памяти
__xdata __at (0x0) unsigned char stack_storage[128];


void copy_stack() {
    // Указатель на начало стека
    __idata unsigned char *stack_pointer = 0;
    // Стек со всеми регистрами = 128 байт
    while (stack_pointer < 127) {
        // Поехали копировать
        stack_storage[(unsigned char) stack_pointer] = *stack_pointer;
        stack_pointer++;
    }
}

void main() {
    // Заполняем стек
    __asm
            mov a, #3
            push a
            mov a, #7
            push a 
            mov a, SP 
            push a
    __endasm;
    copy_stack();
    while (1) {}
}