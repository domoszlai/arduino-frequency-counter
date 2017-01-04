/*
  Attiny (except Attiny13) frequency counter using a Pin-Change Interrupt. It uses Timer1 for gate time generation.
  Supposed to count relatively low frequencies (tested with ~60KHz, with Attiny85).
  
  Copyright (c) 2017 dlacko

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
 */

#ifndef FREQUENCY_COUNTER_ATTINY_H_
#define FREQUENCY_COUNTER_ATTINY_H_

/*
 * Counts pulses synchronously (blocking) on the given pin and calculate frequency. Gate time is 100ms.
 * For the pin, it is supposed that there is an associated Pin-Change Interrupt (all the pins on Attiny85)
 */
unsigned long count_frequency(uint8_t pin);

#endif  // FREQUENCY_COUNTER_ATTINY_H_ 

