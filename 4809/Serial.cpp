#include "Serial.h"

Serial::Serial()
{
}

void Serial::setup()
{
    // USART3
    // 4809 ==> 32u4
    PORTB.DIRSET = PIN4_bm;
    PORTB.DIRCLR = PIN5_bm;
    PORTMUX_USARTROUTEA |= PORTMUX_USART3_ALT1_gc; // Make USART3 use alt pins PB[5:4]
    // USART3_BAUD = 556;                             // (16000000 * 64) / (16 * 115200) = 555.556
    // USART3_BAUD = 6667;                             // (16000000 * 64) / (16 * 9600) = 6666.667
    USART3_BAUD = 833;                             // (16000000 * 64) / (16 * 76800) = 833.333
    USART3_CTRLB = USART_TXEN_bm;                  // Enable transmitter and 8 bit mode

    // USART0
    // 4809 <== esp32
    PORTA.DIRSET = PIN4_bm;
    PORTA.DIRCLR = PIN5_bm;
    PORTMUX_USARTROUTEA |= PORTMUX_USART0_ALT1_gc; // Make USART0 use alt pins PA[7:4]
    USART0_BAUD = 556;                             // (16000000 * 64) / (16 * 115200) = 555.556
    USART0_CTRLA = USART_RXCIE_bm;
    USART0_CTRLB = USART_TXEN_bm | USART_RXEN_bm;  // Enable transmitter + rcv
}

void Serial::bt_send_byte(uint8_t byte)
{
}

void Serial::u4_send_byte(uint8_t byte)
{
    while (!(USART3.STATUS & USART_DREIF_bm))
    {     // Transmit buffer is not empty - wait
        ; //spin
    }
    USART3_TXDATAL = byte;
}

void Serial::bt_send(uint8_t *buffer)
{
}

void Serial::u4_send(uint8_t *buffer)
{
    while (*buffer != 0)
    {
        while (!(USART3.STATUS & USART_DREIF_bm))
        {     // Transmit buffer is not empty - wait
            ; //spin
        }
        USART3_TXDATAL = *buffer;
        buffer++;
    }
}

uint8_t Serial::bt_receive_byte()
{
    while (!(USART0.STATUS & USART_RXCIF_bm))
    {
        ; //spin wait
    }
    return USART0_RXDATAL;
}

uint8_t Serial::u4_receive_byte()
{
    return -1;
}