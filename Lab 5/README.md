# Lab 5: LED Blinking with SysTick Timer

## Objective

The objective of this lab is to write an Embedded C application that blinks three LED lights after a delay of 1 minute. The LEDs should blink three times, with each blink occurring after a one-second interval. The SysTick timer operates at 16 MHz.

## Description

The program will:
1. Turn on all LEDs upon startup.
2. After a delay of 1 minute, blink the LEDs three times, with each blink separated by a one-second interval.

## Files

- `main.c`: The main source code file that implements the LED blinking logic using the SysTick timer.

## Requirements

- ARM Cortex Development Board
- LEDs (connected to appropriate GPIO pins)
- SysTick timer configured to operate at 16 MHz
- [List any other tools or dependencies]

## Setup

1. Connect the LEDs to the appropriate GPIO pins on the ARM Cortex development board.
2. Configure the SysTick timer to operate at 16 MHz.
3. Compile the `main.c` file and upload it to the development board.

## Usage

1. Upon starting the program, all LEDs should be turned on.
2. After a delay of 1 minute, the LEDs will blink three times, with each blink separated by a one-second interval.
3. Verify the behavior of your code through the simulated Kit.

## Expected Behavior

- All LEDs turn on upon program start.
- After 1 minute, LEDs will blink three times, each blink occurring after one second.

## Results

Check the simulated Kit to ensure that the LEDs blink correctly according to the specified behavior. Once verified, download your code onto the actual development kit.


