#include "tm4c123gh6pm.h"
#include <stdint.h>
#define PF123_mask 0xE
#define PF_mask 0x20
#define SYSTEM_CLOCK 16000000

void initPortF(void)     //Initializing port F
{

SYSCTL_RCGCGPIO_R	|= PF_mask;             //port F clock enable
while((SYSCTL_RCGCGPIO_R & 0x20)==0)      // Delay until the clock is initialized
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;       // Unlock port F commit register
GPIO_PORTF_CR_R   |= 0x1F;               // Allow changes to port F (two switches and LEDs)
GPIO_PORTF_AMSEL_R = 0x00;       // Disable analog function
GPIO_PORTF_AFSEL_R = 0x0;       // GPIO clear bit PCTL to act as port
GPIO_PORTF_PCTL_R = 0x0;       //Disable alternate functiom
GPIO_PORTF_DIR_R |= PF123_mask;          //PF 321 output
GPIO_PORTF_DEN_R |= 0x1F;          //Enable digital pins PF0 >> PF4 and switches
GPIO_PORTF_DATA_R &= ~PF123_mask;        //Initialize LEDs to be off
GPIO_PORTF_PUR_R = 0x11;             //enable pull up on switches
}


int seconds = 0;

void SysTick_Handler() {
	GPIO_PORTF_DATA_R ^=  0x08;          //if interrupt happens then toggle the Green LED and incerement the secodes variable
	seconds = seconds + 1;
}


void GPIOF_Handler() {
	if (GPIO_PORTF_MIS_R & 0x10 ){       //if SW1 is pressed then turn on Red LED and pause the systick timer
		GPIO_PORTF_DATA_R = 0x00;             //first clear the data as if the Green LED is on so it would be turned off 
		GPIO_PORTF_DATA_R |= 0x02; 
    GPIO_PORTF_ICR_R |= 0x10;             //clear		
    NVIC_ST_CTRL_R = 0x0;
	}
  if (GPIO_PORTF_MIS_R & 0x01 ){     //if SW2 is pressed then turn off Red LED and turn on the systick timer again
		GPIO_PORTF_DATA_R &= ~(0x02);
		GPIO_PORTF_ICR_R |= 0x01;           //clear
		NVIC_ST_CTRL_R = 0x7;
	}
}



int main(){
initPortF();
	
	
GPIO_PORTF_IS_R = ~0x11;             // edge-sensitive
GPIO_PORTF_IBE_R = ~0x11;                    // controlled by IEV
GPIO_PORTF_IEV_R = ~0x11;                 // falling edge
GPIO_PORTF_IM_R = 0x11;         // I enabled only for pins 0, 4
NVIC_PRI7_R |= 0x00400000;     // set priorty 2 to Port F
NVIC_EN0_R = 0x40000000;      // enable interrupts for Port F
//enabling systick iterrupt
NVIC_ST_CURRENT_R = 0;
NVIC_ST_RELOAD_R = SYSTEM_CLOCK  - 1;        //wait 1 sec for each interrupt
NVIC_ST_CTRL_R = 0x7;                       //enable systick interrupt
NVIC_SYS_PRI3_R = 0x20000000;               //set priorty of systick to 1	
	
__asm {
    cpsie i
}
while (1) {
}
}