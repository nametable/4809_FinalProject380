#include <avr/io.h>

void setup_serial();
void serial_send(uint8_t *buffer);
void serial_send_byte(uint8_t byte);
uint8_t serial_receive_byte();