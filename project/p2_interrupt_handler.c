#include <msp430.h>
#include "switches.h"

void port2_c_handler(void)
{
  if(P2IFG & SWITCHES)
    {
      P2IFG &= ~SWITCHES;
      switch_interrupt_handler();
    }
}
