#ifndef _TIMER_H_
#define _TIMER_H_

class Timer {
private:
  int startTicks;
  int pausedTicks;
public:
  bool paused, started;

  Timer();
  void start();
  void pause();
  void unpause();
  int getTicks();
};

#endif /* _TIMER_H_ */
