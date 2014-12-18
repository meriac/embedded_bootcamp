# Baremetal-Programming Bootcamp 16th-17th December #

A single plain C file is sufficient to express an embedded program.

As the Cortex-M architecture is designed with C-Code in mind, no assembly level bringup code is required. The projects in this repository show how to program C code on top of a bare metal CPU without an operating system or support libraries like libc.

The purpose of this course is to lay out the programming methods for talking to hardware in a minimal configuration. Our target is a better understanding of interaction with low level hardware and toolchains for embedded systems.

## Lessons ##
* [Lesson 1](k64f/lesson1-blinky/minimal.c#L27): Blink RGB LED - alternate between red and blue
* [Lesson 2](k64f/lesson2-interrupts/interrupts.c#L18): Blink red LED using the low power interrupt
* [Lesson 3](k64f/lesson3-debug/swo_debug.c#L60): Simple SWO printing of "hello world" and a counter using 
* [Lesson 4](k64f/lesson4-debug-printf/main.c#L33): Advanced SWO printing using printf

## Usage Example ##
The example below (see [source code](k64f/lesson1-blinky)) will blink the RGB led alternating between red and blue.
```bash
# simple example
cd k64f/lesson1-blinky
make clean flash

# debug example
cd k64f/lesson4-debug-printf
make clean swo
```


## Further Reading ##
* [ARM v7-M Architecture Reference Manual](https://web.eecs.umich.edu/~prabal/teaching/eecs373-f10/readings/ARMv7-M_ARM.pdf):
  * p434 : Interrupt Vector Table Layout (Reset Vector, Stack Pointer Initialization)

* [K64 Sub-Family Reference Manual](http://cache.freescale.com/files/microcontrollers/doc/ref_manual/K64P144M120SF5RM.pdf?fasp=1)
 *  p172-p173 : memory map
 *  p663 : security fuse settings

## Software Requirements ##
* [J-Link software & documentation pack](https://www.segger.com/jlink-software.html)
* [Launchpad GCC] (https://launchpad.net/gcc-arm-embedded)

