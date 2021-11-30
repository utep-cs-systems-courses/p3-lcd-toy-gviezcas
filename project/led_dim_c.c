#include "led.h"

void led_dim_state_machine(int state)
{
  switch(state)
    {
    case(0):
      red_on = 1;
      break;
    case(1):
      redOneThird();
      break;
    }
  led_changed = 1;
  led_update();
}
