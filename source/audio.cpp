#include "SRU/audio.hpp"
#include "SRU/assets.hpp"
#include "SRU/error.hpp"
#include "SRU/random.hpp"

void playSound(const std::string &name, float volume) {
   playSound(name, randomFloat(SRULIB_MIN_PITCH, SRULIB_MAX_PITCH), volume);
}

void playSound(const std::string &name, float pitch, float volume) {
   if (!soundExists(name)) {
      SRULibWarning(TextFormat("srulib::playSound: Sound '%s' does not exist.\n", name.c_str()));
      return;
   }

   std::vector<Sound> &soundPool = getSoundPool(name);
   if (soundPool.empty()) {
      SRULibWarning(TextFormat("srulib::playSound: Sound pool '%s' is empty. Most likely, it failed to load.\n", name.c_str()));
      return;
   }

   Sound sound = randomElement(soundPool);
   SetSoundPitch(sound, pitch);
   SetSoundVolume(sound, volume);
   PlaySound(sound);
}

void playRawSound(Sound sound, float volume) {
   playRawSound(sound, randomFloat(SRULIB_MIN_PITCH, SRULIB_MAX_PITCH), volume);
}

void playRawSound(Sound sound, float pitch, float volume) {
   SetSoundPitch(sound, pitch);
   SetSoundVolume(sound, volume);
   PlaySound(sound);
}
