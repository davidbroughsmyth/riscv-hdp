### IOT Apps
1. ZeroRV and NopRV - does nothing but has the smallest cpu footprint
1. Doorbell - rings a bell when a button is pushed
1. Blinky - displays a pattern on leds
1. Secure code doorlock - tamper proof door locking/unlocking 

#### Future Apps
1. Serial uart echo
1. Serial uart monitor
1. Riscv machine code monitor - over serial
1. Riscv machine code monitor with Wifi - serial to Wifi 
1. Stress and vibration IOT monitor - datalogger with pattern recognition
1. Stress and vibration IOT monitor with a Verlog Neuromorphic module - enable AI edge decision making


#### Utility programs
*cpusage.py* extracts and displays the unique assembly inctructions from a assembly file, the lines of code and calculates the pc_bit_width for Chipcron verilog generation
```
python3 cpusage.py -h
cpusage.py -i <inputfile> -o <outputfile>
flags: -ci or -c -i to count instructions, -h this help
``` 
