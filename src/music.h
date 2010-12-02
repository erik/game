#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "SDL/SDL_mixer.h"

class Music {
  const static int audioRate = 22050;
  const static Uint16 audioFormat = AUDIO_S16;
  const static int audioChannels = 2;
  const static int audioBuffers = 4096;
 private:
  Mix_Music *music;
 public:
  static void init();
  Music() {};
  Music(std::string);
  ~Music();
  void load(std::string);
  void play();
  void stop();
  void loop();

};

#endif
