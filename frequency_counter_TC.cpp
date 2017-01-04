#include <Arduino.h>

volatile unsigned long _freq;
// tick counter for gate time  measurement
volatile unsigned int _tickCount;
// counter overflow counter. counter is 16 bit
volatile unsigned int _overflowCount;
volatile uint8_t _ready; // becomes 1 when gate time is elapsed

#if F_CPU == 16000000 
  #define GATETIME_CLICKS 50
#elif F_CPU == 8000000
  #define GATETIME_CLICKS 25
#endif

unsigned long count_frequency()
{
  noInterrupts();

  _overflowCount = 0;
  _tickCount = 0;
  _ready = 0;

#if defined(__AVR_ATmega2560__)
  // Set up Timer/Counter5 for counting
  TCCR5A = 0;                   
  TCCR5B = 0;                   
  TCNT5 = 0;                    // Counter5 = 0                
  
  // External clock source on T1 pin. Clock on rising edge.  
  TCCR5B |= _BV(CS50) | _BV(CS51) | _BV(CS52);         
#else
  // Set up Timer/Counter1 for counting
  TCCR1A = 0;                   
  TCCR1B = 0;                   
  TCNT1 = 0;                    // Counter1 = 0                
  
  // External clock source on T1 pin. Clock on rising edge.  
  TCCR1B |= _BV(CS10) | _BV(CS11) | _BV(CS12);         
#endif
           
  // Set up Timer2 for gate time measurement. Prescaler: 256
  TCCR2B &= ~_BV(CS20);
  TCCR2B |= _BV(CS21);
  TCCR2B |= _BV(CS22);

  // CTC Mode
  TCCR2A &= ~_BV(WGM20);
  TCCR2A |= _BV(WGM21);
  TCCR2A &= ~_BV(WGM22);
  
  OCR2A = 124;                  // 2ms on 16MHz, prescaler 256 (4 ms on 8MHz)

  GTCCR |= _BV(PSRASY);         // reset prescaler counting
  TCNT2 = 0;                    // Counter2 = 0

  TIMSK2 |= _BV(OCIE2A);        // enable Timer2 Interrupt
  
#if defined(__AVR_ATmega2560__)
  // enable Timer/Counter5: increment timer 5 on T5 Pin rising edge
  TCCR5B |= _BV(CS50) | _BV(CS51) | _BV(CS52);          
#else
  // enable Timer/Counter1: increment timer 1 on T1 Pin rising edge
  TCCR1B |= _BV(CS10) | _BV(CS11) | _BV(CS12);          
#endif  
  interrupts();    

  while(_ready == 0){}          // Wait for gate time
  
  return _freq;
}

#if defined(__AVR_ATmega2560__)

ISR(TIMER2_COMPA_vect) 
{
  if (_tickCount == GATETIME_CLICKS) 
  {
    _freq = (_overflowCount * 0x10000 + TCNT5) * 10;   // based on 100ms
    _ready = 1;

    // disable Timer/Counter5
    TCCR5B &= ~_BV(CS50) & ~_BV(CS51) & ~_BV(CS51);       
    TIMSK2 &= ~_BV(OCIE2A);     // disable Timer2 Interrupt
  }

  _tickCount++;

  if (TIFR5 & 1) {              // Check Timer/Counter5 overflow flag
    _overflowCount++;                  
    TIFR5 &= _BV(TOV5);         // Clear overflow flag
  }
}

#else

ISR(TIMER2_COMPA_vect) 
{
  if (_tickCount == GATETIME_CLICKS) 
  {
    _freq = (_overflowCount * 0x10000 + TCNT1) * 10;   // based on 100ms
    _ready = 1;

    // disable Timer/Counter1
    TCCR1B &= ~_BV(CS10) & ~_BV(CS11) & ~_BV(CS11);       
    TIMSK2 &= ~_BV(OCIE2A);     // disable Timer2 Interrupt
  }

  _tickCount++;

  if (TIFR1 & 1) {              // Check Timer/Counter1 overflow flag
    _overflowCount++;                  
    TIFR1 &= _BV(TOV1);         // Clear overflow flag
  }
}

#endif

