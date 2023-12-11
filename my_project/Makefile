# Makefile configuration
COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h
LDFLAGS         = -L../lib -L/opt/ti/msp430_gcc/include

# Compiler and assembler settings
CC              = msp430-elf-gcc
AS              = msp430-elf-as

# Application name
APP_NAME        = pongGame

# Object files
OBJECTS         = wdt_handler.o wdt_handler.s p1_interrupt_handler.o \
                  buzzer.o switches.o stateMachines.o led.o led_s.s \
                  pong.o ../lib/libTimer.a ../lib/libLcd.a

# Default target
all: $(APP_NAME).elf

# Linking the application
$(APP_NAME).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lTimer -lLcd

# Object file dependencies
switches.o: switches.h stateMachines.h
stateMachines.o: stateMachines.h
led.o: led.h
buzzer.o: buzzer.h
pong.o: pong.h

# Load the application to the device
load: $(APP_NAME).elf
	msp430loader.sh $(APP_NAME).elf

# Clean up
clean:
	rm -f *.o *.elf *# *~

# Additional rules (e.g., for assembly files or additional dependencies) can be added here
