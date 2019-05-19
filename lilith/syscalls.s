	.text
	.globl asm_syscall_RawPutChar
	.type asm_syscall_RawPutChar, @function
asm_syscall_RawPutChar:
	push_registers
	movq  0x10(%rbp), %rdi
	call syscall_RawPutChar
	pop_registers
	ret $0x8

	.text
	.globl asm_syscall_DrvLock
	.type asm_syscall_DrvLock, @function
asm_syscall_DrvLock:
	// don't do anything
	movq $0, %rax
	ret $0x8

	.text
	.globl asm_syscall_JobsHndlr
	.type asm_syscall_JobsHndlr, @function
asm_syscall_JobsHndlr:
	// don't do anything
	movq $0, %rax
	ret $0x8

	.text
	.globl asm_syscall_MAlloc
	.type asm_syscall_MAlloc, @function
asm_syscall_MAlloc:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	call syscall_MAlloc
	pop_registers_except_rax
	ret $0x10
	
	.text
	.globl asm_syscall_Free
	.type asm_syscall_Free, @function
asm_syscall_Free:
	push_registers
	movq 0x10(%rbp), %rdi
	call syscall_Free
	pop_registers
	ret $0x8

	.text
	.globl asm_syscall_RedSeaFileFind
	.type asm_syscall_RedSeaFileFind, @function
asm_syscall_RedSeaFileFind:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	movq 0x20(%rbp), %rdx
	movq 0x28(%rbp), %rcx
	movq 0x30(%rbp), %r8
	call syscall_RedSeaFileFind
	pop_registers_except_rax
	ret $0x28

	.text
	.globl asm_syscall_RedSeaFileRead
	.type asm_syscall_RedSeaFileRead, @function
asm_syscall_RedSeaFileRead:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	movq 0x20(%rbp), %rdx
	movq 0x28(%rbp), %rcx
	movq 0x30(%rbp), %r8
	call syscall_RedSeaFileRead
	pop_registers_except_rax
	ret $0x28

	.text
	.globl asm_syscall_SysTimerRead
	.type asm_syscall_SysTimerRead, @function
asm_syscall_SysTimerRead:
	push_registers_except_rax
	call syscall_SysTimerRead
	pop_registers_except_rax
	ret
	
	