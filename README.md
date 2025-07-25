# STM32 Nucleo-G0B1RE advanced timer control test code

**MIT license**

This project is for testing a way to get narrow pulses from timers in the STM32G0 series of microcontrollers.

This refactored version is using `OC1M[3:0] = 1101` which is **Combined PWM mode 2** in which the `OC1REFC`
timer output signal is the logical AND between the `OC1REF` and `OC2REF` signals. Thus the `CCR1` register
defines the time of the rising edge and the `CCR3` register defines the falling edge, while the `ARR` 
register still defines the overall period. This allows both the pulse position and pulse width to be 
controlled within the period. Similarly, the `CCR3` and `CCR4` registers can be used in the same manner
to control a second independent strobe from the same timer.

```
Combined PWM mode 2:

         +---------+
CH1      |         |
     +---+         +---------------------+
     0  CCR1      CCR2                  ARR

                         +---------+
CH3                      |         |
     +-------------------+         +-----+
     0                  CCR3      CCR4  ARR
```
