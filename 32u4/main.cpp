/*
main.c
*/

// Fuses on 355 - CLKDIV 8 may be set on startup

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>
#include "usb.h"
#include "keys.h"
#include "serial.h"
#include "Queue.h"

static volatile Queue *queue;

ISR(USART1_RX_vect) {
    // send_keypress(KEY_A, KEY_NONE);
    uint8_t val = serial_receive_byte();
    ((Queue *)queue)->queue(val);
}

int main(int argc, char **argv)
{
  usb_init();

  DDRC |= ((1 << 7) | (1 << 6));

  while (!get_usb_config_status())
  {
    // LED Animation
    PORTC &= ~(1 << 6);
    PORTC |= (1 << 7);
    _delay_ms(100);
    PORTC &= ~(1 << 7);
    PORTC |= (1 << 6);
    _delay_ms(100);
  }
  PORTC &= ~((1 << 6) | (1 << 7));

  // Switch to 16 mhz by disabling clock divider
  cli();
  CLKPR = 0x80;
  CLKPR = 0x00;
  sei();

  Queue myQueue;
  queue = &myQueue;

  // PB04 PB05 <--> PD02 PD03
  // 32u4           4809
  setup_serial();
  // matrix_init();
  // while(1) do_matrix_scan(); // Scan the matrix
  send_keypress(KEY_A, KEY_NONE);
  send_keypress(KEY_B, KEY_MOD_LSHIFT);
  send_keypress(KEY_C, KEY_NONE);
  send_keypress(KEY_D, KEY_MOD_LSHIFT);
  while (1)
  {
    if (myQueue.size() >= 2)  // 2 or more
    {
      // Send A ... ?
      // _delay_ms(500);
      uint8_t key_mod = myQueue.dequeue();
      uint8_t key_norm = myQueue.dequeue();
      if (key_norm)
      {
        send_keypress(key_norm, key_mod);
      }
      _delay_us(2000);
    }

  }
}
