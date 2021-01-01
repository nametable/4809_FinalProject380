/*
main.c
*/

#define F_CPU 16000000
// Fuses on 355 - CLKDIV 8 may be set on startup

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>
#include "matrix.h"
#include "usb.h"
#include "keys.h"
#include "serial.h"

int main(int argc, char** argv) {
  usb_init();

  DDRC |= ((1 << 7) | (1 << 6));

  while (!get_usb_config_status()) {
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

  // PB04 PB05 <--> PD02 PD03
  // 32u4           4809

  // matrix_init();
	// while(1) do_matrix_scan(); // Scan the matrix
  while(1) {
    // Send A ... ?
    _delay_ms(500);
    send_keypress(KEY_A, 0);
  }
}
