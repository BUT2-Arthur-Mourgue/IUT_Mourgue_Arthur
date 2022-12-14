
#include <xc.h>
#include "UART.h"
#include "ChipConfig.h"

#define BAUDRATE 115200
#define BRGVAL ((FCY/BAUDRATE)/4)-1

void InitUART ( void) {
U1MODEbits.STSEL = 0 ; // 1 stop bit
U1MODEbits.PDSEL = 0 ; // No parity 8 data bits
U1MODEbits.ABAUD = 0 ; // Auto?Baud Disabled
U1MODEbits.BRGH = 1 ; // Low Speed mode
U1BRG = BRGVAL ; // BAUD Rate settings
U1STAbits.UTXISEL0 = 0 ; // Interrupt flag after une Tx character is transmitted
U1STAbits.UTXISEL1 = 0 ;

IFS0bits.U1TXIF = 0 ; // clear Tx interrupt flag
IEC0bits.U1TXIE = 1 ; // Enable UART Tx interrupt
U1STAbits.URXISEL = 0 ; //Interrupt flag after one Rx character is received
IFS0bits.U1RXIF = 0 ; // clear Rx flag
IEC0bits.U1RXIE = 1 ; // Enable UART Rx interrupt
U1MODEbits.UARTEN = 1 ; // Enable UART
U1STAbits.UTXEN = 1 ; // Enable UART Tx
}

void SendMessageDirect(unsigned char* message, int lenght){
    unsigned char i=0;
    for(i=0;i<lenght;i++){
        while( U1STAbits.UTXBF);  //wait while Tx buffer full
        U1TXREG = *(message)++;   // Transmit one character
    }
}