#pragma once
#include <raylib.h>
#include <raymath.h>

// Screen utilities

float getWindowWidth();
float getWindowHeight();

Vector2 getWindowSize();
Vector2 getMinimumWindowSize();
Vector2 getWindowCenter();
Vector2 getWindowCenterOffset(Vector2 offset);

Vector2 mapRatioToScreen(Vector2 ratio);
Vector2 mapRatioToScreen(float ratioX, float ratioY);
Vector2 mapScreenToRatio(Vector2 screen);
Vector2 mapScreenToRatio(float screenX, float screenY);
Vector2 mapRatioToRectangle(Rectangle rect, Vector2 ratio);
Vector2 mapRatioToRectangle(Rectangle rect, float ratioX, float ratioY);
Vector2 mapRectangleToRatio(Rectangle rect, Vector2 position);
Vector2 mapRectangleToRatio(Rectangle rect, float positionX, float positionY);

Vector2 mapCubicRatioToScreen(Vector2 ratio);
Vector2 mapCubicRatioToScreen(float ratioX, float ratioY);
Vector2 mapScreenToCubicRatio(Vector2 screen);
Vector2 mapScreenToCubicRatio(float screenX, float screenY);
Vector2 mapCubicRatioToRectangle(Rectangle rect, Vector2 ratio);
Vector2 mapCubicRatioToRectangle(Rectangle rect, float ratioX, float ratioY);
Vector2 mapRectangleToCubicRatio(Rectangle rect, Vector2 position);
Vector2 mapRectangleToCubicRatio(Rectangle rect, float positionX, float positionY);

// Origin/source utility
Vector2 getTextSize(Font font, const char *text, float fontSize, float spacing);
Vector2 getTextOrigin(Font font, const char *text, float fontSize, float spacing);

constexpr inline Vector2 getOrigin(Vector2 size) {
   return {size.x / 2.0f, size.y / 2.0f};
}

constexpr inline Rectangle getSource(Texture texture) {
   return {0.0f, 0.0f, (float)texture.width, (float)texture.height};
}

// Render utility

void drawText(Font font, Vector2 position, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextCentered(Font font, Vector2 position, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextOrigin(Font font, Vector2 position, Vector2 origin, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextCenteredResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextOriginResponsive(Font font, Vector2 ratio, Vector2 origin, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);

void drawRect(Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawRectCentered(Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawRectOrigin(Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawRectResponsive(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectCenteredResponsive(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectOriginResponsive(Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectResponsiveCubic(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectCenteredResponsiveCubic(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectOriginResponsiveCubic(Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);

void drawTexture(Texture texture, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureCentered(Texture texture, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureOrigin(Texture texture, Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureCenteredResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureOriginResponsive(Texture texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureResponsiveCubic(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureCenteredResponsiveCubic(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureOriginResponsiveCubic(Texture texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSource(Texture texture, Rectangle source, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceCentered(Texture texture, Rectangle source, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceOrigin(Texture texture, Rectangle source, Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceResponsive(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceCenteredResponsive(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceOriginResponsive(Texture texture, Rectangle source, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceResponsiveCubic(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceCenteredResponsiveCubic(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceOriginResponsiveCubic(Texture texture, Rectangle source, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
