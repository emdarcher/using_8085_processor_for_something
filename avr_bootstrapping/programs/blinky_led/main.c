
#include "main.h"

/* defines */

/* function prototypes */

int main(void){

    /* init stuff */
    DDRE |= (uint8_t)(1<<PE2);    
    /* infinite loop */
    while(1){
       PORTE ^= (uint8_t)(1<<PE2);
        _delay_ms(500); 
    }
}

/* function bodies */



/* Interrupt Service Routines */



