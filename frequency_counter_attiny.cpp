#include <Arduino.h>

volatile unsigned long _freq;
// pulse counter update by the counter_interrupt() interrupt handler
volatile unsigned long _pulseCount;
// tick counter for gate time  measurement
volatile unsigned int _tickCount;
volatile uint8_t _ready; // becomes 1 when gate time is elapsed

#if F_CPU == 20000000
#define GATETIME_CLICKS 1000
#elif F_CPU == 16000000
#define GATETIME_CLICKS 800
#else
#define GATETIME_CLICKS 400
#endif

ISR(PCINT0_vect)
{
  _pulseCount++;
}

unsigned long count_frequency(uint8_t pin)
{
  noInterrupts();

  _tickCount = 0;
  _pulseCount = 0;
  _ready = 0;

  GIMSK = 0b00100000;
  PCMSK |= _BV(pin);

  // Set up Timer1 for gate time measurement.
  TCCR1 = _BV(CTC1);            // CTC mode

#if F_CPU == 20000000 || F_CPU == 16000000 || F_CPU == 8000000
  TCCR1 |= _BV(CS12);           // prescale: 8
#elif F_CPU == 1000000
  TCCR1 |= _BV(CS10);           // no prescale
#endif

  OCR1C = 250;
  TIMSK |= _BV(OCIE1A);         // enable Timer1 interrupt
  interrupts();

  while (_ready == 0) {}        // Wait for gate time

  PCMSK = 0;
  GIMSK = 0;

  return _freq; 
}

ISR(TIM1_COMPA_vect)
{
  if (_tickCount == GATETIME_CLICKS)
  {
    // On ATTtiny, PCI is triggered on both rising and falling edge,
    // use only half of the pulseCount      
      
    _freq = _pulseCount * 5;    // based on 100ms
    _ready = 1;

    TIMSK &= ~_BV(OCIE1A);      // disable Timer1 Interrupt
  }

  _tickCount++;
}



