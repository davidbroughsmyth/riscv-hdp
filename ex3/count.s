	.file	"count.c"
	.option nopic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	delay
	.type	delay, @function
delay:
	addi	sp,sp,-48
	sw	ra,44(sp)
	sw	s0,40(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	lw	a5,-36(s0)
	sw	a5,-20(s0)
	call	clock
	sw	a0,-24(s0)
	nop
.L2:
	call	clock
	mv	a3,a0
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	add	a5,a4,a5
	bltu	a3,a5,.L2
	nop
	nop
	lw	ra,44(sp)
	lw	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	delay, .-delay
	.section	.rodata
	.align	2
.LC0:
	.string	"Count value is: %d\n"
	.text
	.align	2
	.globl	display
	.type	display, @function
display:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	lw	a1,-20(s0)
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	printf
	nop
	lw	ra,28(sp)
	lw	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	display, .-display
	.section	.rodata
	.align	2
.LC1:
	.string	"Start counter\n"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	lui	a5,%hi(.LC1)
	addi	a0,a5,%lo(.LC1)
	call	printf
	sw	zero,-20(s0)
.L6:
	lw	a0,-20(s0)
	call	display
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
	lw	a4,-20(s0)
	li	a5,16
	bne	a4,a5,.L5
	sw	zero,-20(s0)
.L5:
	li	a5,499712
	addi	a0,a5,288
	call	delay
	j	.L6
	.size	main, .-main
	.ident	"GCC: (gc891d8dc2-dirty) 13.2.0"
