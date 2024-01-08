#include <stdio.h>

// GPIO bits
const int BUZZ_ON = 1;             // x30[0] =1
const int BUZZ_OFF = 0;            // x30[0] =0
const int BUTTON_ON = 0x80000000;  // x30[31] =1
const int BUTTON_OFF = 0x00000000; // x30[31] =0

// Function prototypes
void setBuzzer(int GPIO_buzz_bit);
int readBuzzer();
int readButton();
void setButton(int GPIO_button_bit);

int main() {
  int x30_value = 0xC0000000;
  int button = 0;

  // Read the current value of x30 register
  asm volatile("addi %0, x30, 0\n\t" : "=r"(x30_value) : :);
  printf("Powerup state of x30 register = %x\n\n", x30_value);

  // Button on x30[31]
  setButton(BUTTON_ON);
  asm volatile("addi %0, x30, 0\n\t" : "=r"(x30_value) : :); // read x30
  printf("Button on x30[31]: Current state of x30 register = %x\n\n",
         x30_value);

  // Read the current value of button x30[31]
  button = readButton();
  printf("Button on x30[31] register = %x\n\n", button);

  for (int i = 0; i < 8; i++) {

    // Set output to x30[0]
    printf("Set buzzer output x30[0]: ");
    setBuzzer(i);

    // Read the current value of x30 register
    asm volatile("addi %0, x30, 0\n\t" : "=r"(x30_value) : :); // read x30
    printf("Current state of x30 register = %x\n\n", x30_value);

    // Read buzzer data into x30[0]
    // asm volatile("andi %0, x30, 0x0001\n\t" : "=r"(x30_value) : :);
    x30_value = readBuzzer();
    printf("Read x30[0] sensor data to mem = %x\n\n", x30_value);

    // Read buzzer data into x30[8] .. x30[0]
    asm volatile("andi %0, x30, 0x00FF\n\t" : "=r"(x30_value) : :);
    printf("Read x30[8] .. x30[0] sensor data to mem = %x\n\n", x30_value);

    // Read the current value of x30 register
    asm volatile("addi %0, x30, 0\n\t" : "=r"(x30_value) : :);
    printf("Current state of x30 register = %x\n\n", x30_value);
  }

  // Button off x30[31]
  setButton(BUTTON_OFF);
  asm volatile("addi %0, x30, 0\n\t" : "=r"(x30_value) : :); // read x30
  printf("Button off x30[31]: Current state of x30 register = %x\n\n",
         x30_value);

  // Read the current value of button x30[31]
  button = readButton();

  printf("Button off x30[31] register = %x\n\n", button);

  // Button off x30[31]
  setButton(BUTTON_ON);
  asm volatile("addi %0, x30, 0\n\t" : "=r"(x30_value) : :); // read x30
  printf("Button on x30[31]: Current state of x30 register = %x\n\n",
         x30_value);

  // Read the current value of button x30[31]
  button = readButton();

  printf("Button on x30[31] register = %x\n\n", button);

  // Button on x30[31]
  setButton(BUTTON_OFF);
  asm volatile("addi %0, x30, 0\n\t" : "=r"(x30_value) : :); // read x30
  printf("Button off x30[31]: Current state of x30 register = %x\n\n",
         x30_value);

  // Read the current value of button x30[31]
  button = readButton();

  printf("Button off x30[31] register = %x\n\n", button);
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
