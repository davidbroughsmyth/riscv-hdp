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
'''
xattr -d com.apple.quarantine oss-cad-suite-darwin-x64-yyymmdd.tgz
source <extracted_location>/oss-cad-suite/environment
yosys -V
'''

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
klayout -e -nn $PDK_ROOT/sky130A/libs.tech/klayout/tech/sky130A.lyt \
   -l $PDK_ROOT/sky130A/libs.tech/klayout/tech/sky130A.lyp \
   ./designs/spm/runs/openlane_test/results/final/gds/spm.gds

# Leave the Docker
exit
```
