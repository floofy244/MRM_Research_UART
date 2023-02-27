#include "config.h" // set the configuration of 
#define Baud_Calc 16000000 // value to calculate baud rate @ 16mhz
// This function used to generate delay in miliseconds

//USART Module Initialization
void UART_Init()
{
//Set the pins of RX and TX//
    TRISC6=1;
    TRISC7=1;
    
  //Set the baud rate using//
    BRGH=1;      //high speed baud rate with Bluetooth
    SPBRG  =129;
    
    //Turn on Serial Port//
    SYNC=0;
    SPEN=1;
    
    //Set 8-bit reception and transmission
    RX9=0;
    TX9=0;

   //Enable transmission and reception//
    TXEN=1; 
    CREN=1; 
    
    //Enable global and ph. interrupts//
    GIE = 1;
    PEIE= 1;
  
    //Enable interrupts for Tx. and Rx.//
    RCIE=1;
    TXIE=1;
}
//Function to write one byte of date to UART
void UART_Write(char ch)  
{
    while(!TXIF);  // hold the program till TX buffer is free
    TXREG = ch; //Load the transmitter buffer with the received value
}
//Function to read one byte of date from UART
char UART_Read()   
{
    if(OERR) // check for Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
    while(!RCIF);  // hold the program till RX buffer is free
    return RCREG; //receive the value and send it to main function
}
//Function to print string string over serial monitor
void UART_Write_Text(char* st_print)
{
    while(*st_print) //if there is a char
        UART_Write(*st_print++); //process it as a byte data
}
void main(void) 
{
TRISDbits.TRISD0=0; //Make RD0 pin as a output pin
PORTDbits.RD0=0; //initialize RD0 
UART_Init();               
UART_Write_Text("Hello ritika yeh chal rha h ");    // Introductory Text

    
int Enter_value;
while(1) //Infinite loop
    {
      Enter_value = UART_Read(); 
        
        if (Enter_value == '1') //If the user sends "1"
        {
            PORTDbits.RD0=1; //Turn on LED
            UART_Write_Text(" RED LED ON "); //Send notification to the computer 
            UART_Write_Text(" Enter New Value = ");    // Enter Value to for LED operation
            UART_Write(10);//ASCII value 10 is used for carriage return (to print in new line)
        }
        
        if (Enter_value == '0') //If the user sends "0"
        {
           PORTDbits.RD0=0; //Turn off LED
           UART_Write_Text(" RED LED OFF "); //Send notification to the computer  
           UART_Write_Text(" Enter New Value = ");// Enter Value to for LED operation
           UART_Write(10);//ASCII value 10 is used for carriage return (to print in new line)
        }
       
    }
}