# Lab 4: UART Communication and LED Control

## Objective

The objective of this lab is to write an Embedded C program that receives commands through the UART communication protocol to control LEDs. The program should perform specific actions based on the commands received.

## Description

The program will:
1. Turn off all LEDs upon startup.
2. Perform specific actions when receiving commands "A", "B", and "D" through UART:
   - When sending “A”, all the LEDs are turned off and the Red LED is turned on after 1 minute.
   - When sending “B”, all the LEDs are turned off and the Blue LED is turned on after 0.5 minutes.
   - When sending “D”, all the LEDs are turned off and the Green LED is turned on after 2 minutes.

## Files

- `main.c`: The main source code file that implements the UART communication and LED control logic.

## Requirements

- ARM Cortex Development Board
- UART Communication Interface
- LEDs (Red, Blue, Green)
- [List any other tools or dependencies]

## Setup

1. Connect the LEDs to the appropriate GPIO pins on the ARM Cortex development board.
2. Set up the UART communication interface on the development board.
3. Compile the `main.c` file and upload it to the development board.

## Usage

1. Upon starting the program, all LEDs should be turned off.
2. Send the command "A", "B", or "D" through the UART interface to see the corresponding LED actions.
   - Example: To send the command "A", use a terminal program or UART communication tool.

## Expected Behavior

- On sending “A”, all LEDs will turn off and the Red LED will turn on after 1 minute.
- On sending “B”, all LEDs will turn off and the Blue LED will turn on after 0.5 minutes.
- On sending “D”, all LEDs will turn off and the Green LED will turn on after 2 minutes.

## Results

Verify the behavior of your code through the simulated Kit. Ensure that the LEDs respond correctly to the commands sent via UART.


