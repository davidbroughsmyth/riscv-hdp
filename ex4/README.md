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

  *sky130: This refers to the SkyWater PDK130, a 130-nanometer CMOS process technology offered by SkyWater Technology. It's popular for its low cost and ease of use, making it ideal for a wide range of applications, including research, education, and commercial products.
  *fd_sc: This part stands for "foundation standard cells". These are the basic logic gates and other circuit elements that can be combined to create more complex functions.
  *hd: This indicates the "high-drive" version of the standard cells. These cells have lower resistance compared to regular cells, allowing them to drive larger loads or operate at higher frequencies.
  *tt_025C: This part likely refers to the specific transistor size and channel width used in the cells. Different sizes offer different trade-offs between performance, power consumption, and area.
  *1v80: This specifies the nominal supply voltage (1.8V) and the typical threshold voltage (0.8V) of the transistors in the cells.
  *256: This is likely the number of cells included in the library. More cells provide more flexibility for designers, but also increase the file size and complexity.
Overall, sky130_fd_sc_hd__tt_025C_1v80_256.lib is a crucial file for anyone designing circuits using the SkyWater PDK130 process. It provides the basic building blocks and characteristics needed to simulate, layout, and fabricate your design.
