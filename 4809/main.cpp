#include <avr/io.h>
#include <avr/interrupt.h>
#include "Serial.h"

static volatile uint8_t something_happened = 0;

ISR(PORTD_PORT_vect)
{
    PORTD_INTFLAGS = 1;
    something_happened = 1;
}

int main()
{
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL_MCLKCTRLB = 0; // Back to 16MHz

    CPU_CCP = CCP_IOREG_gc;
    CPUINT_CTRLA |= CPUINT_IVSEL_bm; // Change int vect location

    // LED pin set to OUTPUT
    PORTA.DIRSET = PIN1_bm;
    PORTA.OUTSET = PIN1_bm;

    // Enable and setup input pins for Buttons
    PORTD.DIRCLR = (PIN0_bm | PIN1_bm | PIN2_bm);
    PORTD.PIN0CTRL = PORT_PULLUPEN_bm;
    PORTD.PIN0CTRL |= PORT_ISC_BOTHEDGES_gc;

    Serial mySerial;
    mySerial.setup();

    sei();

    while (1)
    {
        if (something_happened)
        {
            something_happened = 0;
            PORTA.OUTTGL = PIN1_bm;
            mySerial.u4_send((uint8_t *)"Something happened...\n");
        }
    }

    return 0;
}