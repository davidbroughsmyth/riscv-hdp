### Doorbell IOT
Very basic doorbell with one button to activate a bell

#### Block Diagram
![image](../../images/riscv_doorbell_bd.png)

#### Doorbell Schematic
![image](../../images/riscv_doorbell.png)

#### x30 GPIO allocation
Output:

x30[0] - enable buzzer sound: active high

Input:

x30[31] - detect button signal: active high

#### C code
1. doorbell_concept.c - original thinking
1. doorbell_test.c - app for testing the GPIO x30 registor
1. doorbell.c - stripped for verilog generation

``` C
// #include <stdio.h>
// #include <stdlib.h>

// GPIO bits
const int ON = 1;
const int OFF = 0;

// Function prototypes
void setBuzzer(int GPIO_buzz_bit);
int readButton();

int main() {
  int button_state = 0; // Store button state
  int i;                // Loop counter
  int seconds = 1;      // Delay time

  while (1) {
    // Continuously read the button state
    button_state = readButton();

    // If button is pressed, turn on the buzzer
    if (button_state == ON) {
      setBuzzer(ON);
      // printf("Doorbell activated! Buzzer on.\n");
    } else {
      // If button is not pressed, turn off the buzzer
      setBuzzer(OFF);
      // printf("Doorbell deactivated! Buzzer off.\n");
    }

    // Delay to avoid excessive button readings
    for (i = 0; i < seconds * 1000000; i++) {
      asm("nop");
    }
  }

  return 0;
}

// Function definitions =====================================================

void setBuzzer(int GPIO_buzz_bit) {
  int mask = 0xFFFFFFFE; // preserve all bits except x30[0] - set to 0
  asm volatile("and x30,x30, %1\n\t"
               "or x30,x30, %0\n\t"
               :
               : "r"(GPIO_buzz_bit), "r"(mask)
               : "x30" // clobber list,indicating that x30 is modified
  );
}

int readButton() {
  int button_press; // read whether is pressed or not
  asm volatile("srli x10, x30, 31\n\t"
               "andi %0, x10, 1\n\t"
               : "=r"(button_press)
               :
               : "x10");
  return button_press;
}

```

#### Instructions used
```
Total Number of instructions    : 64
Chipcron pc_bit_width config    : 7
Number of different instructions: 16
List of unique instructions:
or
bne
mv
blt
srl
sw
sll
lw
ret
li
j
nop
sub
jal
and
add
```
#### Testing app via x30 GPIO bits 
![image](../../images/doorbell_test.png)

#### Verilog generation 
Unmodified ChipCron processor.v and testbench.v doing a verilog run. This tests out the doorbell program loading from the uart.
```
```
![image](../../images/doorbell_verilog_run1.png)
![image](../../images/doorbell_verilog_run2.png)

-- running simulator with -fst flag to compress the .vcd file as the native file waveform can get very large. A smaller .vcd helps gtkwave to load faster. 
```
```
![image](../../images/doorbell_run_fst.png)
