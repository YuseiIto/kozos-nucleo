#include <stdint.h>
#include "targets/STM32F303K8/system.h"

/*
*PA_2=TX
*PA_15=RX
*/

void configureUSBSerial()
{
 RCC->AHBENR |= (1 << 17);
 GPIOA->MODER = (0b10 << 2 * 2);
 GPIOA->MODER |= (0b10 << 2 * 15);
 GPIOA->AFRL = 0b0111 << (4 * 2);
 GPIOA->AFRH = 0b0111 << (4 * 8);

 // Configure UART
 RCC->APB1ENR |= (0b1 << 17);
 USART2->BRR = 8000000L / 115200L;
 USART2->CR1 |= (0b1 << 3); // Transmitter enable
 USART2->CR1 |= (0b1 << 2); // Receiver enable
 USART2->CR1 |= (0b1 << 0); //Enable USART
}

int main(void)
{

 // Configure Blink
 RCC->AHBENR |= (1 << 18);
 GPIOB->MODER = (0b01 << 2 * 3); // Set '01' to GPIOB port 3
 GPIOB->OTYPER = 0x0000;         // All-push pull
 GPIOB->PUPDR = 0x000000000;     // No pullup-pulldown

 configureUSBSerial();

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

   USART2->TDR = 'A';
  }
  i++;
 }
 return 0;
}
