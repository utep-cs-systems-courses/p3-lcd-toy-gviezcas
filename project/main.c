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

void update_text(void)
{
  const u_char text_row = 20;
  const u_char text_col = 40;
  const u_char char_width = 12;
  static u_char blue = 31, green = 16, red = 31;
  u_int on_color = (green << 5) | red;
  u_int off_color = (blue << 11) | red;
  static u_char score = '0';
  static u_char tenths_score = '0';

  drawChar5x7(text_col + char_width, text_row, score, on_color, background_color);
  drawString5x7((screenWidth / 4), 150, "Feed PacMan", COLOR_RED, background_color);

  if(switch1_state_down && switch3_state_down)
    {
      if(score == '9')
	{
	  score = '0';
	  tenths_score = (u_char)(tenths_score + 1);
	  drawChar5x7(text_col, text_row, tenths_score, on_color, background_color);
	  if(tenths_score == '9')
	    {
	      tenths_score = '0';
	    }
	}else
	{
	  score = (u_char)(score + 1);
	  drawChar5x7(text_col + char_width, text_row, score, on_color, background_color);
	}
    }
}

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

  while(1)
    {
      if(redraw_screen)
	{
	  redraw_screen = 0;
	  update_text();
	}
      green_on = 0;
      led_changed = 1;
      led_update();
      or_sr(0x10);

      green_on = 1;
      led_changed = 1;
      led_update();
    }
}
