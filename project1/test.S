        .global testval
        .global testproc

testval:
        .quad   123

testproc:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    testval, %rax
        popq    %rbp
        ret
