#pragma config FOSC = HS       // Oscillator Selection bits (HS oscillator)

#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)

#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)

#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)

#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)

#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)

#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)

#pragma config CP = OFF  


#include <xc.h>
#include <stdio.h>



void main()
{
    TRISCbits.TRISC6 = 0;   
    TRISCbits.TRISC7 = 1;   
    
    SPBRG = 25;             
    TXSTAbits.BRGH = 1;
    TXSTAbits.SYNC = 0;     
    RCSTAbits.SPEN = 1;     
    
    while (1)
    {
        while (!TXSTAbits.TRMT);     
        TXREG = 'A';                 
        while (!PIR1bits.RCIF);      
        char received = RCREG;       
        printf("Received: %c\n", received);  
    }
}

