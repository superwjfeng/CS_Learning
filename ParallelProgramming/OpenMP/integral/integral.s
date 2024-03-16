	.file	"integral.c"
# GNU C17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -fopenmp -fomit-frame-pointer -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.globl	x_square_partial_integral
	.type	x_square_partial_integral, @function
x_square_partial_integral:
.LFB0:
	.cfi_startproc
	endbr64	
	subq	$56, %rsp	#,
	.cfi_def_cfa_offset 64
	movsd	%xmm0, 24(%rsp)	# start, start
	movsd	%xmm1, 16(%rsp)	# end, end
	movsd	%xmm2, 8(%rsp)	# delta, delta
# integral.c:13:   double s = 0;
	pxor	%xmm0, %xmm0	# tmp86
	movsd	%xmm0, 32(%rsp)	# tmp86, s
# integral.c:14:   for(double i = start; i < end; i += delta) {
	movsd	24(%rsp), %xmm0	# start, tmp87
	movsd	%xmm0, 40(%rsp)	# tmp87, i
# integral.c:14:   for(double i = start; i < end; i += delta) {
	jmp	.L2	#
.L3:
# integral.c:15:     s += pow(i, 2) * delta;
	movsd	.LC1(%rip), %xmm0	#, tmp88
	movq	40(%rsp), %rax	# i, tmp89
	movapd	%xmm0, %xmm1	# tmp88,
	movq	%rax, %xmm0	# tmp89,
	call	pow@PLT	#
	movq	%xmm0, %rax	#, _1
# integral.c:15:     s += pow(i, 2) * delta;
	movq	%rax, %xmm0	# _1, _1
	mulsd	8(%rsp), %xmm0	# delta, _1
# integral.c:15:     s += pow(i, 2) * delta;
	movsd	32(%rsp), %xmm1	# s, tmp91
	addsd	%xmm1, %xmm0	# tmp91, tmp90
	movsd	%xmm0, 32(%rsp)	# tmp90, s
# integral.c:14:   for(double i = start; i < end; i += delta) {
	movsd	40(%rsp), %xmm0	# i, tmp93
	addsd	8(%rsp), %xmm0	# delta, tmp92
	movsd	%xmm0, 40(%rsp)	# tmp92, i
.L2:
# integral.c:14:   for(double i = start; i < end; i += delta) {
	movsd	16(%rsp), %xmm0	# end, tmp94
	comisd	40(%rsp), %xmm0	# i, tmp94
	ja	.L3	#,
# integral.c:17:   return s;
	movsd	32(%rsp), %xmm0	# s, _10
	movq	%xmm0, %rax	# _10, <retval>
# integral.c:18: }
	movq	%rax, %xmm0	# <retval>,
	addq	$56, %rsp	#,
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE0:
	.size	x_square_partial_integral, .-x_square_partial_integral
	.section	.rodata
.LC2:
	.string	"sum = %lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64	
	subq	$56, %rsp	#,
	.cfi_def_cfa_offset 64
# integral.c:20: int main() {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp94
	movq	%rax, 40(%rsp)	# tmp94, D.3887
	xorl	%eax, %eax	# tmp94
# integral.c:22:   int s = 0;
	movl	$0, (%rsp)	#, s
# integral.c:23:   int e = 10;
	movl	$10, 4(%rsp)	#, e
# integral.c:24:   double sum = 0;
	pxor	%xmm0, %xmm0	# tmp84
	movsd	%xmm0, 8(%rsp)	# tmp84, sum
# integral.c:25:   #pragma omp parallel num_threads(32) reduction(+:sum)
	movsd	8(%rsp), %xmm0	# sum, tmp85
	movsd	%xmm0, 16(%rsp)	# tmp85, .omp_data_o.1.sum
	movl	4(%rsp), %eax	# e, tmp86
	movl	%eax, 28(%rsp)	# tmp86, .omp_data_o.1.e
	movl	(%rsp), %eax	# s, tmp87
	movl	%eax, 24(%rsp)	# tmp87, .omp_data_o.1.s
	leaq	16(%rsp), %rax	#, tmp88
	movl	$0, %ecx	#,
	movl	$32, %edx	#,
	movq	%rax, %rsi	# tmp88,
	leaq	main._omp_fn.0(%rip), %rax	#, tmp89
	movq	%rax, %rdi	# tmp89,
	call	GOMP_parallel@PLT	#
	movsd	16(%rsp), %xmm0	# .omp_data_o.1.sum, tmp90
	movsd	%xmm0, 8(%rsp)	# tmp90, sum
# integral.c:33:   printf("sum = %lf\n", sum);
	movq	8(%rsp), %rax	# sum, tmp91
	movq	%rax, %xmm0	# tmp91,
	leaq	.LC2(%rip), %rax	#, tmp92
	movq	%rax, %rdi	# tmp92,
	movl	$1, %eax	#,
	call	printf@PLT	#
# integral.c:34:   return 0;
	movl	$0, %eax	#, _12
# integral.c:35: }
	movq	40(%rsp), %rdx	# D.3887, tmp95
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp95
	je	.L7	#,
	call	__stack_chk_fail@PLT	#
.L7:
	addq	$56, %rsp	#,
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.type	main._omp_fn.0, @function
main._omp_fn.0:
.LFB2:
	.cfi_startproc
	endbr64	
	subq	$56, %rsp	#,
	.cfi_def_cfa_offset 64
	movq	%rdi, 8(%rsp)	# .omp_data_i, .omp_data_i
# integral.c:25:   #pragma omp parallel num_threads(32) reduction(+:sum)
	pxor	%xmm0, %xmm0	# tmp100
	movsd	%xmm0, 24(%rsp)	# tmp100, sum
	movq	8(%rsp), %rax	# .omp_data_i, tmp101
	movl	12(%rax), %eax	# .omp_data_i_5(D)->e, tmp102
	movl	%eax, 16(%rsp)	# tmp102, e
	movq	8(%rsp), %rax	# .omp_data_i, tmp103
	movl	8(%rax), %eax	# .omp_data_i_5(D)->s, tmp104
	movl	%eax, 20(%rsp)	# tmp104, s
# integral.c:29:     double start = (double)(e - s) / 32 * omp_get_thread_num();
	movl	16(%rsp), %eax	# e, tmp105
	subl	20(%rsp), %eax	# s, _8
# integral.c:29:     double start = (double)(e - s) / 32 * omp_get_thread_num();
	pxor	%xmm0, %xmm0	# _9
	cvtsi2sdl	%eax, %xmm0	# _8, _9
# integral.c:29:     double start = (double)(e - s) / 32 * omp_get_thread_num();
	movsd	.LC3(%rip), %xmm1	#, tmp106
	divsd	%xmm1, %xmm0	# tmp106, _9
	movsd	%xmm0, (%rsp)	# _9, %sfp
# integral.c:29:     double start = (double)(e - s) / 32 * omp_get_thread_num();
	call	omp_get_thread_num@PLT	#
# integral.c:29:     double start = (double)(e - s) / 32 * omp_get_thread_num();
	pxor	%xmm0, %xmm0	# _13
	cvtsi2sdl	%eax, %xmm0	# _12, _13
# integral.c:29:     double start = (double)(e - s) / 32 * omp_get_thread_num();
	mulsd	(%rsp), %xmm0	# %sfp, tmp107
	movsd	%xmm0, 32(%rsp)	# tmp107, start
# integral.c:30:     double end   = (double)(e - s) / 32 * (omp_get_thread_num() + 1);
	movl	16(%rsp), %eax	# e, tmp108
	subl	20(%rsp), %eax	# s, _15
# integral.c:30:     double end   = (double)(e - s) / 32 * (omp_get_thread_num() + 1);
	pxor	%xmm0, %xmm0	# _16
	cvtsi2sdl	%eax, %xmm0	# _15, _16
# integral.c:30:     double end   = (double)(e - s) / 32 * (omp_get_thread_num() + 1);
	movsd	.LC3(%rip), %xmm1	#, tmp109
	divsd	%xmm1, %xmm0	# tmp109, _16
	movsd	%xmm0, (%rsp)	# _16, %sfp
# integral.c:30:     double end   = (double)(e - s) / 32 * (omp_get_thread_num() + 1);
	call	omp_get_thread_num@PLT	#
# integral.c:30:     double end   = (double)(e - s) / 32 * (omp_get_thread_num() + 1);
	addl	$1, %eax	#, _20
# integral.c:30:     double end   = (double)(e - s) / 32 * (omp_get_thread_num() + 1);
	pxor	%xmm0, %xmm0	# _21
	cvtsi2sdl	%eax, %xmm0	# _20, _21
# integral.c:30:     double end   = (double)(e - s) / 32 * (omp_get_thread_num() + 1);
	mulsd	(%rsp), %xmm0	# %sfp, tmp110
	movsd	%xmm0, 40(%rsp)	# tmp110, end
# integral.c:31:     sum = x_square_partial_integral(start, end, 0.0000001);
	movsd	.LC4(%rip), %xmm1	#, tmp111
	movsd	40(%rsp), %xmm0	# end, tmp112
	movq	32(%rsp), %rax	# start, tmp113
	movapd	%xmm1, %xmm2	# tmp111,
	movapd	%xmm0, %xmm1	# tmp112,
	movq	%rax, %xmm0	# tmp113,
	call	x_square_partial_integral	#
	movq	%xmm0, %rax	#, tmp114
	movq	%rax, 24(%rsp)	# tmp114, sum
# integral.c:25:   #pragma omp parallel num_threads(32) reduction(+:sum)
	movq	8(%rsp), %rcx	# .omp_data_i, _25
	movq	(%rcx), %rdx	#* _25, _1
.L9:
	movq	%rdx, %xmm0	# _1, _30
# integral.c:25:   #pragma omp parallel num_threads(32) reduction(+:sum)
	addsd	24(%rsp), %xmm0	# sum, _31
	movq	%xmm0, %rsi	# _31, _32
	movq	%rdx, %rax	# _1, _34
	lock cmpxchgq	%rsi, (%rcx)	#, _32,* _25
	movq	%rdx, %rsi	# _1, _35
	movq	%rax, %rdx	# _34, _1
	cmpq	%rsi, %rax	# _35, _34
	jne	.L9	#,
# integral.c:25:   #pragma omp parallel num_threads(32) reduction(+:sum)
	addq	$56, %rsp	#,
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE2:
	.size	main._omp_fn.0, .-main._omp_fn.0
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1073741824
	.align 8
.LC3:
	.long	0
	.long	1077936128
	.align 8
.LC4:
	.long	-1698910392
	.long	1048238066
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
