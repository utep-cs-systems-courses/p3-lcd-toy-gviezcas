#ifndef switches_included
#define switches_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

void switch_init();
void p2sw_init();
void switch_interrupt_handler();
static char switchp2_update_interrupt_sense();
extern char switch_state_down, switch1_state_down, switch2_state_down, switch3_state_down, switch4_state_down;

#endif // included
