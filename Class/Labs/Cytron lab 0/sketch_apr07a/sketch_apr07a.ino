#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN 5 // Define the pin number for the LED (pin 13 on Arduino Uno)

int main(void) {
    // Set pin 13 as output
    DDRB |= (1 << LED_PIN);

    while (1) {
        // Turn on the LED
        PORTB |= (1 << LED_PIN);
        _delay_ms(1000); // Delay for 1 second

        // Turn off the LED
        PORTB &= ~(1 << LED_PIN);
        _delay_ms(1000); // Delay for 1 second
    }

    return 0;
}
