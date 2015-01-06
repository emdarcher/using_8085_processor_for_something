
#include "main.h"

/* defines */

/* function prototypes */

void main(void){

    /* init stuff */
    DDRE |= (1<<PE2);    
    /* infinite loop */
    while(1){
       PORTE ^= (1<<PE2);
        _delay_ms(500); 
    }
}

/* function bodies */



/* Interrupt Service Routines */



