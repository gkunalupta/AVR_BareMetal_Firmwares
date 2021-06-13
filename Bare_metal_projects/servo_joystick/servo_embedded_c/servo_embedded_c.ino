    #include <avr/io.h>
                  #include <util/delay.h>
                  #include <avr/interrupt.h>
                  
                  

                  #define PULSE_MIN         10000         /* experiment with these values */
                  #define PULSE_MAX         20000              /* to match your own servo */
                  #define PULSE_MID         15000

                  static inline uint16_t getNumber16(void);

                  static inline void initTimer1Servo(void) {
                    /* Set up Timer1 (16bit) to give a pulse every 20ms */
                    /* Use Fast PWM mode, counter max in ICR1 */
                    TCCR1A |= (1 << WGM11);
                    TCCR1B |= (1 << WGM12) | (1 << WGM13);
                    TCCR1B |= (1 << CS11);  /* /8 prescaling -- counting in microseconds */
                    ICR1 = 40000;                                    /* TOP value = 20ms */
                    TCCR1A |= (1 << COM1A1)|(1<<COM1B1);              /* Direct output on PB1 / OC1A */
                    DDRB |= (1 << PB2)|(1<<PB6)|(1<<PB1);                            /* set pin for output */
                  }

                
                  int main(void) 
          {  

                    // -------- Inits --------- //
                    uint16_t servoPulseLength;
                    OCR1A = PULSE_MIN;            /* set it to middle position initially */
                    initTimer1Servo();
                    
          
            OCR1B=2000;
          OCR1A=3000;
          
          
         // OCR1B=2700;
         // OCR1A=2000;
          
          }
          
