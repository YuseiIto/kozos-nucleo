#include <stdint.h>
#include "targets/STM32F303K8/system.h"

/*
*PA_2=TX
*PA_15=RX
*/
int svc_handler(uint8_t o)
{
 USART2->TDR = 'S';
 return 0;
}

int usart2_handler(uint8_t o)
{
 NVIC->ICPR[1] &= ~(uint32_t)(0b1 << 6);
 USART2->TDR = USART2->RDR;
 return 0;
}

int main(void)
{

 // Configure Blink
 RCC->AHBENR |= (1 << 18);
 GPIOB->MODER = (0b01 << 2 * 3); // Set '01' to GPIOB port 3
 GPIOB->OTYPER = 0x0000;         // All-push pull
 GPIOB->PUPDR = 0x000000000;     // No pullup-pulldown

 int i = 1;
 while (1)
 {
  if (i > 500000)
  {
   i = 0;

   if (GPIOB->ODR & (1 << 3))
   {
    GPIOB->ODR &= ~(1 << 3);
   }
   else
   {
    GPIOB->ODR |= (1 << 3);
   }
  }
  i++;
 }
 return 0;
}
