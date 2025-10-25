#ifndef BUTTON_ANIMATION_HANDLER_H
#define BUTTON_ANIMATION_HANDLER_H

#include <genesis.h>

void buttonAnimation();
void setButtonAnimationState(u16 buttonType, bool state);
void buttonAnimationProcess(u16 buttonIndex, u16 buttonType[]);
bool isButtonAnimation();
void stadyButtonsAnimation();
bool isStadyButtonsAnimation();
void setStadyButtonsAnimation(bool state);
bool isStadyButtonsAnimation();
void setTimerPieButtonAnimation(bool state, u16 totalTime);
bool isTimerPieButtonAnimation();
void timerPieButtonAnimation();

#endif
