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



