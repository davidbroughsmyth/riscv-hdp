### Blinky IOT
Display a pattern on 16 leds. The pattern changes when the display waveform button is pressed.

#### Block Diagram
![image](../../images/blinky_bd.png)

#### Blinky Schematic
![image](../../images/riscv_blinky.png)

#### x30 GPIO allocation
Output:

x30[15:0] - 16 display leds: active high

Input:

x30[31] - toggle mode button: pulse length 100ms

#### C code
1. blinky_test.c - app for testing the GPIO x30 registor
1. blinky.c - stripped for verilog generation

``` C
// #include <stdio.h>
// #include <stdlib.h>

// GPIO bits
const int ON = 1;
const int OFF = 0;
```

#### Instructions used
```
```
#### Testing app via x30 GPIO bits 
![image](../../images/blinky_test.png)
