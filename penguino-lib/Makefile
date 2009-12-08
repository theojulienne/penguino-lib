NAME       = example
DEVICE     = atmega32
CLOCK      = 16000000
OBJECTS    = $(NAME).o penguino/uart/RingBuff.o penguino/uart/uart.o penguino/uart/uart-stdio.o penguino/io.o

COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -std=gnu99

# symbolic targets:
all:	$(NAME).bin

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

clean:
	rm -f $(NAME).bin $(NAME).elf $(OBJECTS)

$(NAME).elf: $(OBJECTS)
	$(COMPILE) -o $(NAME).elf $(OBJECTS)

$(NAME).bin: $(NAME).elf
	rm -f $(NAME).bin
	avr-objcopy -j .text -j .data -O binary $(NAME).elf $(NAME).bin

disasm:	$(NAME).elf
	avr-objdump -d $(NAME).elf
