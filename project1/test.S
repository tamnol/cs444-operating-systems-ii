        .global testval
        .global testproc
        .global supports_rdrand
        .global rdrand

testval:
        .quad 123

testproc:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    testval, %rax
        popq    %rbp
        ret

supports_rdrand:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    $1, %rax
        xor     %rcx, %rcx      # zero the destination register
        cpuid                   # get cpu information
        shr     $30, %rcx       # shift off unused bits
        and     $1, %rcx        # rdrand supported if 1
        movq    %rcx, %rax      # store return value
        popq    %rbp
        ret

rdrand:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    $11, %rcx       # set retry counter to 11
.rdrand_retry:
        dec     %rcx            # decrement retry counter
        jz      .rdrand_quit    # quit if max retries
        rdrand  %rax            # read random number
        jnc     .rdrand_retry   # retry if carry flag not set
.rdrand_quit:
        popq    %rbp
        ret
