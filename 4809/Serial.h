// #include <cstdint>
#include <avr/io.h>

class Serial
{
public:
    Serial();
    void setup();
    void bt_send_byte(uint8_t byte);
    void u4_send_byte(uint8_t byte);
    void bt_send(uint8_t *buffer);
    void u4_send(uint8_t *buffer);
    uint8_t bt_receive_byte();
    uint8_t u4_receive_byte();

private:
};