#pragma once
#include <raylib.h>
#include <raymath.h>

inline float getFontSizeScaled(float fontSize) {
   return fontSize * fminf(GetScreenWidth(), GetScreenHeight()) / 1000.0f;
}

inline float getSpacingScaled(float spacing = 1.0f) {
   return spacing * fminf(GetScreenWidth(), GetScreenHeight()) / 1000.0f;
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

inline Vector2 translateRatioToScreen(float ratioX, float ratioY) {
   return {ratioX * GetScreenWidth(), ratioY * GetScreenHeight()};
}

inline Vector2 translateScreenToRatio(Vector2 screen) {
   return screen / getWindowSize();
}

inline Vector2 translateScreenToRatio(float screenX, float screenY) {
   return {screenX / GetScreenWidth(), screenY / GetScreenHeight()};
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
