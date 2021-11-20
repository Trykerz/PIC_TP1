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

void init_uart( unsigned int baud){

 TXSTA1 = 0; // Reset USART registers to POR state
 RCSTA1 = 0;
 //calcul bad-rate 
 int N;
 N = ((10000000 - baud*64)/(baud*64));
 SPBRG1 = N; //init baudrate
 TXSTA1bits.BRGH = 0; //low speed
 BAUDCON1bits.BRG16 = 0; //8bit asynchronous 
 TXSTA1bits.SYNC = 0; //asynchronous mode
 RCSTA1bits.SPEN = 1; //enble eusart and enable TX as output
 
 
 RCSTA1bits.CREN = 1; //enble receiver
 RCSTA1bits.RX9 = 0; //8bit reception
 ANSC7 = 0; /// Pour le PIC18f45k22
 ANSC6 = 0; /// Pour le PIC18f45k22

 TXSTA1bits.TXEN = 1; //enble transmitter
 TRISCbits.TRISC6 = 1; //tx
 TRISCbits.TRISC7 = 1; //rx
 }