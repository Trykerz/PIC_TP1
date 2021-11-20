#include "adc.h"


int main(void)
{
    uint8_t  j; // buffer qui va stocker la conversion adc
    Adc_init();
    init_led();
    while(1){
       j = conv();
       PORTC = 0b00001111 & j; //masquage avec les leds modifier aussi init_led
    }
   
}