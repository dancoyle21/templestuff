// autogenerated file see scripts/syscall_generate.go
	.text
	.globl asm_syscall_RawPutChar
	.type asm_syscall_RawPutChar, @function
asm_syscall_RawPutChar:
	push_registers
	movq 0x10(%rbp), %rdi
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
	.globl asm_syscall_RedSeaFilesFind
	.type asm_syscall_RedSeaFilesFind, @function
asm_syscall_RedSeaFilesFind:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	movq 0x20(%rbp), %rdx
	call syscall_RedSeaFilesFind
	pop_registers_except_rax
	ret $0x18

	.text
	.globl asm_syscall_RedSeaFileWrite
	.type asm_syscall_RedSeaFileWrite, @function
asm_syscall_RedSeaFileWrite:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	movq 0x20(%rbp), %rdx
	movq 0x28(%rbp), %rcx
	movq 0x30(%rbp), %r8
	movq 0x38(%rbp), %r9
	pushq 0x40(%rbp)
	call syscall_RedSeaFileWrite
	addq $0x8, %rsp
	pop_registers_except_rax
	ret $0x38

	.text
	.globl asm_syscall_RedSeaMkDir
	.type asm_syscall_RedSeaMkDir, @function
asm_syscall_RedSeaMkDir:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	movq 0x20(%rbp), %rdx
	movq 0x28(%rbp), %rcx
	call syscall_RedSeaMkDir
	pop_registers_except_rax
	ret $0x20

	.text
	.globl asm_syscall_SysTimerRead
	.type asm_syscall_SysTimerRead, @function
asm_syscall_SysTimerRead:
	push_registers_except_rax
	call syscall_SysTimerRead
	pop_registers_except_rax
	ret

	.text
	.globl asm_syscall_Snd
	.type asm_syscall_Snd, @function
asm_syscall_Snd:
	// don't do anything
	movq $0, %rax
	ret $0x8

	.text
	.globl asm_syscall_MHeapCtrl
	.type asm_syscall_MHeapCtrl, @function
asm_syscall_MHeapCtrl:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	call syscall_MHeapCtrl
	pop_registers_except_rax
	ret $0x8

	.text
	.globl asm_syscall_MSize
	.type asm_syscall_MSize, @function
asm_syscall_MSize:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	call syscall_MSize
	pop_registers_except_rax
	ret $0x8

	.text
	.globl asm_syscall_NowDateTimeStruct
	.type asm_syscall_NowDateTimeStruct, @function
asm_syscall_NowDateTimeStruct:
	push_registers
	movq 0x10(%rbp), %rdi
	call syscall_NowDateTimeStruct
	pop_registers
	ret $0x8

	.text
	.globl asm_syscall_GetS
	.type asm_syscall_GetS, @function
asm_syscall_GetS:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	movq 0x20(%rbp), %rdx
	call syscall_GetS
	pop_registers_except_rax
	ret $0x18

	.text
	.globl asm_syscall_Busy
	.type asm_syscall_Busy, @function
asm_syscall_Busy:
	push_registers
	movq 0x10(%rbp), %rdi
	call syscall_Busy
	pop_registers
	ret $0x8

	.text
	.globl asm_syscall_TaskDerivedValsUpdate
	.type asm_syscall_TaskDerivedValsUpdate, @function
asm_syscall_TaskDerivedValsUpdate:
	// don't do anything
	ret $0x10

	.text
	.globl asm_syscall_Yield
	.type asm_syscall_Yield, @function
asm_syscall_Yield:
	push_registers
	call syscall_Yield
	pop_registers
	ret

	.text
	.globl asm_syscall_KbdTypeMatic
	.type asm_syscall_KbdTypeMatic, @function
asm_syscall_KbdTypeMatic:
	// don't do anything
	movq $0, %rax
	ret $0x8

	.text
	.globl asm_syscall_Spawn
	.type asm_syscall_Spawn, @function
asm_syscall_Spawn:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	movq 0x20(%rbp), %rdx
	movq 0x28(%rbp), %rcx
	movq 0x30(%rbp), %r8
	movq 0x38(%rbp), %r9
	pushq 0x40(%rbp)
	call syscall_Spawn
	addq $0x8, %rsp
	pop_registers_except_rax
	ret $0x38

	.text
	.globl asm_syscall_TaskStkNew
	.type asm_syscall_TaskStkNew, @function
asm_syscall_TaskStkNew:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	call syscall_TaskStkNew
	pop_registers_except_rax
	ret $0x10

	.text
	.globl asm_syscall_CallStkGrow
	.type asm_syscall_CallStkGrow, @function
asm_syscall_CallStkGrow:
	push_registers_except_rax
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	movq 0x20(%rbp), %rdx
	call syscall_CallStkGrow
	pop_registers_except_rax
	ret $0x18

	.text
	.globl asm_lilith_lock_task
	.type asm_lilith_lock_task, @function
asm_lilith_lock_task:
	push_registers
	movq 0x10(%rbp), %rdi
	call lilith_lock_task
	pop_registers
	ret $0x8

	.text
	.globl asm_lilith_unlock_task
	.type asm_lilith_unlock_task, @function
asm_lilith_unlock_task:
	push_registers
	movq 0x10(%rbp), %rdi
	call lilith_unlock_task
	pop_registers
	ret $0x8

	.text
	.globl asm_lilith_replace_syscall
	.type asm_lilith_replace_syscall, @function
asm_lilith_replace_syscall:
	push_registers
	movq 0x10(%rbp), %rdi
	movq 0x18(%rbp), %rsi
	call lilith_replace_syscall
	pop_registers
	ret $0x10

	.text
	.globl asm_lilith_wait_for_enqueued_task
	.type asm_lilith_wait_for_enqueued_task, @function
asm_lilith_wait_for_enqueued_task:
	push_registers
	movq 0x10(%rbp), %rdi
	call lilith_wait_for_enqueued_task
	pop_registers
	ret $0x8

	.text
	.globl asm_lilith_signal_enqueued_task
	.type asm_lilith_signal_enqueued_task, @function
asm_lilith_signal_enqueued_task:
	push_registers
	movq 0x10(%rbp), %rdi
	call lilith_signal_enqueued_task
	pop_registers
	ret $0x8

	.text
	.globl asm_lilith_wait_for_idle_task
	.type asm_lilith_wait_for_idle_task, @function
asm_lilith_wait_for_idle_task:
	push_registers
	movq 0x10(%rbp), %rdi
	call lilith_wait_for_idle_task
	pop_registers
	ret $0x8

	.text
	.globl asm_lilith_signal_idle_task
	.type asm_lilith_signal_idle_task, @function
asm_lilith_signal_idle_task:
	push_registers
	movq 0x10(%rbp), %rdi
	call lilith_signal_idle_task
	pop_registers
	ret $0x8

