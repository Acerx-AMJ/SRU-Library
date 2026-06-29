#pragma once
#include <cmath>
#include <raylib.h>
#include <raymath.h>

#ifndef SRULIB_BASE_WIDTH
#define SRULIB_BASE_WIDTH 1920.0f
#endif // #ifndef SRULIB_BASE_WIDTH

#ifndef SRULIB_BASE_HEIGHT
#define SRULIB_BASE_HEIGHT 1080.0f
#endif // #ifndef SRULIB_BASE_HEIGHT

// Window size/ratio utility
inline float getWidthRatio() {
   return GetScreenWidth() / SRULIB_BASE_WIDTH;
}

inline float getHeightRatio() {
   return GetScreenHeight() / SRULIB_BASE_HEIGHT;
}

inline float getMinimumRatio() {
   return fminf(getWidthRatio(), getHeightRatio());
}

inline float getMaximumRatio() {
   return fmaxf(getWidthRatio(), getHeightRatio());
}

inline float getAspectRatio() {
   return (float)GetScreenWidth() / GetScreenHeight();
}

inline float getFontSizeScaled(float fontSize) {
   return fontSize * getMinimumRatio();
}

inline float getWindowWidth() {
   return GetScreenWidth();
}

inline float getWindowHeight() {
   return GetScreenHeight();
}

inline Vector2 getWindowSize() {
   return {(float)GetScreenWidth(), (float)GetScreenHeight()};
}

inline Vector2 getWindowCenter() {
   return getWindowSize() / 2.0f;
}

inline Vector2 getWindowCenterOffset(Vector2 offset) {
   return getWindowSize() / 2.0f + offset;
}

inline Vector2 translateRatioToScreen(Vector2 ratio) {
   return ratio * getWindowSize();
}

inline Vector2 translateScreenToRatio(Vector2 screen) {
   return screen / getWindowSize();
}

// Origin/source utility
inline Vector2 getTextSize(Font font, const char *text, float fontSize, float spacing) {
   return MeasureTextEx(font, text, fontSize, spacing);
}

inline Vector2 getTextOrigin(Font font, const char *text, float fontSize, float spacing) {
   return MeasureTextEx(font, text, fontSize, spacing) / 2.0f;
}

constexpr inline Vector2 getOrigin(Vector2 size) {
   return {size.x / 2.0f, size.y / 2.0f};
}

constexpr inline Rectangle getSource(Texture texture) {
   return {0.0f, 0.0f, (float)texture.width, (float)texture.height};
}
