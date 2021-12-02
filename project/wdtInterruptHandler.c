#include <msp430.h>
#include "libTimer.h"
#include "draw_shapes.h"
#include "buzzer.h"

// function that handles interrupts
// from the periodic timer
// The timer fires an event 250 times/sec
void
__interrupt_vec(WDT_VECTOR) WDT()
{
  const  u_int second_limit = 250;
  static u_int second_count = 0;

  second_count++;

  if(second_count >= 100)
    {
      blank_triangle();
      buzzer_state_machine(4);
    }

  if (second_count >= second_limit)
    {
      draw_triangle();
      buzzer_state_machine(2);
      second_count = 0;
    }
} 

