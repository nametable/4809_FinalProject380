#include "serial.h"

void setup_serial()
{
    // UBRR1 = 7;                            // 115200 baudrate (U2Xn = 0, CLK 16Mhz)
    // UBRR1 = 8;                            // 115200 baudrate (U2Xn = 1, CLK 8Mhz)
    // UCSR1A |= (1 << U2X1);
    // UBRR1 = 51;                              // 9600 baudrate (U2Xn = 0, CLK 8Mhz)
    // UBRR1 = 103;                              // 9600 baudrate (U2Xn = 0, CLK 16Mhz)
    UBRR1 = 12;                              // 76800 baud (.2% error)
                                          // Leaving parity to default
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1); // Enable transmit and receive + RX interrrupt
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