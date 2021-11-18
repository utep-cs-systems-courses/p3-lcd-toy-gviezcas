#include <msp430.h>
#include "libTimer.h"
#include "draw_shapes.h"

// function that handles interrupts
// from the periodic timer
// The timer fires an event 250 times/sec
void
__interrupt_vec(WDT_VECTOR) WDT()
{
  const  u_int second_limit = 250;
  static u_int second_count = 0;

  second_count++;

  if(second_count >= 125)
    {
      blank_triangle();
    }

  if (second_count >= second_limit) {
    draw_triangle();
    second_count = 0;
  }
} 

