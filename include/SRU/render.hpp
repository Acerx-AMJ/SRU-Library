#pragma once
#include "SRU/constants.hpp"
#include <raymath.h>
#include <string>
#include <vector>

// Screen utilities
float getWindowWidth();
float getWindowHeight();

Vector2 getWindowSize();
Vector2 getCubicWindowSize();
Vector2 getWindowCenter();
Rectangle getWindowArea();

// Responsiveness utilities
Rectangle mapRatioToArea(Rectangle ratio, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Rectangle mapRatioToArea(Vector2 startRatio, Vector2 endRatio, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapRatioToArea(Vector2 ratio, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapRatioToArea(float ratioX, float ratioY, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapSizeRatioToArea(Vector2 sizeRatio, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapSizeRatioToArea(float sizeRatioX, float sizeRatioY, Rectangle area = WINDOW_AREA, int type = RATIO);

Rectangle mapAreaToRatio(Rectangle rect, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Rectangle mapAreaToRatio(Vector2 start, Vector2 end, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToRatio(Vector2 position, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToRatio(float x, float y, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToSizeRatio(Vector2 size, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToSizeRatio(float width, float height, Rectangle area = WINDOW_AREA, int type = RATIO);

float mapRatioToX(float ratioX, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapRatioToY(float ratioY, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapRatioToWidth(float ratioX, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapRatioToHeight(float ratioY, Rectangle area = WINDOW_AREA, int type = RATIO);

float mapXToRatio(float x, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapYToRatio(float y, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapWidthToRatio(float width, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapHeightToRatio(float height, Rectangle area = WINDOW_AREA, int type = RATIO);

// Grid/origin utility
Vector2 gridPosition(Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
Vector2 gridRatio(Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
Rectangle gridRectangle(Vector2 size, Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
Rectangle gridRatioRectangle(Vector2 sizeRatio, Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);

Vector2 getGridCellSize(Rectangle grid, int columns, int rows);
Vector2 getGridCellRatio(Rectangle grid, int columns, int rows, int type = RATIO);

Vector2 getGridCell(Rectangle grid, int columns, int rows, Vector2 position);
Vector2 snapToGrid(Rectangle grid, int columns, int rows, Vector2 position, Vector2 origin = CENTER);

Vector2 getTextSize(Font font, const char *text, float fontSize, float spacing);
Vector2 getTextOrigin(Font font, const char *text, float fontSize, float spacing, Vector2 origin = CENTER);

constexpr inline Vector2 getOrigin(Vector2 size, Vector2 origin = CENTER) {
   return {size.x * origin.x, size.y * origin.y};
}

constexpr inline Rectangle getSource(Texture texture) {
   return {0.0f, 0.0f, (float)texture.width, (float)texture.height};
}

// Render utility
void drawText(Font font, Vector2 position, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawTextResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, float rotation = 0.0f);
void drawText(const std::string &font, Vector2 position, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawTextResponsive(const std::string &font, Vector2 ratio, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, float rotation = 0.0f);

void drawRect(Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawRect(Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawRectResponsive(Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawRectResponsive(Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);

void drawTexture(Texture texture, Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
void drawTexture(Texture texture, Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
void drawTextureResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawTextureResponsive(Texture texture, Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawTexture(const std::string &texture, Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
void drawTexture(const std::string &texture, Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
void drawTextureResponsive(const std::string &texture, Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawTextureResponsive(const std::string &texture, Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);

// Animation render utility
using AnimationID = size_t;

struct AnimationConfig {
   AnimationConfig() = default;
   AnimationConfig(Texture texture, size_t frameWidth, size_t frameHeight, size_t gap, size_t frameY, size_t frameCount, float frameTime, bool loop = true);
   AnimationConfig(Texture texture, size_t frameSize, size_t gap, size_t frameY, size_t frameCount, float frameTime, bool loop = true);
   AnimationConfig(Texture texture, size_t frameSize, size_t frameCount, float frameTime, bool loop = true);

   Texture texture;
   size_t frameWidth = 0;
   size_t frameHeight = 0;
   size_t gapX = 0;
   size_t gapY = 0;
   size_t frameY = 0;
   size_t frameCount = 0;
   float frameTime = 0.0f;
   bool loop = true;
};

struct Animation {
   Animation() = default;
   Animation(size_t ID, bool paused, bool flipX, bool flipY, bool randomStart = false);
   Animation(size_t ID, bool randomStart = false);

   size_t ID = 0;
   size_t frame = 0;
   float timer = 0.0f;
   bool paused = false;
   bool flipX = false;
   bool flipY = false;
   bool finished = false;
};

AnimationID pushAnimation(AnimationConfig config);
AnimationConfig &getAnimation(AnimationID ID);
std::vector<AnimationConfig> &getAnimationContainer();
Rectangle getAnimationSource(Animation animation);
Rectangle getAnimationSource(Animation animation, AnimationConfig config);

bool isAnimationPlaying(Animation &animation, AnimationID ID);
void setAnimationState(Animation &animation, AnimationID ID);
void forceAnimationState(Animation &animation, AnimationID ID);
void animate(Animation &animation, float DT);

void drawTextureAnimated(Animation animation, Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimated(Animation animation, Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedResponsive(Animation animation, Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawTextureAnimatedResponsive(Animation animation, Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
