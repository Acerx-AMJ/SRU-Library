#include "SRU/audio.hpp"
#include "SRU/assets.hpp"
#include "SRU/error.hpp"
#include "SRU/random.hpp"

static float pitchMin = 0.925f;
static float pitchMax = 1.075f;
static float soundVolume = 1.0f;

// sound pitch/volume getters/setters
void setSoundPitch(float pitch) {
   pitchMin = pitchMax = pitch;
}

void setSoundPitch(float min, float max) {
   pitchMin = min;
   pitchMax = max;
}

void setSoundPitchMin(float pitch) {
   pitchMin = pitch;
}

void setSoundPitchMax(float pitch) {
   pitchMax = pitch;
}

void setSoundVolume(float volume) {
   soundVolume = volume;
}

float getSoundPitchMin() {
   return pitchMin;
}

float getSoundPitchMax() {
   return pitchMax;
}

float getSoundVolume() {
   return soundVolume;
}

// play sound functions
void playSound(const std::string &name) {
   playSound(name, randomFloat(pitchMin, pitchMax), soundVolume);
}

void playSound(const std::string &name, float pitch, float volume) {
   if (!soundExists(name)) {
      SRULibWarning("srulib::playSound: Sound '%s' does not exist.\n", name.c_str());
      return;
   }

   std::vector<Sound> &soundPool = getSoundPool(name);
   if (soundPool.empty()) {
      SRULibWarning("srulib::playSound: Sound pool '%s' is empty. Most likely, it failed to load.\n", name.c_str());
      return;
   }

   Sound sound = randomElement(soundPool);
   SetSoundPitch(sound, pitch);
   SetSoundVolume(sound, volume);
   PlaySound(sound);
}

void playRawSound(Sound sound) {
   playRawSound(sound, randomFloat(pitchMin, pitchMax), soundVolume);
}

void playRawSound(Sound sound, float pitch, float volume) {
   SetSoundPitch(sound, pitch);
   SetSoundVolume(sound, volume);
   PlaySound(sound);
}
