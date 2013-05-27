	.file	"CallBack_Clavier.c"
	.text
.globl _CallBack_INT_Clavier
	.def	_CallBack_INT_Clavier;	.scl	2;	.type	32;	.endef
_CallBack_INT_Clavier:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	cmpl	$1, %eax
	je	L4
	cmpl	$1, %eax
	jb	L3
	cmpl	$2, %eax
	je	L5
	jmp	L7
L3:
	call	_Lecture_Scan_Code
	jmp	L6
L4:
	call	_Attendre_Scan_Code
	jmp	L6
L5:
	call	_Attendre_Touche_Relache
	jmp	L6
L7:
	jmp	L1
L6:
L1:
	leave
	ret
	.def	_Lecture_Scan_Code;	.scl	2;	.type	32;	.endef
	.def	_Attendre_Scan_Code;	.scl	2;	.type	32;	.endef
	.def	_Attendre_Touche_Relache;	.scl	2;	.type	32;	.endef
