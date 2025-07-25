# STM32 Nucleo-G0B1RE Advanced-control Timer (TIM1) test code

**MIT license**

This project is for testing a way to get narrow pulses from timers in the STM32G0 series of microcontroller.

This refactored version is usng `OC1M[3:0] = 1101` which is **Combined PWM mode 2** in which `OC1REFC` is
the logical AND between `OC1REF` and `OC2REF`. Thus the `CCR1` register defines the time of the rising 
edge and the `CCR3` register defines the falling edge, while the `ARR` rgister still defines the overall
period. This allows the pulse position and with to be controlled with fine granularity.  The
`CCR2` and `CCR4` registers can be used in the same manner to control two independent strobes from one
timer.

```
         +---------+
         |         |
  +------+         +---------------------------+
  0     CCR1      CCR3                        ARR

                            +---------+
                            |         |
  +-------------------------+         +--------+
  0                        CCR2      CCR4     ARR
```
