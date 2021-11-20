#include "adc.h"

void Adc_init(void){
    ADCON0 = 0; // init
    ADCON1 = 0; // init
    ADCON2 = 0; // init

    ADCON0bits.CHS = 0b00000; //analog channel select bits
    ADCON1bits.PVCFG = 00;  // Positive Voltage Reference Configuration bits connected to internal Vref+
    ADCON1bits.NVCFG = 00; // Negative Voltage Reference Configuration bits connected to internal Vref-
    ADCON2bits.ADCS = 0b000; // Fosc/2
    ADCON2bits.ACQT = 0b001; //acquisition time 2*Tad
    //ADCON2bits.ADFM = 0; //resultat left justified de base à zero
    ADCON0bits.ADON = 1; //adc enabled 
     __delay_ms(5); //wait
}

float conv(){
    ADCON0bits.GO = 1; //lance un cycle de coneversion
    while (ADCON0bits.GO); //tant que la conversion est encore en cours
    return ADRESH ; //retourne les 8bits de poid fort d'une conversion 10bits //le bit adfm est de base à 0
}

void init_led(void){
    TRISC = 0b00000000;
    PORTC = 0b00000000;
    //rajouter les autres led je ne sais plus ou elles sont connecté
}

void init_uart(){
// calcul de la valeur de spbrg: (Fosc-baud*16)/baud*16
    
TXSTA1 = 0; // Reset USART registers to POR state
RCSTA1 = 0;

TRISCbits.TRISC6 = 1; //TX1 //voir datasheet pour expliquer
TRISCbits.TRISC7 = 1; //RX1


TXSTA1bits.BRGH = 1; //high speed
BAUDCON1bits.BRG16 = 0; //8bit asynchronous

ANSC7 = 0; /// Pour le PIC18f45k22
ANSC6 = 0; /// Pour le PIC18f45k22
SPBRG1 = 10; //baud rate vaut : Fosc/[(SPBRG1 + 1)* 16] = 57000 bps

RCSTA1bits.CREN = 1; //enble receiver
RCSTA1bits.RX9 = 1; //enable 9-bit reception
RCSTA1bits.ADDEN = 1; //Enables address detection, enable interrupt and load the receive buffer when RSR<8> is set (RX9 set)

TXSTA1bits.TX9 = 1; //enable 9-bit transmission
TXSTA1bits.TXEN = 1; //enble transmitter
TXSTA1bits.SYNC = 0; //asynchronous mode
RCSTA1bits.SPEN = 1; //serial port enable bit


}  

void write_uart (unsigned char *carac){
    while(*carac){
        while(!TXSTA1.TRMT){ //on attend que le buffer soit vvide donc que le message d'avant soit envoye
            TXREG1 = *carac++;
        }
    }
} 
 
char read_uart (){
    while(!PIR1bits.RC1IF);
    return RCREG1;
}