#include <genesis.h>

#define NUMBER_PIE_TILES 6
#define FINAL_COUNTDOWN_TIME 5

bool timerActive = false;
u16 totalTime;
u16 timeLeft;

u16 getSegmentNum() {
  if (timeLeft > FINAL_COUNTDOWN_TIME) {
    float pieTime = totalTime - FINAL_COUNTDOWN_TIME;
    float elapsed = totalTime - timeLeft;
    int segment = (int)(elapsed / (pieTime / NUMBER_PIE_TILES));
    if (segment >= NUMBER_PIE_TILES) {
      segment = NUMBER_PIE_TILES - 1;
      return segment;
    }
    return segment;
  }
  return timeLeft;
}

void setTimerTotalTime(u16 tTime) { totalTime = tTime; }

void setTimerTimeLeft(u16 tLeft) { timeLeft = tLeft; }

void activateTimer() { timerActive = true; }

void deactivateTimer() { timerActive = false; }

u16 getTimerTotalTime() { return totalTime; }

u16 getTimerTimeLeft() { return timeLeft; }
