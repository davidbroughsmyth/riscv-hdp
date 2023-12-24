### C based 4bit ALU
-- compile to risc-v
```
riscv64-unknown-elf-gcc -o alu alu.c
```
-- execute using spike
```
spike pk alu
``
-- command line C program run
```
bbl loader
Enter two 4-bit binary numbers as decimal (A and B): 3 4
Enter the operation (+, -, *, /, &, |, ^): |
Result: 7
```
### Verilog 4bit ALU
-- compiler verilog
```
iverilog -o alu_v alu_tb.v alu.v
```
-- execute verilog
```
vvp alu_v
```
-- RTL systhesis showing fpga gates
```
yosys -p "read_verilog alu.v; proc; opt; show -colors 2 -width -signed"
```
