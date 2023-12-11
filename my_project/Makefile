# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		        = -L../lib -L/opt/ti/msp430_gcc/include/

# switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: main.elf

# additional rules for files
main.elf: main.o wdt_handler.o input.o switches.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

main.o: main.c input.h switches.h
	${CC} ${CFLAGS} -c main.c

input.o: input.c input.h
	${CC} ${CFLAGS} -c input.c

switches.o: switches.c switches.h
	${CC} ${CFLAGS} -c switches.c

wdt_handler.o: wdt_handler.s
	${AS} wdt_handler.s

load: main.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
