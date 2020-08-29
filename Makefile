#
# Copyright (c) 2018, Shawn D'silva <shawn@shawndsilva.com>
# All rights reserved.
#
#  This file is free software: you can redistribute it and/or modify
 # it under the terms of the GNU Lesser General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This file is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU Lesser General Public License for more details.
 #
 # You should have received a copy of the GNU Lesser General Public License
 # along with this library.  If not, see <http://www.gnu.org/licenses/>.
#
# File:			Makefile
# Author:		Shawn D'silva <https://www.shawndsilva.com>.
# Version:		1.0.0.
# Description:	Makefile used to build files for this program


# MAIN: name of the output file
MAIN = main
#DEV : your TM4C123GH6PM when connected to your system,usually will be /dev/ttyACM0
DEV = /dev/ttyACM0
# SRCS: all source files from src directory
SRCS = $(wildcard src/*.c) \
	  $(wildcard libs/*.c)
OBJ = obj/
# OBJS: list of object files
OBJS = $(addprefix $(OBJ),$(notdir $(SRCS:.c=.o)))

#Flag points to the INC folder containing header files
INC = -Iinc

MCU = TM4C123GH6PM

# LD_SCRIPT: linker script
LD_SCRIPT = ld/$(MCU).ld


#UTILITY VARIABLES
CC = arm-none-eabi-gcc #compiler
LD = arm-none-eabi-ld #linker
OBJCOPY = arm-none-eabi-objcopy #final executable builder
FLASHER = lm4flash #flashing utility
RM      = rm -rf
MKDIR   = @mkdir -p $(@D) #creates folders if not present


#GCC FLAGS
CFLAGS = -ggdb -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16
CFLAGS += -mfloat-abi=softfp -O1 -MD -std=c99 -c

#LINKER FLAGS
LDFLAGS = -T $(LD_SCRIPT) -e Reset_Handler


# Rules to build bin
all: bin/$(MAIN).bin

$(OBJ)%.o: src/%.c               #turns .c source files into object files
	$(MKDIR)
	$(CC) -o $@ $^ $(INC) $(CFLAGS)

$(OBJ)%.o: libs/%.c                #turns .c source files into object files
	$(MKDIR)
	$(CC) -o $@ $^ $(INC) $(CFLAGS)

bin/$(MAIN).elf: $(OBJS)      ##contains debug symbols for GNU GDB
	$(MKDIR)
	$(LD) -o $@ $^ $(LDFLAGS)

bin/$(MAIN).bin: bin/$(MAIN).elf    #debug symbols for GNU GDB stripped by objcopy,finished binary ready for flashing
	$(OBJCOPY) -O binary $< $@

#Flashes bin to TM4C
flash: all
	$(FLASHER) -S $(DEV) bin/$(MAIN).bin

#remove object and bin files
clean:
	-$(RM) obj
	-$(RM) bin

re: clean all


.PHONY: all clean re
