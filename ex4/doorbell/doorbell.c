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
      asm volatile("nop");
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
  int button_press; // read whether it is pressed or not
  asm volatile("srli x10, x30, 31\n\t"
               "andi %0, x10, 1\n\t"
               : "=r"(button_press)
               :
               : "x10");
  return button_press;
}
