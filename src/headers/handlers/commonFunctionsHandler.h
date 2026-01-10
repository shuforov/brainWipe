#ifndef COMMON_FUNCTIONS_HANDLER_H
#define COMMON_FUNCTIONS_HANDLER_H

#include <genesis.h>

typedef struct {
  u16 originNum;
  u16 digits[4];
  u16 count;
} CFH_SplitDigits;

typedef struct {
  u16 hexDigits[4];
  u16 count;
} CFH_transformDigits;

CFH_SplitDigits CFH_splitDigits(u16 number);
CFH_transformDigits CFH_transformDigitsToHex(CFH_SplitDigits splitDigits);

#endif
