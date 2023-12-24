### C based 4bit ALU
-- compile to risc-v
```
riscv64-unknown-elf-gcc -o alu alu.c
```
-- execute using spike
```
spike pk alu
```
-- command line C program run
![image](../images/c_alu.png)

### Verilog 4bit ALU
-- compiler verilog
```
iverilog -o alu_v alu_tb.v alu.v
```
-- execute verilog
```
vvp alu_v
```
![image](../images/alu_verilog_run.png)

-- display gtkwave for ALU
```
gtkwave.vcd
```
![image](../images/gtkwave_alu.png)

-- RTL systhesis showing fpga gates
```
yosys -p "read_verilog alu.v; proc; opt; show -colors 2 -width -signed"
```
![image](../images/alu_synth.png)
