	.file	"CallBack_IRQ.c"
	.text
.globl _CallBack_IRQ0
	.def	_CallBack_IRQ0;	.scl	2;	.type	32;	.endef
_CallBack_IRQ0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
/APP
 # 23 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 23 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 23 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 23 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	call	_Ordonnanceur
	leave
	ret
	.comm	_L_Touche, 2, 1
.globl _CallBack_IRQ1
	.def	_CallBack_IRQ1;	.scl	2;	.type	32;	.endef
_CallBack_IRQ1:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
/APP
 # 60 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 60 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 60 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 60 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	call	_Lecture_Scan_Code
	movw	%ax, _L_Touche
	leave
	ret
	.section .rdata,"dr"
LC0:
	.ascii "IRQ3\12\0"
	.text
.globl _CallBack_IRQ3
	.def	_CallBack_IRQ3;	.scl	2;	.type	32;	.endef
_CallBack_IRQ3:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 78 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 78 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 78 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 78 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC0, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC1:
	.ascii "IRQ4\12\0"
	.text
.globl _CallBack_IRQ4
	.def	_CallBack_IRQ4;	.scl	2;	.type	32;	.endef
_CallBack_IRQ4:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 85 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 85 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 85 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 85 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC1, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC2:
	.ascii "IRQ5\12\0"
	.text
.globl _CallBack_IRQ5
	.def	_CallBack_IRQ5;	.scl	2;	.type	32;	.endef
_CallBack_IRQ5:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 93 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 93 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 93 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 93 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC2, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC3:
	.ascii "IRQ6\12\0"
	.text
.globl _CallBack_IRQ6
	.def	_CallBack_IRQ6;	.scl	2;	.type	32;	.endef
_CallBack_IRQ6:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 101 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 101 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 101 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 101 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC3, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC4:
	.ascii "IRQ7\12\0"
	.text
.globl _CallBack_IRQ7
	.def	_CallBack_IRQ7;	.scl	2;	.type	32;	.endef
_CallBack_IRQ7:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 109 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 109 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 109 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 109 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC4, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC5:
	.ascii "IRQ8\12\0"
	.text
.globl _CallBack_IRQ8
	.def	_CallBack_IRQ8;	.scl	2;	.type	32;	.endef
_CallBack_IRQ8:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 117 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 117 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 117 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 117 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC5, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC6:
	.ascii "IRQ9\12\0"
	.text
.globl _CallBack_IRQ9
	.def	_CallBack_IRQ9;	.scl	2;	.type	32;	.endef
_CallBack_IRQ9:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 125 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 125 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 125 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 125 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC6, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC7:
	.ascii "IRQ10\12\0"
	.text
.globl _CallBack_IRQ10
	.def	_CallBack_IRQ10;	.scl	2;	.type	32;	.endef
_CallBack_IRQ10:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 134 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 134 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 134 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 134 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC7, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC8:
	.ascii "IRQ11\12\0"
	.text
.globl _CallBack_IRQ11
	.def	_CallBack_IRQ11;	.scl	2;	.type	32;	.endef
_CallBack_IRQ11:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 142 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 142 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 142 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 142 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC8, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC9:
	.ascii "IRQ12\12\0"
	.text
.globl _CallBack_IRQ12
	.def	_CallBack_IRQ12;	.scl	2;	.type	32;	.endef
_CallBack_IRQ12:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 150 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 150 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 150 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 150 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC9, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC10:
	.ascii "IRQ13\12\0"
	.text
.globl _CallBack_IRQ13
	.def	_CallBack_IRQ13;	.scl	2;	.type	32;	.endef
_CallBack_IRQ13:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 158 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 158 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 158 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 158 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC10, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC11:
	.ascii "IRQ14\12\0"
	.text
.globl _CallBack_IRQ14
	.def	_CallBack_IRQ14;	.scl	2;	.type	32;	.endef
_CallBack_IRQ14:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 166 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 166 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 166 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 166 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC11, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC12:
	.ascii "IRQ15\12\0"
	.text
.globl _CallBack_IRQ15
	.def	_CallBack_IRQ15;	.scl	2;	.type	32;	.endef
_CallBack_IRQ15:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 174 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 174 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 174 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 174 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC12, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.section .rdata,"dr"
LC13:
	.ascii "Interruption \12\0"
	.text
.globl _CallBack_Defaut
	.def	_CallBack_Defaut;	.scl	2;	.type	32;	.endef
_CallBack_Defaut:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
/APP
 # 184 "CallBack_IRQ.c" 1
	.intel_syntax noprefix 
 # 0 "" 2
 # 184 "CallBack_IRQ.c" 1
	 mov AX,(2<<3)
 # 0 "" 2
 # 184 "CallBack_IRQ.c" 1
	 mov DS,AX
 # 0 "" 2
 # 184 "CallBack_IRQ.c" 1
	.att_syntax noprefix 

 # 0 "" 2
/NO_APP
	movl	$LC13, %eax
	movl	%eax, (%esp)
	call	_Affiche_Chaine
	leave
	ret
	.def	_Ordonnanceur;	.scl	2;	.type	32;	.endef
	.def	_Lecture_Scan_Code;	.scl	2;	.type	32;	.endef
	.def	_Affiche_Chaine;	.scl	2;	.type	32;	.endef
