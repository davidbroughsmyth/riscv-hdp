### ZeroRV IOT
The smallest c program footprint. Used only to validate very basic riscv cpu generation, as it has no input or output and the program is the smallest possible for c to generate. Useful to validate verilog simlations as the programs steps are small enough to trace through the waveforms. 

**ZeroRV** with implicit int return
```
int main()
{
}
```

**ZeroRv_rtn** with explicit int return
```
int main()
{
	return(0);
}
```

**ZeroRV_void** void return
```
void main()
{
}
```
Both ZeroRV and ZeroRv_rtn have 6 instructions, ZeroRV_void has 5 by removing the return.

### NopRV
One riscv nop instruction.  
``` assembly
asm("nop");
```

#### Block Diagram
![image](../../images/zerorv_bd.png)

#### ZeroRV Complilation and assembly
```
riscv64-unknown-elf-gcc -mabi=ilp32 -march=rv32i -ffreestanding -nostdlib -o zerorv.o zerorv.c
riscv64-unknown-elf-objdump -d -r zerorv.o > zero_assembly.txt
```

#### NopRV Complilation and assembly
```
riscv64-unknown-elf-gcc -mabi=ilp32 -march=rv32i -ffreestanding -nostdlib -o noprv.o noprv.c
riscv64-unknown-elf-objdump -d -r noprv.o > noprv_assembly.txt
```
