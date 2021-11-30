#include <msp430.h>
#include "led.h"

// led states, red starts off green starts on
unsigned char red_on = 0, green_on = 1;
unsigned char led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] ={0, LED_GREEN};
void led_init()
{
  P1DIR |= LEDS;		        // bits attached to leds are output
  led_changed = 1;
  led_update();
}

void led_update()
{
  if (led_changed)
    {
    char ledFlags = redVal[red_on] | greenVal[green_on];
    
    P1OUT &= (0xff^LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;		     // set bit for on leds
    led_changed = 0;
    }
}

void redOneThird(void)
{
  static unsigned int redState = 0;
  
  switch(redState)
    {
    case(0):
      red_on = 0;
      redState = 1;
      break;
    case(1):
      red_on = 0;
      redState = 2;
      break;
    case(2):
      red_on = 1;
      redState = 0;
      break;
    }
  led_changed = 1;
  led_update();
}
