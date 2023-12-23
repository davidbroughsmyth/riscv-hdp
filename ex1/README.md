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

#### Hello
![image](../images/count.png)

``` assembly
	.file	"hello.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"Hello"
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	addi	s0,sp,16
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	puts
	li	a5,0
	mv	a0,a5
	ld	ra,8(sp)
	ld	s0,0(sp)
	addi	sp,sp,16
	jr	ra
	.size	main, .-main
	.ident	"GCC: (gc891d8dc2-dirty) 13.2.0"
```

#### Hello_rvbook
![image](../images/count_rvbook.png)
