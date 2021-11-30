# makfile configuration
COMMON_OBJECTS		= draw_shapes.o wdtInterruptHandler.o buzzer.o led.o switches.o p2_interrupt_handler.o p2_asm_handler.o
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: main.elf main_s.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} main.o led_dim_c.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

main_s.elf: ${COMMON_OBJECTS} main.o led_dim_s.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load_c: main.elf
	msp430loader.sh $^

load_s: main_s.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *~
