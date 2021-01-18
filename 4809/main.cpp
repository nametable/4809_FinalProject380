#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Serial.h"
#include "Queue.h"
#include "stdio.h"
#include "ascii_keycodes.h"

static volatile uint8_t something_happened = 0;
static volatile uint8_t queue_empty = 1;
static volatile Serial *serial;
static volatile Queue *queue;

ISR(PORTD_PORT_vect)
{
    PORTD_INTFLAGS = 1;
    if (queue_empty) {
        if ((PORTD_IN & PIN0_bm) == 0) {
            ((Queue *)queue)->queue((uint8_t *)"Button 1 Pressed");
        }
        if ((PORTD_IN & PIN1_bm) == 0) {
            ((Queue *)queue)->queue((uint8_t *)"Button 2 Pressed");
        }
        // if ((PORTD_IN & PIN2_bm) == 0) {
        //     ((Queue *)queue)->queue((uint8_t *)"Button 3 Pressed");
        // }
        queue_empty = 0;
    }

    something_happened = 1;
}

ISR(USART0_RXC_vect){
    something_happened = 1;
    uint8_t val = ((Serial *)serial)->bt_receive_byte();
    ((Queue *)queue)->queue(val);
    queue_empty = 0;
}

void set_leds(uint8_t value) {
    PORTC_OUT = (PORTC_OUT & ~(PIN5_bm)) | ((value << 5) & PIN5_bm); //0
    PORTC_OUT = (PORTC_OUT & ~(PIN4_bm)) | ((value << 3) & PIN4_bm); //1
    PORTA_OUT = (PORTA_OUT & ~(PIN0_bm)) | ((value >> 2) & PIN0_bm); //2
    PORTF_OUT = (PORTF_OUT & ~(PIN5_bm)) | ((value << 2) & PIN5_bm); //3
    PORTC_OUT = (PORTC_OUT & ~(PIN6_bm)) | ((value << 2) & PIN6_bm); //4
    PORTB_OUT = (PORTB_OUT & ~(PIN2_bm)) | ((value >> 3) & PIN2_bm); //5
    PORTF_OUT = (PORTF_OUT & ~(PIN4_bm)) | ((value >> 2) & PIN4_bm); //6
    // PORTA_OUT = (PORTA_OUT & ~(PIN1_bm)) | ((value >> 6) & PIN1_bm); //7
}

int main()
{
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL_MCLKCTRLB = 0; // Back to 16MHz

    CPU_CCP = CCP_IOREG_gc;
    CPUINT_CTRLA |= CPUINT_IVSEL_bm; // Change int vect location

    // LED pin set to OUTPUT
    PORTA.DIRSET |= PIN0_bm | PIN1_bm;
    PORTF.DIRSET |= PIN4_bm | PIN5_bm;
    PORTB.DIRSET |= PIN2_bm;
    PORTC.DIRSET |= PIN4_bm | PIN5_bm | PIN6_bm;
    // PORTA.OUTSET = PIN1_bm;
    set_leds(0xAA);

    // Enable and setup input pins for Buttons
    PORTD.DIRCLR = (PIN0_bm | PIN1_bm | PIN2_bm);
    PORTD.PIN0CTRL = PORT_PULLUPEN_bm;
    PORTD.PIN1CTRL = PORT_PULLUPEN_bm;
    PORTD.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTD.PIN0CTRL |= PORT_ISC_BOTHEDGES_gc;
    PORTD.PIN1CTRL |= PORT_ISC_BOTHEDGES_gc;
    // PORTD.PIN2CTRL |= PORT_ISC_BOTHEDGES_gc;

    Serial mySerial;
    serial = &mySerial;
    mySerial.setup();
    Queue myQueue;
    queue = &myQueue;

    sei();

    while (1)
    {
        if (something_happened)
        {
            something_happened = 0;
            // PORTA.OUTTGL = PIN1_bm;


            while(myQueue.size() > 0) {
                uint8_t key_ascii = myQueue.dequeue();
                if (key_ascii < 128) {
                    set_leds(key_ascii);
                    uint8_t key_mod = codes4ascii[key_ascii * 2];
                    uint8_t key_norm = codes4ascii[key_ascii * 2 + 1];

                    // uint8_t buf[32];
                    // sprintf((char *)buf, "MOD: %x\n", key_mod);
                    // mySerial.u4_send(buf);
                    // sprintf((char *)buf, "KEY: %x\n", key_norm);
                    // mySerial.u4_send(buf);
                    
                    mySerial.u4_send_byte(key_mod);
                    mySerial.u4_send_byte(key_norm);
                    PORTA.OUTTGL = PIN1_bm;
                    if ((PORTD_IN & PIN2_bm) == 0)
                        _delay_ms(100);
                }

            }
            queue_empty = 1;
        }

    }

    return 0;
}