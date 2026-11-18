#pragma once
#include <raylib.h>
#include <string>

// sound pitch/volume getters/setters
void setSoundPitch(float pitch);
void setSoundPitch(float min, float max);
void setSoundPitchMin(float pitch);
void setSoundPitchMax(float pitch);
void setSoundVolume(float volume);

float getSoundPitchMin();
float getSoundPitchMax();
float getSoundVolume();

// play sound functions
void playSound(const std::string &name);
void playSound(const std::string &name, float pitch, float volume);

void playRawSound(Sound sound);
void playRawSound(Sound sound, float pitch, float volume);
