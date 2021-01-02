#include "serial.h"

void setup_serial()
{
    UBRR1 = 7;                            // 115200 baudrate (U2Xn = 0, CLK 16Mhz)
                                          // Leaving parity to default
    UCSR1B = (1 << RXEN1) | (1 << TXEN1); // Enable transmit and receive
}

void serial_send(uint8_t *buffer)
{
    while (*buffer != 0x0) // Loop until end of string
    {
        /* Wait for empty transmit buffer */
        while (!(UCSR1A & (1 << UDRE1)))
            ;
        /* Put data into buffer, sends the data */
        UDR1 = *buffer;
        buffer++;
    }
}

void serial_send_byte(uint8_t byte)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR1A & (1 << UDRE1)))
        ;
    /* Put data into buffer, sends the data */
    UDR1 = byte;
}

uint8_t serial_receive_byte()
{
    /* Wait for data to be received */
    while (!(UCSR1A & (1 << RXC1)))
        ;
    /* Get and return received data from buffer */
    return UDR1;
}