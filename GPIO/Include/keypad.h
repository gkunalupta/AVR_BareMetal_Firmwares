#ifndef KEYPAD_H_
#define KEYPAD_H_
#include <uarts.h>
/*
R1 : PC0(37)
R2 : PC1(36)
R3 : PC2(35)
R4 : PC3(34)
C1 : PC4(33)
C2 : PC5(32)
C3 : PC6(31)
*/

#define R1 0
#define R2 1
#define R3 2
#define R4 3
#define C1 4
#define C2 5
#define C3 6

uint8_t getkey();
bool flag = 0;
uint8_t getKey();

#include "keypad.cpp"

#endif