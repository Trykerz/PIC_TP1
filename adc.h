#include <p18f45K22.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#define _XTAL_FREQ 10000000 // On d?finit la valeur d'une variable globale ? _XTAL_FREQ ? 10000000

#pragma config FOSC = HSMP
#pragma config FCMEN = OFF
#pragma config WDTEN = OFF
#pragma config XINST = OFF

#pragma config LVP = OFF


void Adc_init(void);
float conv();
void init_led(void);

void init_uart( unsigned int baud);
void write_uart (unsigned char *carac);
char read_uart ();