.text
.global machine_switch
.global delete

delete:
	# restore regs and run the thread
	movq (%rdi), %rsp
    	popq %rbp
	popq %r15
	popq %r14
	popq %r13
    	popq %r12	
    	popq %r11
    	popq %r10
   	popq %rbx
    	popq %rax
    	ret

machine_switch:

    #At first machine switch function should be called with 0 as the first argument and first Thread as the second argument
    cmpq $0, %rdi
    je .initial


    # %rsi = old thread / %rdi = New Thread

    
	#save current regs
	pushq %rax
	pushq %rbx
	pushq %r10
	pushq %r11
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
        pushq %rbp
	movq  %rsp,(%rsi)


   	#load the regs 
    	movq (%rdi), %rsp
    	popq %rbp
	popq %r15
	popq %r14
	popq %r13
    	popq %r12	
    	popq %r11
    	popq %r10
   	popq %rbx
    	popq %rax
    	ret

.initial:# starting first Thread
    movq (%rsi),%rsp
    ret

