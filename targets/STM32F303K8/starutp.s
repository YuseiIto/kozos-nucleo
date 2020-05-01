.syntax unified
.cpu cortex-m4
.fpu softfvp
.thumb
.global _start

.section .text.start
    ldr sp,=__stack_start
    bl data_init
    bl bss_clear
    bl main

LoopForever:
    b  LoopForever

/*
 * data section initializer
 * Copies idata on Flash to RAM data section
 * r1 : Address being copied to
 * r2 : Address begin copied from
 * r3 : Address of end of copied data
 */

data_init:
    ldr r1, =__data_start
    ldr r2, =__idata_start
    ldr r3, =__data_end
    1:
        cmp r1,r3
        beq 2f
        ldr r4,[r2]
        str [r4],[r1]
        adds r1,r1,#4
        adds r2,r2,#4
        b 1b
    2: 
        bx lr

/*
 * BSS section Initializer.
 * filles BSS section with 0
 * Using r3 as a Zero register
 */

bss_clear:
    ldr r1,=__bss_start
    ldr r2,=__bss_end
    movs r3,0
    1:
        cmp r1,r2
        beq 2f
        str r3,[r1]
        adds r1,r1,#4
        b 1b
    2:
        bx lr


/*
 * Interrupt Vector table
 */

.section .isr_vector,"a"
    .word __stack_start
    .word _start
