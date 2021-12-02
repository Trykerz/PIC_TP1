//#include "uart.h"
#include "def.h"

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

TRISCbits.TRISC6 = 1; //TX1 //voir datasheet pour expliquer For all modes of EUSART operation, the TRIS control
//bits corresponding to the RXx/DTx and TXx/CKx pins
//should be set to ?1?. The EUSART control will
//automatically reconfigure the pin from input to output, as
//needed.  p260
TRISCbits.TRISC7 = 1; //RX1


TXSTA1bits.BRGH = 1; //high speed
BAUDCON1bits.BRG16 = 0; //8bit asynchronous

ANSC7 = 0; /// Pour le PIC18f45k22
ANSC6 = 0; /// Pour le PIC18f45k22
SPBRG1 = 8; //baud rate vaut : Fosc/[(SPBRG1 + 1)* 16] = 10417 bps (Fosc = 8MHz) (cf tableau p.274) (test avec 8, anciennement 47)

RCSTA1bits.CREN = 1; //enable receiver
//RCSTA1bits.RX9 = 1; //enable 9-bit reception
RCSTA1bits.ADDEN = 0; //desables address detection, enable interrupt and load the receive buffer when RSR<8> is set (RX9 set)

//TXSTA1bits.TX9 = 1; //enable 9-bit transmission
TXSTA1bits.TXEN = 1; //enble transmitter
TXSTA1bits.SYNC = 0; //asynchronous mode
RCSTA1bits.SPEN = 1; //serial port enable bit


}  

void write_uart (unsigned char carac){
    while(!PIR1bits.TX1IF); //on attend que le buffer soit vide donc que le message d'avant soit envoye
        TXREG1 = carac;
       }

char read_uart (){
    while(!PIR1bits.RC1IF);
    return RCREG1;
}

void init_rfid(){
    //On utilise notre liaison uart pour init le rfid 1bit  à notre baud rate equivaut à 100us
    //on reste à 0 pendant 700us puis on passe à 1 pendant 200us 
    //si on avait init en utilisant trisc il aurait fallut init lme rfid avant l'uart.
    //write_uart(0b10000000);
    
    RCSTA1bits.SPEN = 0;
    TXSTA1bits.TXEN = 0;
    TRISCbits.TRISC6 = 0;
    PORTCbits.RC6 = 1;
    __delay_us(200);
    PORTCbits.RC6 = 0;
    __delay_us(100);
     PORTCbits.RC6 = 1;
    __delay_us(200);
}

char echo(){
   unsigned char v;      
   flag = 0;
   write_echo();
   if(read_echo() == 0x55){
       return 1;
   }
   //cas d'une interruption
   return 0;      
}

char read_echo(){
    while(!PIR1bits.RC1IF && !flag); // flag passe a 1 quand le timer dépasse la valeur voulue
    return RCREG1;
}

void write_echo(){
    write_uart(0x55);
}