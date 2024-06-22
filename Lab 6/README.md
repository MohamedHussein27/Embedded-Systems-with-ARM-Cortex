# Lab 6: SysTick Timer and GPIO Interrupts

## Objective

The objective of this lab is to write an Embedded C program that uses the SysTick timer to increment a "seconds" variable each second and toggle a Green LED. The program also handles GPIO interrupts to pause/resume the SysTick timer and control a Red LED.

## Description

The program will:
1. Increment a "seconds" variable and toggle the Green LED each second in the SysTick_Handler().
2. Pause the SysTick timer and turn on the Red LED when SW1 is pressed.
3. Resume the SysTick timer and turn off the Red LED when SW2 is pressed.

## Requirements

- ARM Cortex Development Board
- LEDs (Green and Red) connected to appropriate GPIO pins
- Switches (SW1 and SW2) connected to appropriate GPIO pins
- SysTick timer configured to operate at 16 MHz
- GPIOF interrupt with a priority of 2

## Setup

1. Connect the Green and Red LEDs to the appropriate GPIO pins on the ARM Cortex development board.
2. Connect SW1 and SW2 to the appropriate GPIO pins on the ARM Cortex development board.
3. Configure the SysTick timer to operate at 16 MHz with an interrupt priority of 1.
4. Configure GPIOF interrupts with a priority of 2.
5. Compile the `main.c` file and upload it to the development board.

## Files

- `main.c`: The main source code file that implements the SysTick timer, GPIO interrupt handling, and LED control.

## Usage

1. Upon starting the program, all LEDs should be turned off.
2. The Green LED should toggle each second, and the "seconds" variable should increment.
3. Press SW1 to pause the SysTick timer and turn on the Red LED.
4. Press SW2 to resume the SysTick timer and turn off the Red LED.
5. Verify the behavior of your code through the simulated Kit.

## Expected Behavior

- All LEDs are off upon program start.
- The Green LED toggles each second.
- Pressing SW1 pauses the SysTick timer and turns on the Red LED.
- Pressing SW2 resumes the SysTick timer and turns off the Red LED.

## Results

Check the simulated Kit to ensure that the LEDs and timer behave correctly according to the specified behavior. Once verified, download your code onto the actual development kit.


