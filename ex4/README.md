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
### Tooling for Verilog generation, simulation and synthesis, FPGA programming, and ASIC design

#### Yosys (VM install): https://github.com/YosysHQ/yosys
Installing Yosys on the vsdworkshop VM. Install the latest by entering the following commands in the terminal:
```
apt install build-essential clang bison flex libreadline-dev \
    gawk tcl-dev libffi-dev git graphviz \
    xdot pkg-config python python3 libftdi-dev \
    qt5-default python3-dev libboost-all-dev cmake libeigen3-dev

git clone https://github.com/YosysHQ/yosys yosys
cd yosys
make -j$(nproc)
make install
```

#### OSS CAD Suite MacOS M1/2: https://github.com/YosysHQ/oss-cad-suite-build
Download the latest release from https://github.com/YosysHQ/oss-cad-suite-build/releases/latest

It has many tools including yosys, ABC, nextpnr, icestorm, iverilog, verilator, gtkwave
```
xattr -d com.apple.quarantine oss-cad-suite-darwin-x64-yyymmdd.tgz
source <extracted_location>/oss-cad-suite/environment
yosys -V
```

#### Openlane MacOS M1/2: https://github.com/The-OpenROAD-Project/OpenLane
Has many tools including yosys, Magic, klayout and OpenROAD
Installing Openlane on a M2 mac. Install the latest by entering the following commands in the terminal:
```
cd $HOME
git clone https://github.com/The-OpenROAD-Project/OpenLane
cd OpenLane
make
make test
```

Testing klayout with sky130 technology, ensure XQuartz is installed and running, see https://www.xquartz.org or https://github.com/XQuartz/XQuartz

Run the following command in a terminal first:
```
xhost +localhost
```

Then run the following command to start docker:
```
# Enter a Docker session:
make mount

# Open the spm.gds using KLayout with sky130 PDK
klayout -e -nn $PDK_ROOT/sky130A/libs.tec h/klayout/tech/sky130A.lyt \
   -l $PDK_ROOT/sky130A/libs.tech/klayout/tech/sky130A.lyp \
   ./designs/spm/runs/openlane_test/results/final/gds/spm.gds

# Leave the Docker
exit
```

### SkyWater Libraries
sky130_fd_sc_hd - sky130 FreePDK high density standard cell library

*sky130_fd_sc_hd__tt_025C_1v80_256.lib*, is a standard cell library for the SkyWater PDK130 process. It's used in integrated circuit (IC) design to describe the basic building blocks of circuits, like logic gates, memories, and analog circuits. Here's a breakdown of its components:

  * sky130: This refers to the SkyWater PDK130, a 130-nanometer CMOS process technology offered by SkyWater Technology. It's popular for its low cost and ease of use, making it ideal for a wide range of applications, including research, education, and commercial products.
  * fd_sc: This part stands for "SkyWater foundary standard cells". These are the basic logic gates and other circuit elements that can be combined to create more complex functions.
  * hd: This indicates the "high-density" version of the standard cells.
  * tt_025C: This part refers to the timming model and temperature. The "tt" stands for "typical typical", which means the model is based on typical values. The "025C" indicates the temperature is 25 degrees Celsius.
  * 1v80: This specifies the nominal supply voltage (1.8V) of the transistors in the cells.
  * 256: Includes cell sky130_sram_1kbyte_1rw1r_32x256_8


Overall, *sky130_fd_sc_hd__tt_025C_1v80_256.lib* is a crucial file for anyone designing circuits using the SkyWater PDK130 process. It provides the basic building blocks and characteristics needed to simulate, layout, and fabricate your design.

*sky130_sram_1kbyte_1rw1r_32x256_8.v* is a Verilog module that describes a 1 kilobyte Static Random-Access Memory (SRAM) for the SkyWater PDK130 process. Here's a breakdown of its components:

  * sky130: This refers to the SkyWater PDK130 technology, as mentioned previously.
  * sram: This indicates the module defines a memory block.
  * 1kbyte: This specifies the total memory capacity of the block, which is 1 kilobyte, or 1024 bytes.
  * 1rw1r: This describes the access mode. It's a pseudo-dual port SRAM, meaning you can only perform one write operation and one read operation simultaneously. It's not a true dual-port where both actions can happen independently.
  * 32x256: This defines the memory organization. It has a word size of 32 bits (4 bytes) and a depth of 256 words, resulting in the 1 kilobyte capacity.
  * 8: This likely refers to the data bus width. You can read and write 8 bits (one byte) at a time from the 32-bit words.
  * .v: This is the file extension for Verilog source code.
