#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H

#include <genesis.h>

void setTimerTotalTime(u16 tTime);
void setTimerTimeLeft(u16 tTIme);
void activateTimer();
void deactivateTimer();
u16 getSegmentNum();
u16 getTimerTotalTime();
u16 getTimerTimeLeft();

#endif
