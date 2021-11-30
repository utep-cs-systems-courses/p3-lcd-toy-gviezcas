#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

char switch1_state_down, switch2_state_down, switch3_state_down, switch4_state_down, switch_state_changed;

/* update he interrupt sense bits so 
   interrupts are fired when a switch changes
   position */

static char
switch_update_interrupt_sense()
{
  char p1val = P1IN;
  P1IES |= (p1val & SWITCHES);// if switch up, sense down
  P1IES &= (p1val | ~SWITCHES);// if switch down, sense up
  return p1val;
}

static char switchp2_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}



/* setup switches */
void
switch_init()
{
  P1REN |=  SWITCHES;// enables resistors for switches
  P1IE  |=  SWITCHES;// enable interrupts from switches
  P1OUT |=  SWITCHES;// turn on switches so we can read them
  P1DIR &= ~SWITCHES;// set switch pins to input
  switch_update_interrupt_sense();
  led_update();
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
  char p1val = switch_update_interrupt_sense();
  char p2val = switchp2_update_interrupt_sense();
  // Switch reads 0 when down, we want to reverse
  // that so the state variable is 1 when down
  switch3_state_down = (p1val & SW3) ? 0 : 1;
  //Check if switch 1 is down.
  switch1_state_down = (p2val & SW1) ? 0 : 1;
  //Check if switch 2 is down.
  switch2_state_down = (p2val & SW2) ? 0 : 1;
  //Check if switch 3 is down.
  switch3_state_down = (p2val & SW3) ? 0 : 1;
  //Check if switch 4 state down.
  switch4_state_down = (p2val & SW4) ? 0 : 1;


  if (switch3_state_down)
    {
      green_on = 0;
    } else
    {
      green_on = 1;
    }
  
  if(switch2_state_down)
    {
      led_dim_state_machine(0);
      
    }

  if(switch1_state_down)
    {
      buzzer_state_machine(3);
    }

  if(switch2_state_down)
    {
      buzzer_state_machine(2);
    }

  if(switch3_state_down)
    {
      buzzer_state_machine(1);
    }

  if(switch4_state_down)
    {
      buzzer_state_machine(0);
    }
  led_changed = 1;
  led_update();
}
