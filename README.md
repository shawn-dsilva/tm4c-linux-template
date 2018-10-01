

TM4C Template for Linux
==================

## About

This is a simple template for writing and building code for the TM4C123GH6PM Launchpad development board by TI on a Linux(specifically Ubuntu) system.This repository includes a `Makefile`,a linker script `TM4C123GH6PM.ld` for the TM4C board,the `Startup.c` file and required headers for the TM4C microcontroller and a basic blinky `main.c` file

Directory structure after running `make`

    ├── inc
    │   ├── hw_nvic.h
    │   └── hw_types.h
    ├── main.bin
    ├── Makefile
    ├── obj
    │   ├── a.axf
    │   ├── main.d
    │   ├── main.o
    │   ├── startup_gcc.d
    │   └── startup_gcc.o
    ├── README.md
    ├── src
    │   ├── main.c
    │   └── startup_gcc.c
    └── TM4C123GH6PM.ld

Tested on Ubuntu 18.04 LTS

## Toolchain setup and installation

You need these dependencies before anything else

    sudo apt install flex bison libgmp3-dev libmpfr-dev libncurses5-dev \
    libmpc-dev autoconf texinfo build-essential libftdi-dev python-yaml \
    zlib1g-dev libusb-1.0-0-dev


You will also need to get the **GCC ARM compiler/linker**

    sudo apt install arm-none-eabi-gcc
    
And a flasher like **lm4flash**

    git clone https://github.com/utzig/lm4tools.git
    cd lm4tools/lm4flash
    make
    sudo cp lm4flash /usr/bin/

## Usage

 - Clone this [tm4c-linux-template](https://github.com/shawn-dsilva/tm4c-linux-template) repository 
  
     `git clone https://github.com/shawn-dsilva/tm4c-linux-template.git`

 - Header files(.h) to be placed in `inc` folder,C source files(.c) to be placed in `src` folder
 - Set the `TARGET` variable in the Makefile to whatever you want the   
   finished .bin to be named as.
 - Run `make`
 - The object files will be in an `obj` folder,and the .bin file will be  
   in the main directory itself.
 - Run `sudo make flash` to flash the main.bin to TM4C board
 - Run `make clean` to delete all object and .bin files.


## TODO

 - OpenOCD and GDB support

