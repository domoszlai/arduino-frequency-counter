## Synopsis

Frequency counter experiments with Arduino. The library implements two different approaches for reliable frequency counting
and an ATTiny version. For more details visit [this blog post](http://dlacko.blogspot.nl/2017/01/arduino-frequency-counter-experiments.html)

## Implementations

* frequency_counter_PCI.cpp: counting with Pin-Change Interrupt

This method uses one timer for gate time measurement and a pin-change interrupt (PCI) for counting the pulses. 
It is very generally usable as pin-change interrupts are available for many/most pins, but it may work well for lower frequencies only (it worked perfectly with ~60KHz in my tests).

* frequency_counter_attiny.cpp: counting on ATTiny

The Pin-Change Interrupt based method ported to ATTiny. It should work on all of the ATTiny chips, except ATTiny13.

* frequency_counter_TC.cpp: counting with a hardware timer/counter

This the most reliable method that (supposedly) works for up to several MHz. It uses one timer for gate time measurement and a hardware timer/counter (TC) for counting the pulses. 
However, the hardware counter requires the usage of one specific pin, what can be very impractical in some situations. It must be the T1 pin (usually pin 5) for most boards, 
but T5 (pin 47) in the case of an Arduino Mega.


 

