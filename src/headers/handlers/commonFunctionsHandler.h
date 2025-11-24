#ifndef COMMON_FUNCTIONS_HANDLER_H
#define COMMON_FUNCTIONS_HANDLER_H

#include <genesis.h>

typedef struct {
  u16 originNum;
  u16 digits[3];
  u16 count;
} CFH_SplitDigits;

CFH_SplitDigits CFH_splitDigits(u16 number);

#endif
