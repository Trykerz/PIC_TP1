#include "def.h"

void init_timer(){
    T0CONbits.T0PS = 0b111;  //prescaler 1:16
    T0CONbits.PSA = 0; //enable prescaler
    T0CONbits.T0CS = 0; //internal clock
    T0CONbits.T08BIT = 1; //timer 16bit
    //INTCONbits.TMR0IE = 0; //disable overflow interrupt
    T0CONbits.TMR0ON = 1;//enable timer0
    
    //gestion interupt
    INTCONbits.TMR0IE = 1; //enable overflow interupt
    RCONbits.IPEN = 0; //disable interrupt priority
    INTCONbits.GIE = 1; //enable all interrupt
    INTCONbits.PEIE = 1; //Peripheral Interrupt Enable
}

/*
void interrupt isr(){
    
    if (INTCONbits.TMR0IF && INTCONbits.TMR0IE){
        INTCONbits.TMR0IF = 0;
        TMR0L = 0;
        i = !i;
    }
}
*/

/*
void interrupt isr(){
    
    if (INTCONbits.TMR0IF && INTCONbits.TMR0IE){
        INTCONbits.TMR0IF = 0;
        TMR0L = 0;
        j = j << 1;
        if(j == 0b00010000){
            j=0b00000001;
        }
        
    }
}*/

void interrupt isr(){
    if (INTCONbits.TMR0IF && INTCONbits.TMR0IE){
        INTCONbits.TMR0IF = 0;
        TMR0L = 0;
        flag = 1;
        }  
    }
