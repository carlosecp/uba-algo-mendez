	.file	"quick_sort.c"
# GNU C17 (GCC) version 11.1.0 (x86_64-pc-linux-gnu)
#	compiled by GNU C version 11.1.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# warning: MPFR header version 4.1.0 differs from library version 4.1.0-p13.
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O2
	.text
	.p2align 4
	.globl	swap
	.type	swap, @function
swap:
.LFB22:
	.cfi_startproc
# quick_sort.c:6: {
	movq	%rdx, %r8	# pos_2, tmp95
# quick_sort.c:7: 	int temp = vector[pos_1];
	leaq	(%rdi,%rsi,4), %rdx	#, _2
# quick_sort.c:8: 	vector[pos_1] = vector[pos_2];
	leaq	(%rdi,%r8,4), %rax	#, _4
# quick_sort.c:7: 	int temp = vector[pos_1];
	movl	(%rdx), %ecx	# *_2, temp
# quick_sort.c:8: 	vector[pos_1] = vector[pos_2];
	movl	(%rax), %esi	# *_4, _5
# quick_sort.c:8: 	vector[pos_1] = vector[pos_2];
	movl	%esi, (%rdx)	# _5, *_2
# quick_sort.c:9: 	vector[pos_2] = temp;
	movl	%ecx, (%rax)	# temp, *_4
# quick_sort.c:10: }
	ret	
	.cfi_endproc
.LFE22:
	.size	swap, .-swap
	.p2align 4
	.globl	pivot
	.type	pivot, @function
pivot:
.LFB23:
	.cfi_startproc
# quick_sort.c:15: 	size_t pos_pivote = tope - 1, pos_pivote_final = 0;
	leaq	-1(%rsi), %r8	#, <retval>
# quick_sort.c:7: 	int temp = vector[pos_1];
	leaq	(%rdi,%r8,4), %r10	#, _58
# quick_sort.c:7: 	int temp = vector[pos_1];
	movl	(%r10), %ecx	# *_58, prephitmp_41
# quick_sort.c:17: 	for (size_t i = 0; i < pos_pivote; i++) {
	testq	%r8, %r8	# <retval>
	je	.L4	#,
	movq	%rdi, %rax	# vector, ivtmp.14
	leaq	-4(%rdi,%rsi,4), %rsi	#, _46
# quick_sort.c:15: 	size_t pos_pivote = tope - 1, pos_pivote_final = 0;
	xorl	%r8d, %r8d	# <retval>
	.p2align 4,,10
	.p2align 3
.L6:
# quick_sort.c:18: 		if (vector[i] < vector[pos_pivote]) {
	movl	(%rax), %edx	# MEM[(int *)_9], _3
# quick_sort.c:18: 		if (vector[i] < vector[pos_pivote]) {
	cmpl	%ecx, %edx	# prephitmp_41, _3
	jge	.L5	#,
# quick_sort.c:8: 	vector[pos_1] = vector[pos_2];
	leaq	(%rdi,%r8,4), %rcx	#, _55
# quick_sort.c:20: 			pos_pivote_final++;
	addq	$1, %r8	#, <retval>
# quick_sort.c:8: 	vector[pos_1] = vector[pos_2];
	movl	(%rcx), %r9d	# *_55, pretmp_56
# quick_sort.c:8: 	vector[pos_1] = vector[pos_2];
	movl	%r9d, (%rax)	# pretmp_56, MEM[(int *)_9]
# quick_sort.c:9: 	vector[pos_2] = temp;
	movl	%edx, (%rcx)	# _3, *_55
# quick_sort.c:7: 	int temp = vector[pos_1];
	movl	(%r10), %ecx	# *_58, prephitmp_41
.L5:
# quick_sort.c:17: 	for (size_t i = 0; i < pos_pivote; i++) {
	addq	$4, %rax	#, ivtmp.14
	cmpq	%rsi, %rax	# _46, ivtmp.14
	jne	.L6	#,
# quick_sort.c:8: 	vector[pos_1] = vector[pos_2];
	leaq	(%rdi,%r8,4), %rdi	#, vector
.L4:
	movl	(%rdi), %eax	# *prephitmp_51, _27
# quick_sort.c:8: 	vector[pos_1] = vector[pos_2];
	movl	%eax, (%r10)	# _27, *_58
# quick_sort.c:27: }
	movq	%r8, %rax	# <retval>,
# quick_sort.c:9: 	vector[pos_2] = temp;
	movl	%ecx, (%rdi)	# prephitmp_41, *prephitmp_51
# quick_sort.c:27: }
	ret	
	.cfi_endproc
.LFE23:
	.size	pivot, .-pivot
	.p2align 4
	.globl	quick_sort
	.type	quick_sort, @function
quick_sort:
.LFB24:
	.cfi_startproc
	pushq	%r15	#
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14	#
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13	#
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12	#
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp	#
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx	#
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$184, %rsp	#,
	.cfi_def_cfa_offset 240
# quick_sort.c:31: {
	movq	%rdi, 88(%rsp)	# tmp163, %sfp
	movq	%rsi, 96(%rsp)	# tope, %sfp
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rsi	#, tope
	jbe	.L11	#,
.L12:
# quick_sort.c:35: 	size_t pos_pivot = pivot(vector, tope);
	movq	88(%rsp), %rbx	# %sfp, vector
	movq	96(%rsp), %rsi	# %sfp,
	movq	%rbx, %rdi	# vector,
	call	pivot	#
	movq	%rax, 112(%rsp)	# pos_pivot, %sfp
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, pos_pivot
	jbe	.L13	#,
	movq	%rbx, 48(%rsp)	# vector, %sfp
	movq	%rax, 40(%rsp)	# pos_pivot, %sfp
.L28:
# quick_sort.c:35: 	size_t pos_pivot = pivot(vector, tope);
	movq	48(%rsp), %rbx	# %sfp, vector
	movq	40(%rsp), %rsi	# %sfp,
	movq	%rbx, %rdi	# vector,
	call	pivot	#
	movq	%rax, 120(%rsp)	# pos_pivot, %sfp
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, pos_pivot
	jbe	.L14	#,
	movq	%rbx, 64(%rsp)	# vector, %sfp
	movq	%rax, 56(%rsp)	# pos_pivot, %sfp
.L27:
# quick_sort.c:35: 	size_t pos_pivot = pivot(vector, tope);
	movq	64(%rsp), %rbx	# %sfp, vector
	movq	56(%rsp), %rsi	# %sfp,
	movq	%rbx, %rdi	# vector,
	call	pivot	#
	movq	%rax, 128(%rsp)	# pos_pivot, %sfp
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, pos_pivot
	jbe	.L15	#,
	movq	%rbx, 80(%rsp)	# vector, %sfp
	movq	%rax, 72(%rsp)	# pos_pivot, %sfp
.L26:
# quick_sort.c:35: 	size_t pos_pivot = pivot(vector, tope);
	movq	80(%rsp), %r14	# %sfp, vector
	movq	72(%rsp), %rsi	# %sfp,
	movq	%r14, %rdi	# vector,
	call	pivot	#
	movq	%rax, 136(%rsp)	# pos_pivot, %sfp
	movq	%rax, %r15	# tmp168, pos_pivot
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, pos_pivot
	jbe	.L16	#,
.L25:
# quick_sort.c:35: 	size_t pos_pivot = pivot(vector, tope);
	movq	%r15, %rsi	# tope,
	movq	%r14, %rdi	# vector,
	call	pivot	#
	movq	%rax, %r13	# tmp169, pos_pivot
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, pos_pivot
	jbe	.L17	#,
	movq	%rax, 16(%rsp)	# pos_pivot, %sfp
	movq	%r14, %rbx	# vector, vector
	movq	%rax, %r12	# pos_pivot, tope
	movq	%r15, 24(%rsp)	# tope, %sfp
	movq	%r14, 32(%rsp)	# vector, %sfp
.L24:
# quick_sort.c:35: 	size_t pos_pivot = pivot(vector, tope);
	movq	%r12, %rsi	# tope,
	movq	%rbx, %rdi	# vector,
	call	pivot	#
	movq	%rax, %rbp	# tmp170, pos_pivot
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, pos_pivot
	jbe	.L18	#,
	movq	%rax, 8(%rsp)	# pos_pivot, %sfp
	movq	%rbx, %r14	# vector, vector
.L23:
# quick_sort.c:35: 	size_t pos_pivot = pivot(vector, tope);
	movq	8(%rsp), %rsi	# %sfp,
	movq	%r14, %rdi	# vector,
	call	pivot	#
	movq	%rax, 144(%rsp)	# pos_pivot, %sfp
	movq	%rax, %r15	# tmp171, pos_pivot
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, pos_pivot
	jbe	.L19	#,
	movq	%rbx, 104(%rsp)	# vector, %sfp
	movq	%r14, %rbx	# vector, vector
.L22:
# quick_sort.c:35: 	size_t pos_pivot = pivot(vector, tope);
	movq	%r15, %rsi	# tope,
	movq	%rbx, %rdi	# vector,
	call	pivot	#
	movq	%rax, %r13	# tmp172, pos_pivot
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, pos_pivot
	jbe	.L20	#,
	movq	%r15, %rcx	# tope, tope
	movq	%r12, %r13	# tope, tope
	movq	%rax, %rdx	# pos_pivot, tope
	movq	%rbp, %r12	# pos_pivot, pos_pivot
	movq	%rax, %r15	# pos_pivot, pos_pivot
	movq	%rbx, %r8	# vector, vector
	movq	%rbx, %rbp	# vector, vector
.L21:
# quick_sort.c:35: 	size_t pos_pivot = pivot(vector, tope);
	movq	%rdx, %rsi	# tope,
	movq	%rbp, %rdi	# vector,
	movq	%r8, 168(%rsp)	# vector, %sfp
	movq	%rcx, 160(%rsp)	# tope, %sfp
	movq	%rdx, 152(%rsp)	# tope, %sfp
	call	pivot	#
# quick_sort.c:37: 	quick_sort(vector, pos_pivot);
	movq	%rbp, %rdi	# vector,
	movq	%rax, %rsi	# pos_pivot,
# quick_sort.c:35: 	size_t pos_pivot = pivot(vector, tope);
	movq	%rax, %rbx	# tmp173, pos_pivot
# quick_sort.c:37: 	quick_sort(vector, pos_pivot);
	call	quick_sort	#
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	movq	152(%rsp), %rdx	# %sfp, tope
# quick_sort.c:32: 	if (tope <= 1)
	movq	160(%rsp), %rcx	# %sfp, tope
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	leaq	4(%rbp,%rbx,4), %rbp	#, vector
# quick_sort.c:32: 	if (tope <= 1)
	movq	168(%rsp), %r8	# %sfp, vector
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	subq	%rbx, %rdx	# pos_pivot, tmp136
	subq	$1, %rdx	#, tope
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rdx	#, tope
	ja	.L21	#,
	movq	%r12, %rbp	# pos_pivot, pos_pivot
	movq	%r8, %rbx	# vector, vector
	movq	%r13, %r12	# tope, tope
	movq	%r15, %r13	# pos_pivot, pos_pivot
	movq	%rcx, %r15	# tope, tope
.L20:
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	subq	%r13, %r15	# pos_pivot, tmp139
	leaq	4(%rbx,%r13,4), %rbx	#, vector
	subq	$1, %r15	#, tope
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %r15	#, tope
	ja	.L22	#,
	movq	104(%rsp), %rbx	# %sfp, vector
.L19:
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	movq	8(%rsp), %r15	# %sfp, tope
	movq	144(%rsp), %rcx	# %sfp, pos_pivot
	subq	%rcx, %r15	# pos_pivot, tope
	leaq	4(%r14,%rcx,4), %r14	#, vector
	leaq	-1(%r15), %rax	#, tope
	movq	%rax, 8(%rsp)	# tope, %sfp
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, tope
	ja	.L23	#,
.L18:
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	subq	%rbp, %r12	# pos_pivot, tmp145
	leaq	4(%rbx,%rbp,4), %rbx	#, vector
	subq	$1, %r12	#, tope
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %r12	#, tope
	ja	.L24	#,
	movq	16(%rsp), %r13	# %sfp, pos_pivot
	movq	24(%rsp), %r15	# %sfp, tope
	movq	32(%rsp), %r14	# %sfp, vector
.L17:
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	subq	%r13, %r15	# pos_pivot, tmp148
	leaq	4(%r14,%r13,4), %r14	#, vector
	subq	$1, %r15	#, tope
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %r15	#, tope
	ja	.L25	#,
.L16:
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	movq	72(%rsp), %rax	# %sfp, tope
	movq	136(%rsp), %rcx	# %sfp, pos_pivot
	movq	80(%rsp), %rsi	# %sfp, vector
	subq	%rcx, %rax	# pos_pivot, tope
	subq	$1, %rax	#, tope
	leaq	4(%rsi,%rcx,4), %rcx	#, vector
	movq	%rax, 72(%rsp)	# tope, %sfp
	movq	%rcx, 80(%rsp)	# vector, %sfp
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, tope
	ja	.L26	#,
.L15:
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	movq	56(%rsp), %rax	# %sfp, tope
	movq	128(%rsp), %rdx	# %sfp, pos_pivot
	movq	64(%rsp), %rsi	# %sfp, vector
	subq	%rdx, %rax	# pos_pivot, tope
	subq	$1, %rax	#, tope
	leaq	4(%rsi,%rdx,4), %rcx	#, vector
	movq	%rax, 56(%rsp)	# tope, %sfp
	movq	%rcx, 64(%rsp)	# vector, %sfp
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, tope
	ja	.L27	#,
.L14:
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	movq	40(%rsp), %rax	# %sfp, tope
	movq	120(%rsp), %rcx	# %sfp, pos_pivot
	movq	48(%rsp), %rdx	# %sfp, vector
	subq	%rcx, %rax	# pos_pivot, tope
	subq	$1, %rax	#, tope
	leaq	4(%rdx,%rcx,4), %rsi	#, vector
	movq	%rax, 40(%rsp)	# tope, %sfp
	movq	%rsi, 48(%rsp)	# vector, %sfp
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, tope
	ja	.L28	#,
.L13:
# quick_sort.c:38: 	quick_sort(vector + pos_pivot + 1, tope - pos_pivot - 1);
	movq	96(%rsp), %rax	# %sfp, tope
	movq	112(%rsp), %rdx	# %sfp, pos_pivot
	movq	88(%rsp), %rdi	# %sfp, vector
	subq	%rdx, %rax	# pos_pivot, tope
	subq	$1, %rax	#, tope
	leaq	4(%rdi,%rdx,4), %rcx	#, vector
	movq	%rax, 96(%rsp)	# tope, %sfp
	movq	%rcx, 88(%rsp)	# vector, %sfp
# quick_sort.c:32: 	if (tope <= 1)
	cmpq	$1, %rax	#, tope
	ja	.L12	#,
.L11:
# quick_sort.c:39: }
	addq	$184, %rsp	#,
	.cfi_def_cfa_offset 56
	popq	%rbx	#
	.cfi_def_cfa_offset 48
	popq	%rbp	#
	.cfi_def_cfa_offset 40
	popq	%r12	#
	.cfi_def_cfa_offset 32
	popq	%r13	#
	.cfi_def_cfa_offset 24
	popq	%r14	#
	.cfi_def_cfa_offset 16
	popq	%r15	#
	.cfi_def_cfa_offset 8
	ret	
	.cfi_endproc
.LFE24:
	.size	quick_sort, .-quick_sort
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	" %i "
.LC1:
	.string	"]"
	.text
	.p2align 4
	.globl	mostrar_vector
	.type	mostrar_vector, @function
mostrar_vector:
.LFB25:
	.cfi_startproc
	pushq	%r13	#
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12	#
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12	# tmp90, vector
# quick_sort.c:44: 	printf("[");
	movl	$91, %edi	#,
# quick_sort.c:43: {
	pushq	%rbp	#
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rsi, %rbp	# tmp91, tope
	pushq	%rbx	#
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp	#,
	.cfi_def_cfa_offset 48
# quick_sort.c:44: 	printf("[");
	call	putchar@PLT	#
# quick_sort.c:45: 	for (size_t i = 0; i < tope; i++)
	testq	%rbp, %rbp	# tope
	je	.L41	#,
# quick_sort.c:45: 	for (size_t i = 0; i < tope; i++)
	xorl	%ebx, %ebx	# i
	leaq	.LC0(%rip), %r13	#, tmp89
	.p2align 4,,10
	.p2align 3
.L42:
# quick_sort.c:46: 		printf(" %i ", vector[i]);
	movl	(%r12,%rbx,4), %esi	# MEM[(int *)vector_10(D) + i_15 * 4], MEM[(int *)vector_10(D) + i_15 * 4]
	movq	%r13, %rdi	# tmp89,
	xorl	%eax, %eax	#
# quick_sort.c:45: 	for (size_t i = 0; i < tope; i++)
	addq	$1, %rbx	#, i
# quick_sort.c:46: 		printf(" %i ", vector[i]);
	call	printf@PLT	#
# quick_sort.c:45: 	for (size_t i = 0; i < tope; i++)
	cmpq	%rbx, %rbp	# i, tope
	jne	.L42	#,
.L41:
# quick_sort.c:48: }
	addq	$8, %rsp	#,
	.cfi_def_cfa_offset 40
# quick_sort.c:47: 	printf("]\n");
	leaq	.LC1(%rip), %rdi	#, tmp88
# quick_sort.c:48: }
	popq	%rbx	#
	.cfi_def_cfa_offset 32
	popq	%rbp	#
	.cfi_def_cfa_offset 24
	popq	%r12	#
	.cfi_def_cfa_offset 16
	popq	%r13	#
	.cfi_def_cfa_offset 8
# quick_sort.c:47: 	printf("]\n");
	jmp	puts@PLT	#
	.cfi_endproc
.LFE25:
	.size	mostrar_vector, .-mostrar_vector
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB26:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
# quick_sort.c:56: 	mostrar_vector(elementos, cantidad);
	movl	$13, %esi	#,
# quick_sort.c:52: {
	subq	$64, %rsp	#,
	.cfi_def_cfa_offset 80
# quick_sort.c:53: 	int elementos[] = { 5, 4, 2, 6, 3, 7, 1, 1, 55, 3, 7, 8, 19 };
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp97
	movq	%rax, 56(%rsp)	# tmp97, D.3058
	movabsq	$17179869189, %rax	#, tmp97
# quick_sort.c:56: 	mostrar_vector(elementos, cantidad);
	movq	%rsp, %rbp	#, tmp92
# quick_sort.c:53: 	int elementos[] = { 5, 4, 2, 6, 3, 7, 1, 1, 55, 3, 7, 8, 19 };
	movl	$19, 48(%rsp)	#, elementos[12]
# quick_sort.c:56: 	mostrar_vector(elementos, cantidad);
	movq	%rbp, %rdi	# tmp92,
# quick_sort.c:53: 	int elementos[] = { 5, 4, 2, 6, 3, 7, 1, 1, 55, 3, 7, 8, 19 };
	movq	%rax, (%rsp)	# tmp100, MEM <unsigned long> [(int *)&elementos]
	movabsq	$25769803778, %rax	#, tmp101
	movq	%rax, 8(%rsp)	# tmp101, MEM <unsigned long> [(int *)&elementos + 8B]
	movabsq	$30064771075, %rax	#, tmp102
	movq	%rax, 16(%rsp)	# tmp102, MEM <unsigned long> [(int *)&elementos + 16B]
	movabsq	$4294967297, %rax	#, tmp103
	movq	%rax, 24(%rsp)	# tmp103, MEM <unsigned long> [(int *)&elementos + 24B]
	movabsq	$12884901943, %rax	#, tmp104
	movq	%rax, 32(%rsp)	# tmp104, MEM <unsigned long> [(int *)&elementos + 32B]
	movabsq	$34359738375, %rax	#, tmp105
	movq	%rax, 40(%rsp)	# tmp105, MEM <unsigned long> [(int *)&elementos + 40B]
# quick_sort.c:56: 	mostrar_vector(elementos, cantidad);
	call	mostrar_vector	#
# quick_sort.c:58: 	quick_sort(elementos, cantidad);
	movl	$13, %esi	#,
	movq	%rbp, %rdi	# tmp92,
	call	quick_sort	#
# quick_sort.c:60: 	mostrar_vector(elementos, cantidad);
	movl	$13, %esi	#,
	movq	%rbp, %rdi	# tmp92,
	call	mostrar_vector	#
# quick_sort.c:63: }
	movq	56(%rsp), %rax	# D.3058, tmp98
	subq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp98
	jne	.L51	#,
	addq	$64, %rsp	#,
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax	#
	popq	%rbp	#
	.cfi_def_cfa_offset 8
	ret	
.L51:
	.cfi_restore_state
	call	__stack_chk_fail@PLT	#
	.cfi_endproc
.LFE26:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.1.0"
	.section	.note.GNU-stack,"",@progbits
