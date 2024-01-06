#include <stdio.h>
#include <stdlib.h>

// GPIO bits
const int ON = 1;
const int OFF = 0;
const int BUTTON_ON = 0x80000000;  // x30[31] =1
const int BUTTON_OFF = 0x00000000; // x30[31] =0

// Function prototypes
void setBuzzer(int GPIO_buzz_bit);
int readBuzzer();
int readButton();
void setButton(int GPIO_button_bit);

int main() {
  int button_state = 0; // Store button state
  int i;                // Loop counter
  int seconds = 1;      // Delay time
  int set_button_state = 0;

  while (1) {
    // Continuously read the button state
    button_state = readButton();

    // If button is pressed, turn on the buzzer
    if (button_state == ON) {
      setBuzzer(ON);
      printf("Doorbell activated! Buzzer on.\n");
    } else {
      // If button is not pressed, turn off the buzzer
      setBuzzer(OFF);
    }

    // Delay to avoid excessive button readings
    for (i = 0; i < seconds * 1000000; i++) {
      asm("nop");
    }

    // Randomly set the button state
    set_button_state = random() % 2;
    printf("Button state: %d\n", set_button_state);
    if (set_button_state == 1) {
      setButton(BUTTON_ON);
    } else {
      setButton(BUTTON_OFF);
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

int readBuzzer() {
  int buzzer; // read whether buzzer is on or off
  asm volatile("andi %0, x30, 0x0001\n\t" : "=r"(buzzer) : :);
  return buzzer;
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

void setButton(int GPIO_button_bit) {
  int mask = 0x7FFFFFFF; // preserve all bits except x30[31] - set to 0
  asm volatile("and x30,x30, %1\n\t"
               "or x30,x30, %0\n\t"
               :
               : "r"(GPIO_button_bit), "r"(mask)
               : "x30" // clobber list,indicating that x30 is modified
  );
}
