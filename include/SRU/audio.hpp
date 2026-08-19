#pragma once
#include <raylib.h>
#include <string>

#ifndef SRULIB_MIN_PITCH
   #define SRULIB_MIN_PITCH 0.925f
#endif // SRULIB_MIN_PITCH

#ifndef SRULIB_MAX_PITCH
   #define SRULIB_MAX_PITCH 1.075f
#endif // SRULIB_MAX_PITCH

void playSound(const std::string &name, float volume = 1.0f);
void playSound(const std::string &name, float pitch, float volume);

void playRawSound(Sound sound, float volume = 1.0f);
void playRawSound(Sound sound, float pitch, float volume);
