#include <Arduino.h>

volatile unsigned long _freq;
// pulse counter update by the counter_interrupt() interrupt handler
volatile unsigned long _pulseCount;
// tick counter for gate time  measurement
volatile unsigned int _tickCount;
volatile uint8_t _ready; // becomes 1 when gate time is elapsed 

#if F_CPU == 16000000 
  #define GATETIME_CLICKS 50
#elif F_CPU == 8000000
  #define GATETIME_CLICKS 25
#endif

void counter_interrupt()
{
  _pulseCount++;
}

unsigned long count_frequency(uint8_t pin)
{
  attachInterrupt(digitalPinToInterrupt(pin), counter_interrupt, RISING);

  noInterrupts();
  
  _tickCount = 0;
  _pulseCount = 0;
  _ready = 0;
           
  // Set up Timer2 for gate time measurement. Prescaler: 256
  TCCR2B &= ~_BV(CS20);
  TCCR2B |= _BV(CS21);
  TCCR2B |= _BV(CS22);

  // CTC Mode
  TCCR2A &= ~_BV(WGM20);
  TCCR2A |= _BV(WGM21);
  TCCR2A &= ~_BV(WGM22);
  
  OCR2A = 124;                  // 2ms on 16MHz, prescaler 256 (4 ms on 8MHz)

  TIMSK2 |= _BV(OCIE2A);        // enable Timer2 Interrupt

  GTCCR |= _BV(PSRASY);         // reset prescaler counting
  TCNT2 = 0;                    // Counter2 = 0
  interrupts();    

  while(_ready == 0){}          // Wait for gate time

  detachInterrupt(pin);
  
  return _freq;
}

ISR(TIMER2_COMPA_vect) 
{
  if (_tickCount == GATETIME_CLICKS) 
  {
    _freq = _pulseCount * 10;   // based on 100ms
    _ready = 1;

    TIMSK2 &= ~_BV(OCIE2A);     // disable Timer2 Interrupt
  }

  _tickCount++;
}


