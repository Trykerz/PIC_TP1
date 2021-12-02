#include <p18f45K22.h>
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 8000000 // On définit la valeur d'une variable globale à _XTAL_FREQ à 10000000

#pragma config FOSC = HSMP
#pragma config FCMEN = OFF
#pragma config WDTEN = OFF
#pragma config XINST = OFF

#pragma config LVP = OFF

unsigned char i;
unsigned char j;
unsigned char flag;


void init_timer();

void interrupt isr();

void Adc_init(void);
float conv();
void init_led(void);

void init_uart();
void write_uart (unsigned char);
char read_uart ();


void init_rfid();

char echo();
void write_echo();
char read_echo();