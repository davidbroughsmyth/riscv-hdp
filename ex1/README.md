### C code for counter and matrix multiplication
**shcmds** show comandline to complie and execute each program

Using **spike** as a RISC-V ISA simulator  https://github.com/riscv-software-src/riscv-isa-sim

On a MacOS with a apple M2 cpu I have used  https://github.com/riscv-software-src/homebrew-riscv to set up the RISC-V toolchain which includes Spike

Since I have a https://milkv.io/duo, the programs are tested on actual hardware  

Using https://godbolt.org/ to show RISC-V assemble and execution:
1. Hello: https://godbolt.org/z/zore9ffKW
2. Hello_rvbook: https://godbolt.org/z/Md5frnW1j
3. Count: https://godbolt.org/z/efvE7njTv
4. MatMuli: https://godbolt.org/z/9rfE4d1eW

### Assembly differences

Showing the assembly code differences between a very basic C hello program and the C hello program from the rvbook for RISC-V gcc, x86-64 gcc and the riscv64-unknown-elf-gcc toolchain.

####Hello
![image](https://github.com/davidbroughsmyth/riscv-hdp/blob/main/images/count.c)
