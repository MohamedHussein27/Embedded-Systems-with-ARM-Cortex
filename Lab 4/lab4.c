#define CR 0x0D              //0x0D  is the ASCII code for enter


#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <string.h>





 //******************************************>>> timing <<<********************************************

void systick_Init(void){                             //function to initialize systick timer
    NVIC_ST_CTRL_R = 0;                                  //clear enable to stop counter
    NVIC_ST_RELOAD_R = 0x00FFFFFF;                        //specify the RELOAD value
    NVIC_ST_CURRENT_R = 0 ;                              //clear the counter via NVIC_ST_CURRENT_R
    NVIC_ST_CTRL_R =  0x5  ;                           //enable systick with core clock
}

//function to wait for a 62.5 nsec
void systick_wait(uint32_t delay){                   //the value of delay is equal to 2^R which R is the no. of the registers used
    NVIC_ST_RELOAD_R = delay -1 ;                    //no. of counts is equal to (2^R - 1) >>>> delay -1
    NVIC_ST_CURRENT_R = 0 ;                          // any value written to CURRENT clears
    while((NVIC_ST_CTRL_R & 0x00010000)==0) ;         // wait for the COUNT flag to be set  as the COUNT bit NUMBER is the bit 16
}


//function to wait for delay : 10ms ( delay multiplied by 10ms)
void systick_wait1s(uint32_t delay){
    unsigned long i ;
    for(i=0;i<delay;i++){
        systick_wait(160000);                         //wait 10ms
    }
}




//***********************************************>>> UART0 <<<*********************************************

void UART_Init(void){          // function to initialize UART
	SYSCTL_RCGCUART_R |= 0x1;       //activate UART0
	SYSCTL_RCGCGPIO_R |= 0x1;              // activate PORT A


UART0_CTL_R &= ~0x01  ;                 //disabling UART while initializing

//setting baudrate
UART0_IBRD_R = 0x6B;           // IBRD=int(16000000/(16*9600)) = int (104.1667) (divider for frequency)
UART0_FBRD_R = 0xB;            // FBRD int(0.1667 * 64 +0.5) = 11
UART0_LCRH_R = 0x007;        // bit 4,5 are set to 11 (binary), which corresponds to an 8-bit word length.
	                          //bit 6 is set to 1 (binary) enabling the FIFO mode for the UART receiver and transmitter

UART0_CTL_R = 0x0301; // enable RXE, TXE and UART 001100000001
GPIO_PORTA_AFSEL_R |= 0x03; // enable alt function PA0, PA1 ,
                            //Enable AFSEL for UART pins during initialization to configure them for their alternate function as UART RX and TX pins.
GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00)+0x00000011;

//UART for PAO, PA1
GPIO_PORTA_DEN_R |= 0x03; // enable digital I/O on PA0, PA1
GPIO_PORTA_AMSEL_R &= ~0x03; // disable analog function on PA0, PA1
}


//function to read the data
char UART0_read_data(){
while((UART0_FR_R & UART_FR_RXFE));  // check if RXFE is not empty(0) so the data is avialable
return (char)(UART0_DR_R & 0xFF);   // we are ANDing the first 8 bits in data reg with 0xFF so we are sending the first 8 bits
}

//function to write data
 void UART0_write_data(char data){
    while((UART0_FR_R & UART_FR_TXFF) != 0 );       // check if TXFF is not full(0) so the data can be transmitted
UART0_DR_R = data ;

}


void UART_OutString(char *pt){

    while(*pt){              //While the data has avalue and not the null terminator
        UART0_write_data(*pt);
        pt ++;               //incerement to get all the chars of the array
    }
}

//function to get the command we want to run
void getCommand(char *Command , int len){
    char character;
    int i ;
    for(i=0;i<len;i++){
       character = UART0_read_data();
       if (character != CR){
        Command[i] = character;              //overwriting the array of zeroes with characters to complete a string to do a specific command
        UART0_write_data(character);         //printing the data to be seen after writing it
       }
       else if (character == CR || i==len){ break;}
    }
}




//*********************************************>>> LEDs <<<*********************************************

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




int main()
{
    const int len = 1;
    char Command[len] = {0};
    UART_Init();
    RGBLED_Init();
		systick_Init();

    while(1)
    {
        UART_OutString("\nEnter:\n");
        getCommand(Command,len);

        if (strcmp(Command , "A") == 0){                  //comparing the string to see if it has the char 'A'
            LEDs_clearOutput(~0x02) ;                        //turning off all LEDs first
            systick_wait1s(60);                       //wait for 1 minute
            LEDs_setOutput(0x02) ;                         //after 1 minute turn on the Red LED
            memset(Command , 0 , len);                  //clear the array that holds the taken string
        }
        else if (strcmp(Command , "B") == 0){              //comparing the string to see if it has the char 'B'
            LEDs_clearOutput(~0x04) ;                        //turning off all LEDs first
            systick_wait1s(30);                       //wait for 0.5 minute
            LEDs_setOutput(0x04);                         //after 0.5 minute turn on the Blue LED
            memset(Command , 0 , len);                  //clear the array that holds the taken string
        }
        else if (strcmp(Command , "D") == 0){              //comparing the string to see if it has the char 'D'
            LEDs_clearOutput(~0x08) ;                        //turning off all LEDs first
            systick_wait1s(120);                       //wait for 2 minute
            LEDs_setOutput(0x08) ;                         //after 2 minute turn on the Green LED
            memset(Command , 0 , len);                  //clear the array that holds the taken string
        }
        else {                                              //if the string holds a different value then turn off the LEDs and clear the string
            GPIO_PORTF_DATA_R=0x0 ;                        //turning off all LEDs
            memset(Command , 0 , len);                  //clear the array that holds the taken string
        }
    }
}
