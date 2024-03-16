	.file	"main.c"
	.intel_syntax noprefix
# GNU C17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -masm=intel -mtune=generic -march=x86-64 -Og -fopenmp -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"tid = %d data = %d two = %d\n"
	.text
	.type	main._omp_fn.0, @function
main._omp_fn.0:
.LFB24:
	.cfi_startproc
	endbr64	
	push	rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	push	rbx	#
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	sub	rsp, 8	#,
	.cfi_def_cfa_offset 32
# main.c:9: #pragma omp parallel num_threads(4) default(none) shared(data, two)
	mov	ebp, DWORD PTR 4[rdi]	# two, .omp_data_i_2(D)->two
	mov	ebx, DWORD PTR [rdi]	# data, .omp_data_i_2(D)->data
# main.c:11:     printf("tid = %d data = %d two = %d\n", omp_get_thread_num(), data, two);
	call	omp_get_thread_num@PLT	#
	mov	edx, eax	# _5, tmp88
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	mov	r8d, ebp	#, two
	mov	ecx, ebx	#, data
	lea	rsi, .LC0[rip]	# tmp86,
	mov	edi, 1	#,
	mov	eax, 0	#,
	call	__printf_chk@PLT	#
# main.c:9: #pragma omp parallel num_threads(4) default(none) shared(data, two)
	add	rsp, 8	#,
	.cfi_def_cfa_offset 24
	pop	rbx	#
	.cfi_def_cfa_offset 16
	pop	rbp	#
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE24:
	.size	main._omp_fn.0, .-main._omp_fn.0
	.section	.rodata.str1.1
.LC1:
	.string	"start"
.LC2:
	.string	"finished"
	.text
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	endbr64	
	sub	rsp, 24	#,
	.cfi_def_cfa_offset 32
# main.c:5: {
	mov	rax, QWORD PTR fs:40	# tmp90, MEM[(<address-space-1> long unsigned int *)40B]
	mov	QWORD PTR 8[rsp], rax	# D.2987, tmp90
	xor	eax, eax	# tmp90
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	lea	rdi, .LC1[rip]	# tmp84,
	call	puts@PLT	#
# main.c:9: #pragma omp parallel num_threads(4) default(none) shared(data, two)
	mov	DWORD PTR 4[rsp], -100	# .omp_data_o.1.two,
	mov	DWORD PTR [rsp], 100	# .omp_data_o.1.data,
	mov	rsi, rsp	# tmp85,
	mov	ecx, 0	#,
	mov	edx, 4	#,
	lea	rdi, main._omp_fn.0[rip]	# tmp86,
	call	GOMP_parallel@PLT	#
# /usr/include/x86_64-linux-gnu/bits/stdio2.h:112:   return __printf_chk (__USE_FORTIFY_LEVEL - 1, __fmt, __va_arg_pack ());
	lea	rdi, .LC2[rip]	# tmp87,
	call	puts@PLT	#
# main.c:16: }
	mov	rax, QWORD PTR 8[rsp]	# tmp91, D.2987
	sub	rax, QWORD PTR fs:40	# tmp91, MEM[(<address-space-1> long unsigned int *)40B]
	jne	.L6	#,
	mov	eax, 0	#,
	add	rsp, 24	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret	
.L6:
	.cfi_restore_state
	call	__stack_chk_fail@PLT	#
	.cfi_endproc
.LFE23:
	.size	main, .-main
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
