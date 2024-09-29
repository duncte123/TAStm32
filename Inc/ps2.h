#ifndef ___PS2__H
#define ___PS2__H

#include <stdint.h>

typedef struct __attribute__((packed))
{
    unsigned int select : 1;
    unsigned int l3 : 1; // just pressing down
    unsigned int r3 : 1;
    unsigned int start : 1;
    unsigned int up : 1;
    unsigned int right : 1;
    unsigned int down : 1;
    unsigned int left : 1;
    unsigned int l2 : 1;
    unsigned int r2 : 1;
    unsigned int l1 : 1;
    unsigned int r1 : 1;
    unsigned int triangle : 1;
    unsigned int circle : 1;
    unsigned int x : 1; // Also known as twitter
    unsigned int square : 1;

    // TODO: analog sticks
} PS2ControllerData;

// TODO: how many of these do I actually need?1
uint32_t PS2_ReadCommand(uint8_t player);
void PS2_SendIdentity(uint8_t player);
void PS2_SendOrigin(uint8_t player);
void PS2_SendRunData(uint8_t player, PS2ControllerData data);
void PS2_SendControllerData(uint8_t player, unsigned long data);

#endif
