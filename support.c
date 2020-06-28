#include "uart.h"

#define serial_eol() uart_puts("\r\n")

typedef unsigned char u8;
typedef unsigned int u32;

static const char *hex = "0123456789abcdef"; // hexadecimal map

void serial_rep(int c, int n)
{
    while (n-- > 0)
    {
        uart_send((u8)c);
    }
}

void serial_hex32(u32 w)
{
    uart_send(hex[0xF & (w >> 28)]);
    uart_send(hex[0xF & (w >> 24)]);
    uart_send(hex[0xF & (w >> 20)]);
    uart_send(hex[0xF & (w >> 16)]);
    uart_send(hex[0xF & (w >> 12)]);
    uart_send(hex[0xF & (w >> 8)]);
    uart_send(hex[0xF & (w >> 4)]);
    uart_send(hex[0xF & w]);
}

/*
 * Print u8 in hexadecimal to serial port
 */
void serial_hex8(u8 b)
{
    uart_send(hex[0xF & (b >> 4)]);
    uart_send(hex[0xF & b]);
}

/*
 * Pretty-printed memory dump
 */
void hexdump(const u8 *p, int n)
{
    int i;
    int c;

    while (n > 0)
    {
        serial_hex32((u32)p);
        uart_send(' ');
        for (i = 0; i < 16; ++i)
        {
            if (i == 8)
            {
                uart_send(' ');
            }
            if (i < n)
            {
                uart_send(' ');
                serial_hex8(p[i]);
            }
            else
            {
                serial_rep(' ', 3);
            }
        }
        serial_rep(' ', 2);
        uart_send('|');
        for (i = 0; i < 16; ++i)
        {
            if (i < n)
            {
                c = p[i];
                if ((c >= ' ') && (c < 0x7F))
                {
                    uart_send(c);
                }
                else
                {
                    uart_send('.');
                }
            }
            else
            {
                uart_send(' ');
            }
        }
        uart_send('|');
        serial_eol();
        p += 16;
        n -= 16;
    }
}