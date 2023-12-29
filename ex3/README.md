### C code RISC-V verification

-- compile to 64bit risc-v
```
riscv64-unknown-elf-gcc -o count count.c
riscv64-unknown-elf-gcc -o matmulti matmulti.c
riscv64-unknown-elf-gcc -o alu alu.c
```
### 32bit RISC-V compilation

-- compile to 32bit risc-v with libs
```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -o count32 count.c
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -o matmulti32 matmulti.c
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -o alu32 alu.c
```

-- compile to 32bit risc-v without #includes,libraries and printf
```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -o count32_noprintf count32_noprintf.c
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -o matmulti32_noprintf matmulti32_noprintf.c
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -o alu32_noprintf alu32_noprintf.c
```

-- dump to assembly format without #includes,libraries and printf
```
riscv64-unknown-elf-objdump -d -r count32_noprintf > count32_noprintf.txt
riscv64-unknown-elf-objdump -d -r matmulti32_noprintf > matmulti32_noprintf.txt
riscv64-unknown-elf-objdump -d -r alu32_noprintf > alu32_noprintf.txt
```

-- execute count using spike
![image](../images/count_spike.png)

-- execute matmulti using spike
![image](../images/matmulti_spike.png)

-- execute alu using spike
![image](../images/alu_spike.png)

### Comparing 64bit to 32bit sizes, and 32bit without libs

The same c code for 32bit compliles down to double the size to that of 64bit. Whilst a 32bit lib stripped c code is about 7% of 32bit compliled executable.  

-- count
![image](../images/count_size.png)

-- matmulti
![image](../images/matmulti_size.png)

-- alu
![image](../images/alu_size.png)

### RISCV-C CPU Performance

-- count32 lib stripped assembly
```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -S count32_noprintf.c
```

``` assembly
        .file   "count32_noprintf.c"
        .option nopic
        .attribute arch, "rv32i2p1"
        .attribute unaligned_access, 0
        .attribute stack_align, 16
        .text
        .align  2
        .globl  display
        .type   display, @function
display:
        addi    sp,sp,-32
        sw      s0,28(sp)
        addi    s0,sp,32
        sw      a0,-20(s0)
        nop
        lw      s0,28(sp)
        addi    sp,sp,32
        jr      ra
        .size   display, .-display
        .align  2
        .globl  main
        .type   main, @function
main:
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        addi    s0,sp,32
        sw      zero,-20(s0)
.L4:
        lw      a0,-20(s0)
        call    display
        lw      a5,-20(s0)
        addi    a5,a5,1
        sw      a5,-20(s0)
        lw      a4,-20(s0)
        li      a5,16
        bne     a4,a5,.L4
        sw      zero,-20(s0)
        j       .L4
        .size   main, .-main
        .ident  "GCC: (gc891d8dc2-dirty) 13.2.0"
``` 

**Display** = 8 instructions

**Loop .L4** = 10 instuctions

**Main** = 5 instructions

First pass of the count loop = 5 (inital main) + 10 (loop) + 8 (display) = 23 instructions

If the selected RISC-V CPU does one instruction per clock cycle (lets call this CPU **IdealRV**), hence Cycles per Instruction (CPI) = 1, then one pass of `count32_noprintf.c` = 23 clock cycles

If the CPU was **10Mhz** then one count loop would take 2.3 microseconds if no libraries were called, but since display is non functional the count program could be optimised by removing 8 (display) cpu cycles and 1 cpu cycle from the call to display from .L4, this would make the optimised count program taking 14 cpu cycles or 1.4 microseconds.

On the second pass the 4 inital instructions of main are skipped, so only 10 .L4 loop instructions are run until the count gets to 16  plus the 8 display instructions. The **.L4 loop** + **display** = 1.8 microseconds and 1.7 microseconds when the count gets to 16. 

Hence we expect the whole count sequence to 16 to equal (the loop count sequence will only display 0 to 15):
```
first pass + 14 * second pass + last pass
 = 23 inst + 14 * 18 + 17
 = 292 cpu cycles (or instructions for CPI=1)

CPU time = 1 (CPI) * 292 * 0.1uS (10mhz clock)
 = 29.2 microseconds
```

#### Selecting a PicoRV32 cpu

The average Cycles per Instruction (CPI) for a [PicoRV32](https://github.com/YosysHQ/picorv32) is approximately 4, depending on the mix of instructions in the code. 
The CPI numbers for the individual instructions can be found in the table below. 

| Instruction          |  CPI |
| ---------------------| ----:|
| direct jump (jal)    |    3 |
| ALU reg + immediate  |    3 |
| ALU reg + reg        |    3 |
| branch (not taken)   |    3 |
| memory load          |    5 |
| memory store         |    5 |
| branch (taken)       |    5 |
| indirect jump (jalr) |    6 |
| shift operations     | 4-14 |

Give the same count program and same CPU clock of 10Mhz, then the whole count sequence to 16 to equal:
```
CPU time = 4 (CPI) * 292 instuctions * 0.1uS (10Mhz clock)
 = 116.8 microsconds
```

The relative performance between the IdealRV and PicoRV32 CPU's for the same CPU clock is:
```
CPU performance ratio of the reference IdealRV to PicoRV32 CPU's
 = 4 (CPI PicoRV32)/ 1 (CPI IdealRV)
 = 4
```
*IdealRV is 4 times faster*

If the PicoRV32 CPU clock runs at 100Mhz instead, then compared with IdealRV running at 10Mhz
```
CPU performance ratio of the reference IdealRV to PicoRV32 CPU's
 = 4 (CPI PicoRV32) * 0.01uS/ 1 (CPI IdealRV) * 0.1uS
 = 0.4
```
*IdealRV is .4 times slower, or PicoRV32 is 2.5 times faster*
