
ENTRY(_start)
MEMORY
{
 RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 12K
 FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 64K 
}

SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

 .text :
  {
    . = ALIGN(4);
    __text_start = .;
    *(.text)
    *(.text*)
    . = ALIGN(4);
    __text_end = .;
  } >FLASH

  .rodata :
  {
    . = ALIGN(4);
    __rodata_start = .;
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
    __rodata_end = .;
  } >FLASH


  __idata_start = LOADADDR(.data); /* Address on ROM */

  .data : 
  {
    . = ALIGN(4);
    __data_start = .; 
    *(.data) 
    *(.data*)

    . = ALIGN(4);
    __data_end = .; 
  } >RAM AT> FLASH

  
  . = ALIGN(4);
  .bss :
  {
    __bss_start = .;
    *(.bss)
    *(.bss*)
    . = ALIGN(4);
    __bss_end = .; 
  } >RAM

  .heap : {
        __heap_start = .;
        /* 1KiB heap */ 
        . = . + 1024 ;
        . = ALIGN(4);
        __heap_end = .;
  }> RAM

  .stack : {
        __stack_end = .;
        /* 1KiB stack*/
        __stack_start = __stack_end + 1024;
  }> RAM

}


