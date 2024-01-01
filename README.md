# STM32 Nucleo-G0B1RE Advanced-control Timer (TIM1) test code

This project is for testing and debugging the output compare toggle mode of TIM1 in the STM32G0 series of microcontroller.
Toggle mode is set with `OCxM=0011` for x=1 to 4 in the `TIM1_CCMR1` and `TIM1_CCMR2` registers.
Interrupts are used to modify the value in the Capture/Compare Register to create  
staggered 100us pulses on each of TIM1_CH1 through TIM1_CH4. 
The timing was validated using an oscilloscope.

I confirmed that the toggle mode really does toggle. 
It does not start in a fixed state on each count up cycle. 
This could be a problem if the timer is stopped as part of a safety fault and later restarted.

I added a saftey check by reading the GPIO pin in the interrupts.
If the TIM1_CHx output is in the wrong state, a `polarity_fault` flag is set for the main-line code to handle.

**MIT license**

