/*
  Frequency counting using a Timer Counter (Timer5 on MEGA and Timer1 otherwise). It uses Timer2 for gate time generation.
  It works on the T1 (T5 on Mega) pin only, but for high frequencies (up to 4MHz). 
  (On Mega T1 is used inside the chip, we have to use T5 instead)

  For the implementation I used this source: 
  http://interface.khm.de/index.php/lab/interfaces-advanced/theremin-as-a-capacitive-sensing-device/
  
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

#ifndef FREQUENCY_COUNTER_TC_H_
#define FREQUENCY_COUNTER_TC_H_

/*
 * Counts pulses synchronously (blocking) on pin T1 (T5 on Mega) and calculate frequency. Gate time is 100ms.
 * T1 is pin5 on Uno, T5 is pin 47 on Mega
 */
unsigned long count_frequency();

#endif  // FREQUENCY_COUNTER_TC_H_ 

