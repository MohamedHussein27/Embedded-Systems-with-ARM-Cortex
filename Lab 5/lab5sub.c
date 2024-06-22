#include "tm4c123gh6pm.h"
#include <stdint.h>


//function to turn on LEDs
void LEDs_setOutput(unsigned char data){
	  GPIO_PORTF_DATA_R &= ~ 0x0E;
    GPIO_PORTF_DATA_R |= data;
}

//function to clear LEDs
void LEDs_clearOutput(unsigned char data){
	   GPIO_PORTF_DATA_R &= ~ 0x0E;
     GPIO_PORTF_DATA_R &= data;
}


void RGBLED_Init(void)     //Initializing port F
{

SYSCTL_RCGCGPIO_R	|= 0x20;             //port F clock enable
while((SYSCTL_RCGCGPIO_R & 0x20)==0)      // Delay until the clock is initialized
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;       // Unlock port F commit register
GPIO_PORTF_CR_R   |= 0x0E;               // Allow changes to port F 321
GPIO_PORTF_AMSEL_R &= ~0x0E;       // Disable analog function
GPIO_PORTF_AFSEL_R &= ~0x0E;       // GPIO clear bit PCTL to act as port
GPIO_PORTF_PCTL_R &= ~ 0x0000FFF0;       //Disable alternate functiom
GPIO_PORTF_DIR_R |= 0x0E;          //PF 321 output
GPIO_PORTF_DEN_R |= 0x0E;          //Enable digital pins PF0 >> PF4
GPIO_PORTF_DATA_R &= ~0x0E;        //Initialize LEDs to be off
}




void systick_Init(void){                             //function to initialize systick timer
    NVIC_ST_CTRL_R = 0;                                  //clear enable to stop counter
    NVIC_ST_RELOAD_R = 0x00FFFFFF;                        //specify the RELOAD value
    NVIC_ST_CURRENT_R = 0 ;                              //clear the counter via NVIC_ST_CURRENT_R
    NVIC_ST_CTRL_R =  0x5  ;                           //enable systick with core clock
}

//fire each 10ms
void systick_wait(uint32_t delay){                   //the value of delay is equal to 2^R which R is the no. of the registers used
    NVIC_ST_RELOAD_R = delay -1 ;                    //no. of counts is equal to (2^R - 1) >>>> delay -1
    NVIC_ST_CURRENT_R = 0 ;                          // any value written to CURRENT clears
    while((NVIC_ST_CTRL_R & 0x00010000)==0) ;         // wait for the COUNT flag to be set  as the COUNT bit NUMBER is the bit 16
}


//function to wait for delay : 10ms ( delay multiplied by 10ms)
void systick_wait10ms(uint32_t delay){
    unsigned long i ;
    for(i=0;i<delay;i++){
        systick_wait(160000);                        //wait 10 ms
		}
}
int j ;

int main(){
    systick_Init();
    RGBLED_Init();
	  LEDs_setOutput(0x0E);            //turn on all LEDs initially
    while(1){
			  systick_wait10ms(100);     //wait for 1 minute in the beginning
        LEDs_clearOutput(~0x0E);    //after 1 minute turn off the LEDs
        systick_wait10ms(100);     //wait for 1 sec 
        LEDs_setOutput(0x0E);        //turn on the LEDs again
			  systick_wait10ms(100);     //wait for 1 sec
			  LEDs_clearOutput(~0x0E);    //after 1 sec turn off the LEDs
        systick_wait10ms(100);     //wait for 1 sec 
        LEDs_setOutput(0x0E);        //turn on the LEDs again
			  systick_wait10ms(100);     //wait for 1 sec 
			  LEDs_clearOutput(~0x0E);    //after 1 sec turn off the LEDs
        systick_wait10ms(100);     //wait for 1 sec 
        LEDs_setOutput(0x0E);        //turn on the LEDs again
			  break;
    }

}
	