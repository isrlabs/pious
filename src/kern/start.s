.section .init
.globl _start
_start:
	b	_main

.section .text
.extern main
.globl _main
_main:
	mov	sp,	#0x8000
	b	main
