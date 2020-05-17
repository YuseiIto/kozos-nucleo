#pragma once
#include <stdint.h>

uint16_t StrLen(char *str)
{
 uint16_t i = 0;
 while (*str++)
  i++;

 return i;
}
