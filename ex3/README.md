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

### comparing 64bit to 32bit sizes, and 32bit without libs

-- count
![image](../images/count_size.png)

-- matmulti
![image](../images/matmulti_size.png)

-- alu
![image](../images/alu_size.png)
