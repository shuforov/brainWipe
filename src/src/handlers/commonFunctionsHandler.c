#include <genesis.h>
#include "../../headers/commonConstants.h"
#include "../../headers/handlers/commonFunctionsHandler.h"

CFH_SplitDigits splitNumberData;

void CFH_resetSplitNumberData() {
  splitNumberData.originNum = 0;
  for (u16 i = 0; i < 4; i++) {
    splitNumberData.digits[0] = 0;
  }
  splitNumberData.count = 0;
}

CFH_SplitDigits CFH_splitDigits(u16 number) {
  CFH_resetSplitNumberData();
  splitNumberData.originNum = number;
  if (splitNumberData.originNum == 0) {
    splitNumberData.digits[0] = 0;
    splitNumberData.count = 1;
  } else {
    // Extract digits from end to start
    while (splitNumberData.originNum > 0) {
      splitNumberData.digits[splitNumberData.count++] =
          splitNumberData.originNum % 10;
      splitNumberData.originNum /= 10;
    }

    // reverse digits[]
    for (u16 i = 0; i < splitNumberData.count / 2; i++) {
      u16 temp = splitNumberData.digits[i];
      splitNumberData.digits[i] =
          splitNumberData.digits[splitNumberData.count - 1 - i];
      splitNumberData.digits[splitNumberData.count - 1 - i] = temp;
    }
  }
  return splitNumberData;
}

CFH_transformDigits CFH_transformDigitsToHex(CFH_SplitDigits splitDigits) {
  CFH_transformDigits result;
  result.count = splitDigits.count;
  for (u16 i = 0; i < result.count; i++) {
    result.hexDigits[i] = NUMBERS_HEX[splitDigits.digits[i]];
  }
  return result;
}
