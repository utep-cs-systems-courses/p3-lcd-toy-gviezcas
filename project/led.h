#ifndef led_included
#define  led_included
#include <msp430.h>

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

extern unsigned char red_on, green_on;
extern unsigned char led_changed;
extern unsigned int secondCountLimit;

void led_init();                         /* initialize LEDs */
void led_update();                       /* update leds */
void redOneThird(void);                  /*Turn on red LED one third of the time to emulate dimming*/
void led_dim_state_machine(int sate);    /*State machine to dim LED and turn off LED*/

// these are boolean flags
extern unsigned char leds_changed, green_led_state, red_led_state;

#endif
