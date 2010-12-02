#include "game.h"
#include "music.h"


void Music::init() {
  int result = Mix_OpenAudio(audioRate, audioFormat, audioChannels, 
			     audioBuffers);
  if(result) {
    FATAL("Intializing music failed!");
  }
}

Music::Music(std::string filename) {
  music = Mix_LoadMUS(filename.c_str());
}

Music::~Music() {
  Mix_FreeMusic(music);
}

void Music::load(std::string filename) {
  music = Mix_LoadMUS(filename.c_str());
}

void Music::play() {
  Mix_PlayMusic(music, 0);
}

void Music::stop() {
  Mix_HaltMusic();
}

void Music::loop() {
  Mix_PlayMusic(music, -1);
}


