### 32bit RISC-V compilation

-- compile to 64bit risc-v
```
riscv64-unknown-elf-gcc -o count count.c
riscv64-unknown-elf-gcc -o matmulti matmulti.c
riscv64-unknown-elf-gcc -o alu alu.c
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
