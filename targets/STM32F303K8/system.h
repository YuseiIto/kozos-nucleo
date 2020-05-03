#include <stdint.h>
#include "addr.h"
#include "regDef.h"

/*Pheripheral definitions*/
#define USART1 ((USART_t *)USART_1_BASE)
#define USART2 ((USART_t *)USART_2_BASE)
#define RCC ((RCC_t *)RCC_BASE)
#define GPIOA ((GPIO_t *)GPIO_A_BASE)
#define GPIOB ((GPIO_t *)GPIO_B_BASE)

int systemInit()
{
  return 0;
}
