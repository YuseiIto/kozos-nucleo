#include "targets/STM32F303K8/system.h"
#include "structures/ring_buffer.h"

ringBuffer_t buf;

void putstr(char *str, uint16_t len)
{

 uint8_t q = 0;
 ringBuffer_result_t res = push(&buf, str[0]);

 while (res == OK && q < len)
 {
  res = push(&buf, str[q]);
  q++;
 }

 USART2->TDR = 'A';
}

int usart2_handler(uint8_t o)
{
 if ((USART2->ISR & (uint32_t)(0b1 << 6))) //TC bit
 {
  USART2->ICR = 0b1 << 6;

  uint8_t a;

  ringBuffer_result_t res = pop(&buf, &a);

  if (res == OK)
  {
   USART2->TDR = a;
  }
 }
 else if ((USART2->ISR & (uint32_t)(0b1 << 5))) //RXNE bit
 {
 }

 return 0;
}
