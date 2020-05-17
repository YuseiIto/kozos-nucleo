#include <stdint.h>
#include "addr.h"
#include "regDef.h"

/*Pheripheral definitions*/
#define USART1 ((USART_t *)USART_1_BASE)
#define USART2 ((USART_t *)USART_2_BASE)
#define RCC ((RCC_t *)RCC_BASE)
#define GPIOA ((GPIO_t *)GPIO_A_BASE)
#define GPIOB ((GPIO_t *)GPIO_B_BASE)
#define NVIC ((NVIC_t *)NVIC_BASE)

int configureUSBSerial(void)
{

  RCC->AHBENR |= (1 << 17);
  GPIOA->MODER = (uint32_t)(0b10 << (2 * 2));
  GPIOA->MODER |= (uint32_t)(0b10 << (2 * 15));
  GPIOA->AFRL = 0b0111 << (4 * 2);
  GPIOA->AFRH = 0b0111 << (4 * 7);

  // Configure UART
  RCC->APB1ENR |= (0b1 << 17);
  USART2->BRR = 8000000L / 115200L;
  //USART2->CR1 |= (0b1 << 7); // TX interrupt
  USART2->CR1 |= (0b1 << 5); // RX interrupt
  USART2->CR1 |= (0b1 << 3); // Transmitter enable
  USART2->CR1 |= (0b1 << 2); // Receiver enable
  USART2->CR1 |= (0b1 << 0); // Enable USART
  NVIC->ISER[1] = (0b1 << 6);

  return 0;
}

int systemInit()
{
  configureUSBSerial();
  return 0;
}
