#include "targets/STM32F303K8/system.h"
#include "structures/ring_buffer.h"
#include "lib.h"

ringBuffer_t buf;

void flushc()
{
 uint8_t c;
 ringBuffer_result_t res = pop(&buf, &c);
 if (res == OK)
 {
  USART2->TDR = c;
 }
}

void putstrn(char *str, uint16_t len)
{

 uint8_t q = 0;
 ringBuffer_result_t res = push(&buf, str[0]);

 uint8_t flg = 0;
 if ((USART2->ISR & 0b1 << 7) != 0)
  flg = 1;

 while (res == OK && q < len)
 {
  res = push(&buf, str[q]);
  q++;
 }

 if (flg == 1)
 {
  flushc();
 }
}

void putstr(char *str)
{
 putstrn(str, StrLen(str));
}

int usart2_handler(uint8_t o)
{
 if ((USART2->ISR & (uint32_t)(0b1 << 6))) //TC bit
 {
  USART2->ICR = 0b1 << 6;

  flushc();
 }
 else if ((USART2->ISR & (uint32_t)(0b1 << 5))) //RXNE bit
 {
 }

 return 0;
}
