# Concurrency 1: The Producer-Consumer Problem
#
# File: concurrency.S
#
# Group 37: Taylor Alexander Brown & Lucien Armand Tamdja Tamno
# Oregon State University
# CS 444: Operating Systems II
# Fall 2017

        .global supports_rdrand
        .global rdrand

supports_rdrand:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    $1, %rax        # configure cpuid to get version information
        xor     %rcx, %rcx      # zero the destination register
        cpuid                   # get cpu information
        shr     $30, %rcx       # inspect bit 30
        movq    %rcx, %rax      # return 1 if rdrand supported
        popq    %rbp
        ret

rdrand:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    $11, %rcx       # set retry counter to 11
.rdrand_retry:                  # for each retry
        dec     %rcx            # decrement retry counter
        jz      .rdrand_quit    # quit if max retries
        rdrand  %rax            # read random number
        jnc     .rdrand_retry   # retry if carry flag not set
.rdrand_quit:
        popq    %rbp
        ret
