
  
  

# TM4C Template for Linux

**UPDATE** : Added new `startup.c` and `startup.h` files for the TM4C,and a linker script all written from scratch by me,and Open Source,
unlike the earlier TI BSD licensed `startup_gcc.c` file and associated linker script
  

## About

This is a simple template for writing and building code for the TM4C123GH6PM Launchpad development board by TI on a Linux(specifically Ubuntu) system.This repository includes a `Makefile`,a linker script `TM4C123GH6PM.ld` for the TM4C board,the `Startup.c` file and required headers for the TM4C microcontroller and a basic blinky `main.c` file

  

Directory structure after running `make`
```
.
├── bin
│   ├── main.bin
│   └── main.elf
├── inc
│   └── startup.h
├── ld
│   └── TM4C123GH6PM.ld
├── libs
│   └── startup.c
├── Makefile
├── obj
│   ├── main.d
│   ├── main.o
│   ├── startup.d
│   └── startup.o
├── README.md
└── src
    └── main.c
```
Tested on Ubuntu 18.04 LTS

  

## Toolchain setup and installation

  

You need these dependencies before anything else

  
```
sudo apt install flex bison libgmp3-dev libmpfr-dev libncurses5-dev \

libmpc-dev autoconf texinfo build-essential libftdi-dev python-yaml \

zlib1g-dev libusb-1.0-0-dev
```
  
  

You will also need to get the **GCC ARM compiler/linker**

  

```sudo apt install arm-none-eabi-gcc```

And a flasher like **lm4flash**

  
```
git clone https://github.com/utzig/lm4tools.git

cd lm4tools/lm4flash

make

sudo cp lm4flash /usr/bin/
```
  

## Usage

  

- Clone this [tm4c-linux-template](https://github.com/shawn-dsilva/tm4c-linux-template) repository

```git clone https://github.com/shawn-dsilva/tm4c-linux-template.git```

- Create a file called `61.dialout.rules` in `/etc/udev/rules.d` with this line inside it `SUBSYSTEM=="usb", ATTRS{idVendor}=="1cbe", ATTRS{idProduct}=="00fd", MODE="0666"`
this is to allow any program to read or write to your TM4C Launchpad board,i.e you will not have to use `sudo` everytime

- Header files(`.h`) to be placed in `inc` folder
- C source files( `.c`) to be placed in `src` folder
- Library files for peripherals to go in the `libs` folder,these files are also C source files( `.c` )

- Set the `TARGET` variable in the Makefile to whatever you want the
finished `.bin` to be named as.

- Run `make`

- The object files will be in an `obj` folder

- The `main.bin` file and the `main.elf` (with `GNU GDB` debugging symbols) will be in the `bin` folder

- Run `sudo make flash` to flash the `main.bin` to TM4C board

- Run `make clean` to delete all object and `.bin` files.

  
  

## Debugging with OpenOCD and GDB

- Download,Build and Install **OpenOCD**
```
git clone git://git.code.sf.net/p/openocd/code openocd.git
cd openocd.git
./bootstrap
./configure --prefix=/usr --enable-maintainer-mode --enable-stlink 
--enable-ti-icdi
make
sudo make install
 ```

- Install **GNU GDB** 

```sudo apt install gdb-multiarch```

- Run this command to start OpenOCD with your board
```
openocd -f /usr/share/openocd/scripts/board/ek-tm4c123gxl.cfg 
```

You should see this output
```
Open On-Chip Debugger 0.10.0+dev-00554-g05e0d633 (2018-10-16-17:47)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : The selected transport took over low-level target control. 
The results might differ compared to plain JTAG/SWD
adapter speed: 500 kHz
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
Info : RCLK (adaptive clock speed)
Info : ICDI Firmware version: 9270
Info : tm4c123gh6pm.cpu: hardware has 6 breakpoints, 4 watchpoints
Info : Listening on port 3333 for gdb connections
```

- Now open a new terminal and run ```gdb-multiarch -tui``` this command opens gdb with a CLI user interface

- At the prompt enter  `file bin/main.elf`
and then `target remote localhost:3333`
you should see this UI

```
 ┌──src/main.c────────────────────────────────────────────────────────────────────────────────────────┐
   │46      int main(void){                                                                             │
   │47        PortF_Init();                                                                             │
   │48        while(1){                                                                                 │
  >│49         if(PF4 == 0x0){                                                                          │
   │50          Led = GPIO_PORTF_DATA_R;   // read value in PORTF DATA register                         │
   │51          Led = Led^0x02;            // reverse value of LED                                      │
   │52          GPIO_PORTF_DATA_R = Led;   // write value to PORTF DATA register,toggle led             │
   │53          Delay();                                                                                │
   │54          }                                                                                       │
   │55        }                                                                                         │
   │56      }                                                                                           │
   │57                                                                                                  │
   │58      // Color    LED(s) PortF                                                                    │
   │59      // dark     ---    0                                                                        │
   │60      // red      R--    0x02                                                                     │
   │61      // blue     --B    0x04                                                                     │
   │62      // green    -G-    0x08                                                                     │
   │63      // yellow   RG-    0x0A                                                                     │
   │64      // sky blue -GB    0x0C                                                                     │
   │65      // white    RGB    0x0E                                                                     │
   │66      // pink     R-B    0x06                                                                     │
   │67                                                                                                  │
   │68                                                                                                  │
   │69                                                                                                  │
   └────────────────────────────────────────────────────────────────────────────────────────────────────┘
remote Remote target In: main                                                            L49   PC: 0x2da 
Type "apropos word" to search for commands related to "word".
(gdb) target remote localhost:3333
Remote debugging using localhost:3333
warning: Architecture rejected target-supplied description
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
Truncated register 16 in remote 'g' packet
(gdb) file bin/main.elf
Reading symbols from bin/main.elf...done.
(gdb) target remote localhost:3333
Remote debugging using localhost:3333
0x000002da in main () at src/main.c:49
(gdb) 
```

- Now you can run various commands like `layout regs` to get the register layouts or `disass` to disassemble the code for example
