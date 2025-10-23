#ifndef BUTTON_ANIMATION_HANDLER_H
#define BUTTON_ANIMATION_HANDLER_H

#include <genesis.h>

void buttonAnimation();
void setButtonAnimationState(u16 buttonType, bool state);
void buttonAnimationProcess(u16 buttonIndex, u16 buttonType[]);
bool isButtonAnimation();

#endif
