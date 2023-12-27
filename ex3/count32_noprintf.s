	.file	"count32_noprintf.c"
	.option nopic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	display
	.type	display, @function
display:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	display, .-display
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	sw	zero,-20(s0)
.L4:
	lw	a0,-20(s0)
	call	display
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
	lw	a4,-20(s0)
	li	a5,16
	bne	a4,a5,.L4
	sw	zero,-20(s0)
	j	.L4
	.size	main, .-main
	.ident	"GCC: (gc891d8dc2-dirty) 13.2.0"
