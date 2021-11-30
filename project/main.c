#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 
char redraw_screen = 1;

void main()
{
  configureClocks();
  lcd_init();
  clearScreen(background_color);

  init_shapes();
  draw_shapes();
  buzzer_init();
  led_init();
  p2sw_init();

  enableWDTInterrupts();

  or_sr(0x18);	/**< CPU off , GIE on*/
}
