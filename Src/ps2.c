#include <stdint.h>
#include <string.h>
#include "ps2.h"
#include "stm32f4xx_hal.h"
#include "main.h"

uint32_t PS2_ReadCommand(uint8_t player)
{
    uint8_t retVal;

    return retVal;
}

void SendStop(uint8_t player)
{
    // TODO: for ide hinting only
#ifndef BOARDV4
#define BOARDV4 true
#endif

// TODO: copied from n64, need to send the correct data
#ifdef BOARDV4
    if(player == 1)
	{
		ENABLE_P1D2D3_GPIO_Port->BSRR = ENABLE_P1D2D3_Pin<<16;
		my_wait_us_asm(1);
		ENABLE_P1D2D3_GPIO_Port->BSRR = ENABLE_P1D2D3_Pin;
	}
	else if(player == 2)
	{
		ENABLE_P2D2D3_GPIO_Port->BSRR = ENABLE_P2D2D3_Pin<<16;
		my_wait_us_asm(1);
		ENABLE_P2D2D3_GPIO_Port->BSRR = ENABLE_P2D2D3_Pin;
	}
#endif
}

void SendByte(uint8_t player, unsigned char b)
{
    for(int i = 7;i >= 0;i--) // send all 8 bits, one at a time
    {
        if((b >> i) & 1)
        {
            write_1(player);
        }
        else
        {
            write_0(player);
        }
    }
}

// https://archive.org/details/padtest_202111
void PS2_SendIdentity(uint8_t player)
{
    // values from https://store.curiousinventor.com/guides/PS2
    // see "An example exchange that from a dual shock controller when first plugged in"
    SendByte(player, 0xFF); // TODO: respond to command 0x01
    SendByte(player, 0x41); // TODO: respond to command 0x42
    SendByte(player, 0x5A); // TODO: respond to command 0x00
    SendByte(player, 0xFF); // TODO: respond to command 0x00
    SendByte(player, 0xFF); // TODO: respond to command 0x00
    SendStop(player); // TODO: is this needed?
}

void PS2_SendControllerData(uint8_t player, unsigned long data)
{
    unsigned int size = sizeof(data); // should be 5 bytes?

    for(unsigned int i = 0;i < size;i++) // for each byte
    {
        for(int b = 7;b >=0;b--) // for each bit in the byte
        {
            if((data >> (b+(i*8)) & 1))
            {
                write_1(player);
            }
            else
            {
                write_0(player);
            }
        }
    }

    SendStop(player);
}

void PS2_SendRunData(uint8_t player, PS2ControllerData data)
{
    //
}