.syntax unified
.cpu cortex-m4
.thumb
.global _start

.section .text.start
_start:
    ldr sp,=__stack_start
    bl data_init
    bl bss_clear
    bl systemInit
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
        str r4,[r1]
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

default_handler:
    bx lr

/*
 * Interrupt Vector table
 * Need evidence?
 * Refer to "Reference manual RM0316" by STMicroinstruments at https://www.st.com/resource/en/reference_manual/dm00043574-stm32f303xb-c-d-e-stm32f303x6-8-stm32f328x8-stm32f358xc-stm32f398xe-advanced-arm-based-mcus-stmicroelectronics.pdf
 */

.section .isr_vector,"a"
    .word __stack_start
    .word _start
    .word default_handler// NMI
    .word default_handler // Hard fault
    .word default_handler // Memory management fault
    .word default_handler // Bus fault
    .word default_handler // Usage fault
    .space 16             // Reserved
    .word svc_handler     // Superviser call
    .word default_handler // PendSV
    .word default_handler // Systick
    .word default_handler // WWDG
    .word default_handler // PVD
    .word default_handler // TAMPER_STAMP
    .word default_handler // RTC_WKUP
    .word default_handler // FLASH
    .word default_handler // RCC
    .word default_handler // EXIT0
    .word default_handler // EXTI1
    .word default_handler // EXTI2_TS
    .word default_handler // EXIT3
    .word default_handler // EXTI4
    .word default_handler // DMA1 CH1
    .word default_handler // DMA1 CH2
    .word default_handler // DMA1 CH3
    .word default_handler // DMA1 CH4
    .word default_handler // DMA1 CH5
    .word default_handler // DMA1 CH6
    .word default_handler // DMA1 CH7
    .word default_handler // ADC1_2
    .word default_handler // CAN_TX
    .word default_handler // CAN_RX0
    .word default_handler // CAN_RX1
    .word default_handler // CAN_SCE
    .word default_handler // EXIT9_5
    .word default_handler // TIM1_BRK/TIM15
    .word default_handler // TIM1_UP/TIM16
    .word default_handler // TIM1_TRG_COM/TIM17
    .word default_handler // TIM1_CC
    .word default_handler // TIM2
    .word default_handler // TIM3
    .space 4
    .word default_handler // I2C1_EV
    .word default_handler // I2C2_ER
    .space 12
    .word default_handler // SPI1
    .space 8
    .word  default_handler  // UART1
    .word usart2_handler  // UART2
    .word  default_handler  // UART3
    .word default_handler // EXTI[15:10]
    .word default_handler // RTC_Alarm
    .space 52
    .word default_handler // TIM6_DAC1
    .word default_handler // TIM7_DAC2
    .space 36
    .word default_handler // COMP2
    .word default_handler // COMP4,6
    .word 64
    .word default_handler //FPU
