#include "addr.h"

typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t BRR;
  volatile uint32_t GTPR;
  volatile uint32_t RTOR;
  volatile uint32_t RQR;
  volatile uint32_t ISR;
  volatile uint32_t ICR;
  volatile uint32_t RDR;
  volatile uint32_t TDR;
} USART_t;

typedef struct
{
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFRL;
  volatile uint32_t AFRH;
  volatile uint32_t BRR;
} GPIO_t;

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BCDR;
  volatile uint32_t CSR;
  volatile uint32_t AHBRSTR;
  volatile uint32_t CFGR2;
  volatile uint32_t CFGR3;
} RCC_t;

typedef struct
{
  volatile uint32_t CCR;
  volatile uint32_t CNDTR;
  volatile uint32_t CPAR;
  volatile uint32_t CMAR;
} DMA_Channel_t;

typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
  DMA_Channel_t CH1;
  DMA_Channel_t CH2;
  DMA_Channel_t CH3;
  DMA_Channel_t CH4;
  DMA_Channel_t CH5;
  DMA_Channel_t CH6;
  DMA_Channel_t CH7;
} DMA_t;

typedef struct
{
  volatile uint32_t ISER[8]; /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
  uint32_t RESERVED0[24];
  volatile uint32_t ICER[8]; /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
  uint32_t RESERVED1[24];
  volatile uint32_t ISPR[8]; /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
  uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8]; /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
  uint32_t RESERVED3[24];
  volatile uint32_t IABR[8]; /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
  uint32_t RESERVED4[56];
  volatile uint8_t IP[240]; /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
  uint32_t RESERVED5[644];
  volatile uint32_t STIR; /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
} NVIC_t;
