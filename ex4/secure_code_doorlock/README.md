### Secure code doorlock IOT
Secure code doorlock with tamper proof door locking/unlocking. Inputs are 1. tamper switch 2. keypad. Output are 1. lock led 2. lock/unlock buzzer 3. doorlock solenoid 

#### Block Diagram
![image](../../images/doorlock_bd.png)

#### Secure code doorlock Schematic
![image](../../images/riscv_doorlock.png)

#### x30 GPIO allocation
Output:

x30[0] - lock led
x30[1] - lock/unlock audio beep
x30[3] - doorlock solenoid enable/disable

Input:

x30[31] - tamper switch
x30[8:4] - keypad code 

#### C code
1. doorlock_test.c - app for testing the GPIO x30 registor
1. doorlock.c - stripped for verilog generation

-- Secure code doorlock test
``` C
```

#### Instructions used
```
```
#### Testing app via x30 GPIO bits 
![image](../../images/doorlock_test.png)
