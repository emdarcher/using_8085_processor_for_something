

#include "main.h"
#include "uart.h"

/* defines */

#define EXT_MEM_SIZE_BYTES 8192

/* set to the address at the start of external memory
 * in the memory map. Make sure to check your microcontroller's
 * datasheet for this value.*/
#define EXT_MEM_START_ADDR 0x0260
#define EXT_MEM_END_ADDR (EXT_MEM_START_ADDR + EXT_MEM_SIZE_BYTES)

#define EXT_MEM_LOAD_ARRAY_SIZE_BYTES 256

#if 0
const PROGMEM uint8_t[EXT_MEM_LOAD_ARRAY_SIZE_BYTES] = {

};
#endif

uint8_t * ext_mem_ptr;
uint8_t ext_mem_error;
/* function prototypes */
static inline void init_ext_mem(void);


int main(void){

    /* init stuff */
    DDRB |= (1<<PD1); //TX pin init to output
    DDRE |= (1<<PE2); //debug LED
            PORTE |= (1<<PE2);
    uart0_init(UART_BAUD_SELECT(BAUD, F_CPU));
    
    init_ext_mem(); 
    
    ext_mem_ptr = (uint8_t *)(EXT_MEM_START_ADDR);
    uint8_t loop_addr_index = 255;
    while(loop_addr_index--){
        //load memory locations 0-255 with numbers 0-255 
        ext_mem_ptr[loop_addr_index] = loop_addr_index;
    }

            //PORTE &= ~(1<<PE2);
    //loop_addr_index--;//overflow the variable back to 255
    loop_addr_index = 255;
    #if 1
    while(loop_addr_index--){
        if(ext_mem_ptr[loop_addr_index] != loop_addr_index){
            ext_mem_error=1;
            uart0_puts_p(PSTR("memory mismatch error!\n\r")); 
            break;
        } 
        PORTE ^= (1<<PE2);
    }
    #endif
    if(!ext_mem_error){
        
        uart0_puts_p(PSTR("memory matched!\n\r"));
    }
            PORTE &= ~(1<<PE2);
    sei(); 
    /* infinite loop */
    while(1){
        PORTE |= (1<<PE2);
        if(!ext_mem_error){
            //uart0_puts_p(PSTR("memory mismatch error!\n\r"));
            _delay_ms(500);
            PORTE &= ~(1<<PE2);
            _delay_ms(500);
        }
    }
}

/* function bodies */
static inline void init_ext_mem(void){
    DDRD |= ((1<<PD6)|(1<<PD7));
    MCUCR |= (1<<SRE); //enable external memory
}


/* Interrupt Service Routines */



