# TARGET: name of the output file
TARGET = main
# MCU: part number to build for
MCU = TM4C123GH6PM
#DEV : your TM4C123GH6PM when connected to your system,usually will be /dev/ttyACM0
DEV = /dev/ttyACM0
# SRC: all source files from src directory
SRC = $(wildcard src/*.c)
# OBJ: directory to use for output
OBJ = obj
# LD_SCRIPT: linker script
LD_SCRIPT = $(MCU).ld


#PREPROCESSOR FLAGS
CPPFLAGS += -Iinc #inc folder is where header files are

#GCC FLAGS
CFLAGS = -g -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
CFLAGS +=-Os -ffunction-sections -fdata-sections -MD -std=c99 -Wall
CFLAGS += -pedantic -DPART_$(MCU) -c 
CFLAGS += -DTARGET_IS_BLIZZARD_RA1

#LINKER FLAGS
LDFLAGS = -T $(LD_SCRIPT) --entry ResetISR --gc-sections

#UTILITY VARIABLES
CC = arm-none-eabi-gcc #compiler
LD = arm-none-eabi-ld #linker
OBJCOPY = arm-none-eabi-objcopy #final executable builder
FLASHER = lm4flash #flashing utility
RM      = rm -f
MKDIR	= mkdir -p

# list of object files
OBJECTS = $(addprefix $(OBJ)/,$(notdir $(SRC:.c=.o)))

# Rules to build bin

all: $(TARGET).bin

$(OBJ)/%.o: src/%.c | $(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS) $(CFLAGS)

$(OBJ)/a.axf: $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

main.bin: $(OBJ)/a.axf
	$(OBJCOPY) -O binary $< $@

# create directory for object files if not already present
$(OBJ):
	$(MKDIR) $(OBJ)


#Flashes bin to TM4C
flash:
	$(FLASHER) -S $(DEV) $(TARGET).bin 

#remove object files
clean:
	-$(RM) $(OBJ)/*
	-$(RM) main.bin

.PHONY: all clean
