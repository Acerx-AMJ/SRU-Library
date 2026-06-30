#include "SRU/audio.hpp"
#include "SRU/assets.hpp"
#include "SRU/random.hpp"

void playSound(const std::string &name, float volume) {
   if (!soundExists(name)) {
      printf("srulib::playSound: Sound '%s' does not exist.\n", name.c_str());
      exit(EXIT_FAILURE);
   }

   Sound sound = randomElement(getSoundPool(name));
   SetSoundPitch(sound, randomFloat(SRULIB_MIN_PITCH, SRULIB_MAX_PITCH));
   SetSoundVolume(sound, volume);
   PlaySound(sound);
}

void playSoundPure(const std::string &name, float pitch, float volume) {
   if (!soundExists(name)) {
      printf("srulib::playSoundPure: Sound '%s' does not exist.\n", name.c_str());
      exit(EXIT_FAILURE);
   }

   Sound sound = randomElement(getSoundPool(name));
   SetSoundPitch(sound, pitch);
   SetSoundVolume(sound, volume);
   PlaySound(sound);
}

void playRawSound(Sound sound, float volume) {
   SetSoundPitch(sound, randomFloat(SRULIB_MIN_PITCH, SRULIB_MAX_PITCH));
   SetSoundVolume(sound, volume);
   PlaySound(sound);
}

void playRawSoundPure(Sound sound, float pitch, float volume) {
   SetSoundPitch(sound, pitch);
   SetSoundVolume(sound, volume);
   PlaySound(sound);
}
