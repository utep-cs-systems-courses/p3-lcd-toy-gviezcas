#include <msp430.h>
#include "switches.h"
#include "draw_shapes.h"
#include "led.h"
#include "buzzer.h"
#include "lcddraw.h"

char switch1_state_down, switch2_state_down, switch3_state_down, switch4_state_down, switch_state_changed;
extern char redraw_screen;
extern u_int background_color;

/* update he interrupt sense bits so 
   interrupts are fired when a switch changes
   position */

static char switchp2_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void p2sw_init()
{
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switchp2_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p2val = switchp2_update_interrupt_sense();
  // Switch reads 0 when down, we want to reverse
  // that so the state variable is 1 when down
  //Check if switch 1 is down.
  switch1_state_down = (p2val & SW1) ? 0 : 1;
  //Check if switch 2 is down.
  switch2_state_down = (p2val & SW2) ? 0 : 1;
  //Check if switch 3 is down.
  switch3_state_down = (p2val & SW3) ? 0 : 1;
  //Check if switch 4 state down.
  switch4_state_down = (p2val & SW4) ? 0 : 1;

  if(switch1_state_down && switch3_state_down)
    {
      drawString5x7(80, 60, "score!", COLOR_GREEN, background_color);
    }else
    {
      drawString5x7(80, 60, "score!", background_color, background_color);
    }

  if(switch3_state_down)
    {
      draw_rectangle();
    }else
    {
      blank_rectangle();
    }

  if(switch4_state_down)
    {
      buzzer_state_machine(2);
    }else
    {
      buzzer_state_machine(4);
    }

  redraw_screen = 1;
}
