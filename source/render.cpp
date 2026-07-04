#include "SRU/render.hpp"
#include "SRU/text.hpp"
#include "SRU/util.hpp"

// Screen utilities
float getWindowWidth() {
   return GetScreenWidth();
}

float getWindowHeight() {
   return GetScreenHeight();
}

Vector2 getWindowSize() {
   return V2(GetScreenWidth(), GetScreenHeight());
}

Vector2 getMinimumWindowSize() {
   return V2(fminf(GetScreenWidth(), GetScreenHeight()));
}

Vector2 getWindowCenter() {
   return getWindowSize() / 2.0f;
}

Vector2 getWindowCenterOffset(Vector2 offset) {
   return getWindowSize() / 2.0f + offset;
}

Vector2 mapRatioToScreen(Vector2 ratio) {
   return Vector2ClampValue(ratio, 0.0f, 1.0f) * getWindowSize();
}

Vector2 mapRatioToScreen(float ratioX, float ratioY) {
   return Vector2ClampValue({ratioX, ratioY}, 0.0f, 1.0f) * getWindowSize();
}

Vector2 mapScreenToRatio(Vector2 screen) {
   return Vector2ClampValue(screen / getWindowSize(), 0.0f, 1.0f);
}

Vector2 mapScreenToRatio(float screenX, float screenY) {
   return Vector2ClampValue(V2(screenX, screenY) / getWindowSize(), 0.0f, 1.0f);
}

Vector2 mapRatioToRectangle(Rectangle rect, Vector2 ratio) {
   return Vector2ClampValue(ratio, 0.0f, 1.0f) * V2(rect.width, rect.height) + V2(rect.x, rect.y);
}

Vector2 mapRatioToRectangle(Rectangle rect, float ratioX, float ratioY) {
   return Vector2ClampValue({ratioX, ratioY}, 0.0f, 1.0f) * V2(rect.width, rect.height) + V2(rect.x, rect.y);
}

Vector2 mapRectangleToRatio(Rectangle rect, Vector2 position) {
   return Vector2ClampValue(V2(position.x - rect.x, position.y - rect.y) / V2(rect.width, rect.height), 0.0f, 1.0f);
}

Vector2 mapRectangleToRatio(Rectangle rect, float positionX, float positionY) {
   return Vector2ClampValue(V2(positionX - rect.x, positionY - rect.y) / V2(rect.width, rect.height), 0.0f, 1.0f);
}

Vector2 mapCubicRatioToScreen(Vector2 ratio) {
   return Vector2ClampValue(ratio, 0.0f, 1.0f) * getMinimumWindowSize();
}

Vector2 mapCubicRatioToScreen(float ratioX, float ratioY) {
   return Vector2ClampValue({ratioX, ratioY}, 0.0f, 1.0f) * getMinimumWindowSize();
}

Vector2 mapScreenToCubicRatio(Vector2 screen) {
   return Vector2ClampValue(screen / getMinimumWindowSize(), 0.0f, 1.0f);
}

Vector2 mapScreenToCubicRatio(float screenX, float screenY) {
   return Vector2ClampValue(V2(screenX, screenY) / getMinimumWindowSize(), 0.0f, 1.0f);
}

Vector2 mapCubicRatioToRectangle(Rectangle rect, Vector2 ratio) {
   return Vector2ClampValue(ratio, 0.0f, 1.0f) * V2(fminf(rect.width, rect.height)) + V2(rect.x, rect.y);
}

Vector2 mapCubicRatioToRectangle(Rectangle rect, float ratioX, float ratioY) {
   return Vector2ClampValue({ratioX, ratioY}, 0.0f, 1.0f) * V2(fminf(rect.width, rect.height)) + V2(rect.x, rect.y);
}

Vector2 mapRectangleToCubicRatio(Rectangle rect, Vector2 position) {
   return Vector2ClampValue(V2(position.x - rect.x, position.y - rect.y) / V2(fminf(rect.width, rect.height)), 0.0f, 1.0f);
}

Vector2 mapRectangleToCubicRatio(Rectangle rect, float positionX, float positionY) {
   return Vector2ClampValue(V2(positionX - rect.x, positionY - rect.y) / V2(fminf(rect.width, rect.height)), 0.0f, 1.0f);
}

// Origin/source utility
Vector2 getTextSize(Font font, const char *text, float fontSize, float spacing) {
   return MeasureTextEx(font, text, fontSize, spacing);
}

Vector2 getTextOrigin(Font font, const char *text, float fontSize, float spacing) {
   return MeasureTextEx(font, text, fontSize, spacing) / 2.0f;
}

// Render utility
void drawText(Font font, Vector2 position, const char *text, float fontSize, Color color, float rotation) {
   DrawTextPro(font, text, position, V2(), rotation, fontSize, fitSpacing(fontSize), color);
}

void drawTextCentered(Font font, Vector2 position, const char *text, float fontSize, Color color, float rotation) {
   DrawTextPro(font, text, position, getTextOrigin(font, text, fontSize, fitSpacing(fontSize)), rotation, fontSize, fitSpacing(fontSize), color);
}

void drawTextOrigin(Font font, Vector2 position, Vector2 origin, const char *text, float fontSize, Color color, float rotation) {
   DrawTextPro(font, text, position, origin, rotation, fontSize, fitSpacing(fontSize), color);
}

void drawTextResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Color color, float rotation) {
   float fontSizeScaled = getFontSizeScaled(fontSize);
   DrawTextPro(font, text, mapRatioToScreen(ratio), V2(), rotation, fontSizeScaled, fitSpacing(fontSizeScaled), color);
}

void drawTextCenteredResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Color color, float rotation) {
   float fontSizeScaled = getFontSizeScaled(fontSize);
   float spacingScaled = fitSpacing(fontSizeScaled);
   DrawTextPro(font, text, mapRatioToScreen(ratio), getTextOrigin(font, text, fontSizeScaled, spacingScaled), rotation, fontSizeScaled, spacingScaled, color);
}

void drawTextOriginResponsive(Font font, Vector2 ratio, Vector2 origin, const char *text, float fontSize, Color color, float rotation) {
   float fontSizeScaled = getFontSizeScaled(fontSize);
   float spacingScaled = fitSpacing(fontSizeScaled);
   DrawTextPro(font, text, mapRatioToScreen(ratio), origin, rotation, fontSizeScaled, spacingScaled, color);
}

void drawRect(Vector2 position, Vector2 size, Color color, float rotation) {
   DrawRectanglePro(R4(position, size), V2(), rotation, color);
}

void drawRectCentered(Vector2 position, Vector2 size, Color color, float rotation) {
   DrawRectanglePro(R4(position, size), getOrigin(size), rotation, color);
}

void drawRectOrigin(Vector2 position, Vector2 origin, Vector2 size, Color color, float rotation) {
   DrawRectanglePro(R4(position, size), origin, rotation, color);
}

void drawRectResponsive(Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   DrawRectanglePro(R4(mapRatioToScreen(ratio), mapRatioToScreen(sizeRatio)), V2(), rotation, color);
}

void drawRectCenteredResponsive(Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   Vector2 size = mapRatioToScreen(sizeRatio);
   DrawRectanglePro(R4(mapRatioToScreen(ratio), size), getOrigin(size), rotation, color);
}

void drawRectOriginResponsive(Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color, float rotation) {
   DrawRectanglePro(R4(mapRatioToScreen(ratio), mapRatioToScreen(sizeRatio)), origin, rotation, color);
}

void drawRectResponsiveCubic(Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   DrawRectanglePro(R4(mapCubicRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), V2(), rotation, color);
}

void drawRectCenteredResponsiveCubic(Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   Vector2 size = mapCubicRatioToScreen(sizeRatio);
   DrawRectanglePro(R4(mapCubicRatioToScreen(ratio), size), getOrigin(size), rotation, color);
}

void drawRectOriginResponsiveCubic(Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color, float rotation) {
   DrawRectanglePro(R4(mapCubicRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), origin, rotation, color);
}

void drawTexture(Texture texture, Vector2 position, Vector2 size, Color color, float rotation) {
   DrawTexturePro(texture, getSource(texture), R4(position, size), V2(), rotation, color);
}

void drawTextureCentered(Texture texture, Vector2 position, Vector2 size, Color color, float rotation) {
   DrawTexturePro(texture, getSource(texture), R4(position, size), getOrigin(size), rotation, color);
}

void drawTextureOrigin(Texture texture, Vector2 position, Vector2 origin, Vector2 size, Color color, float rotation) {
   DrawTexturePro(texture, getSource(texture), R4(position, size), origin, rotation, color);
}

void drawTextureResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   DrawTexturePro(texture, getSource(texture), R4(mapRatioToScreen(ratio), mapRatioToScreen(sizeRatio)), V2(), rotation, color);
}

void drawTextureCenteredResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   Vector2 size = mapRatioToScreen(sizeRatio);
   DrawTexturePro(texture, getSource(texture), R4(mapRatioToScreen(ratio), size), getOrigin(size), rotation, color);
}

void drawTextureOriginResponsive(Texture texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color, float rotation) {
   DrawTexturePro(texture, getSource(texture), R4(mapRatioToScreen(ratio), mapRatioToScreen(sizeRatio)), origin, rotation, color);
}

void drawTextureResponsiveCubic(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   DrawTexturePro(texture, getSource(texture), R4(mapCubicRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), V2(), rotation, color);
}

void drawTextureCenteredResponsiveCubic(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   Vector2 size = mapCubicRatioToScreen(sizeRatio);
   DrawTexturePro(texture, getSource(texture), R4(mapCubicRatioToScreen(ratio), size), getOrigin(size), rotation, color);
}

void drawTextureOriginResponsiveCubic(Texture texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color, float rotation) {
   DrawTexturePro(texture, getSource(texture), R4(mapCubicRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), origin, rotation, color);
}

void drawTextureSource(Texture texture, Rectangle source, Vector2 position, Vector2 size, Color color, float rotation) {
   DrawTexturePro(texture, source, R4(position, size), V2(), rotation, color);
}

void drawTextureSourceCentered(Texture texture, Rectangle source, Vector2 position, Vector2 size, Color color, float rotation) {
   DrawTexturePro(texture, source, R4(position, size), getOrigin(size), rotation, color);
}

void drawTextureSourceOrigin(Texture texture, Rectangle source, Vector2 position, Vector2 origin, Vector2 size, Color color, float rotation) {
   DrawTexturePro(texture, source, R4(position, size), origin, rotation, color);
}

void drawTextureSourceResponsive(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   DrawTexturePro(texture, source, R4(mapRatioToScreen(ratio), mapRatioToScreen(sizeRatio)), V2(), rotation, color);
}

void drawTextureSourceCenteredResponsive(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   Vector2 size = mapRatioToScreen(sizeRatio);
   DrawTexturePro(texture, source, R4(mapRatioToScreen(ratio), size), getOrigin(size), rotation, color);
}

void drawTextureSourceOriginResponsive(Texture texture, Rectangle source, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color, float rotation) {
   DrawTexturePro(texture, source, R4(mapRatioToScreen(ratio), mapRatioToScreen(sizeRatio)), origin, rotation, color);
}

void drawTextureSourceResponsiveCubic(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   DrawTexturePro(texture, source, R4(mapCubicRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), V2(), rotation, color);
}

void drawTextureSourceCenteredResponsiveCubic(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   Vector2 size = mapCubicRatioToScreen(sizeRatio);
   DrawTexturePro(texture, source, R4(mapCubicRatioToScreen(ratio), size), getOrigin(size), rotation, color);
}

void drawTextureSourceOriginResponsiveCubic(Texture texture, Rectangle source, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color, float rotation) {
   DrawTexturePro(texture, source, R4(mapCubicRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), origin, rotation, color);
}
