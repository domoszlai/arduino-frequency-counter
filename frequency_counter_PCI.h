/*
  Frequency counting using a Pin-Change Interrupt. It uses Timer2 for gate time generation.
  It should work with most Arduinos for all the pins that has an interrupt attached, but use 
  it for counting relatively low frequencies only. If you need to count frequencies on the MHz scale, 
  use the hardware counter based version.
  
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

#ifndef FREQUENCY_COUNTER_PCI_H_
#define FREQUENCY_COUNTER_PCI_H_

/*
 * Counts pulses synchronously (blocking) on the given pin and calculate frequency. Gate time is 100ms.
 * For the pin, it is supposed that there is an associated Pin-Change Interrupt.
 */
unsigned long count_frequency(uint8_t pin);

#endif  // FREQUENCY_COUNTER_PCI_H_ 

