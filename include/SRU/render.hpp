#pragma once
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

// Screen utilities
float getWindowWidth();
float getWindowHeight();

Vector2 getWindowSize();
Vector2 getMinimumWindowSize();
Vector2 getWindowCenter();
Vector2 getWindowCenterOffset(Vector2 offset);

Rectangle mapArea(Vector2 ratio, Vector2 sizeRatio);
Rectangle mapAreaPoints(Vector2 startRatio, Vector2 endRatio);
Rectangle mapAreaCentered(Vector2 centerRatio, Vector2 sizeRatio);
Rectangle mapCubicArea(Vector2 ratio, Vector2 sizeRatio);
Rectangle mapCubicAreaPoints(Vector2 startRatio, Vector2 endRatio);
Rectangle mapCubicAreaCentered(Vector2 centerRatio, Vector2 sizeRatio);

Vector2 mapRatioToScreen(Vector2 ratio);
Vector2 mapRatioToScreen(float ratioX, float ratioY);
Vector2 mapScreenToRatio(Vector2 screen);
Vector2 mapScreenToRatio(float screenX, float screenY);
Vector2 mapRatioToArea(Rectangle area, Vector2 ratio);
Vector2 mapRatioToArea(Rectangle area, float ratioX, float ratioY);
Vector2 mapAreaToRatio(Rectangle area, Vector2 position);
Vector2 mapAreaToRatio(Rectangle area, float positionX, float positionY);

Vector2 mapCubicRatioToScreen(Vector2 ratio);
Vector2 mapCubicRatioToScreen(float ratioX, float ratioY);
Vector2 mapScreenToCubicRatio(Vector2 screen);
Vector2 mapScreenToCubicRatio(float screenX, float screenY);
Vector2 mapCubicRatioToArea(Rectangle area, Vector2 ratio);
Vector2 mapCubicRatioToArea(Rectangle area, float ratioX, float ratioY);
Vector2 mapAreaToCubicRatio(Rectangle area, Vector2 position);
Vector2 mapAreaToCubicRatio(Rectangle area, float positionX, float positionY);

Vector2 mapSizeRatioToArea(Rectangle area, Vector2 ratio);
Vector2 mapSizeRatioToArea(Rectangle area, float ratioX, float ratioY);
Vector2 mapCubicSizeRatioToArea(Rectangle area, Vector2 ratio);
Vector2 mapCubicSizeRatioToArea(Rectangle area, float ratioX, float ratioY);

float mapRatioToX(float ratioX);
float mapRatioToY(float ratioY);
float mapRatioToCubicSize(float ratio);
float mapRatioToAreaX(Rectangle area, float ratioX);
float mapRatioToAreaY(Rectangle area, float ratioY);
float mapRatioToAreaWidth(Rectangle area, float ratioX);
float mapRatioToAreaHeight(Rectangle area, float ratioY);
float mapRatioToAreaCubicSize(Rectangle area, float ratio);

float mapXToRatio(float width);
float mapYToRatio(float height);
float mapCubicSizeToRatio(float cubicSize);
float mapAreaXToRatio(Rectangle area, float x);
float mapAreaYToRatio(Rectangle area, float y);
float mapAreaWidthToRatio(Rectangle area, float width);
float mapAreaHeightToRatio(Rectangle area, float height);
float mapAreaCubicSizeToRatio(Rectangle area, float cubicSize);

// Grid utility
Vector2 gridPosition(Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = {0.5f, 0.5f});
Vector2 gridRatio(Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = {0.5f, 0.5f});
Rectangle gridRectangle(Vector2 size, Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = {0.5f, 0.5f});
Rectangle gridRatioRectangle(Vector2 sizeRatio, Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = {0.5f, 0.5f});

Vector2 getGridCellSize(Rectangle grid, int columns, int rows);
Vector2 getGridCellRatio(Rectangle grid, int columns, int rows);
Vector2 getGridCellCubicRatio(Rectangle grid, int columns, int rows);

Vector2 gridInvalidCell();
Vector2 getGridCell(Rectangle grid, int columns, int rows, Vector2 position);
Vector2 snapToGrid(Rectangle grid, int columns, int rows, Vector2 position, Vector2 origin = {0.5f, 0.5f});

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
void drawTextResponsive(Font font, Rectangle area, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextCenteredResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextCenteredResponsive(Font font, Rectangle area, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextOriginResponsive(Font font, Vector2 ratio, Vector2 origin, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextOriginResponsive(Font font, Rectangle area, Vector2 ratio, Vector2 origin, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);

void drawText(const std::string &font, Vector2 position, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextCentered(const std::string &font, Vector2 position, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextOrigin(const std::string &font, Vector2 position, Vector2 origin, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextResponsive(const std::string &font, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextResponsive(const std::string &font, Rectangle area, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextCenteredResponsive(const std::string &font, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextCenteredResponsive(const std::string &font, Rectangle area, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextOriginResponsive(const std::string &font, Vector2 ratio, Vector2 origin, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextOriginResponsive(const std::string &font, Rectangle area, Vector2 ratio, Vector2 origin, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);

void drawRect(Rectangle rect, Color color = WHITE, float rotation = 0.0f);
void drawRect(Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawRectCentered(Rectangle rect, Color color = WHITE, float rotation = 0.0f);
void drawRectCentered(Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawRectOrigin(Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawRectOrigin(Rectangle rect, Vector2 origin, Color color = WHITE, float rotation = 0.0f);
void drawRectResponsive(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectResponsive(Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectCenteredResponsive(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectCenteredResponsive(Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectOriginResponsive(Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectOriginResponsive(Rectangle area, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectResponsiveCubic(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectResponsiveCubic(Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectCenteredResponsiveCubic(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectCenteredResponsiveCubic(Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectOriginResponsiveCubic(Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectOriginResponsiveCubic(Rectangle area, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);

void drawTexture(Texture texture, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureCentered(Texture texture, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureOrigin(Texture texture, Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureResponsive(Texture texture, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureCenteredResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureCenteredResponsive(Texture texture, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureOriginResponsive(Texture texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureOriginResponsive(Texture texture, Rectangle area, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureResponsiveCubic(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureResponsiveCubic(Texture texture, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureCenteredResponsiveCubic(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureCenteredResponsiveCubic(Texture texture, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureOriginResponsiveCubic(Texture texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureOriginResponsiveCubic(Texture texture, Rectangle area, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});

void drawTexture(const std::string &texture, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureCentered(const std::string &texture, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureOrigin(const std::string &texture, Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureResponsive(const std::string &texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureResponsive(const std::string &texture, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureCenteredResponsive(const std::string &texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureCenteredResponsive(const std::string &texture, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureOriginResponsive(const std::string &texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureOriginResponsive(const std::string &texture, Rectangle area, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureResponsiveCubic(const std::string &texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureResponsiveCubic(const std::string &texture, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureCenteredResponsiveCubic(const std::string &texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureCenteredResponsiveCubic(const std::string &texture, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureOriginResponsiveCubic(const std::string &texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});
void drawTextureOriginResponsiveCubic(const std::string &texture, Rectangle area, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f, Rectangle source = {0, 0, 0, 0});

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

void drawTextureAnimated(Animation animation, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedCentered(Animation animation, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedOrigin(Animation animation, Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedResponsive(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedResponsive(Animation animation, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedCenteredResponsive(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedCenteredResponsive(Animation animation, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedOriginResponsive(Animation animation, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedOriginResponsive(Animation animation, Rectangle area, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedResponsiveCubic(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedResponsiveCubic(Animation animation, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedCenteredResponsiveCubic(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedCenteredResponsiveCubic(Animation animation, Rectangle area, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedOriginResponsiveCubic(Animation animation, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedOriginResponsiveCubic(Animation animation, Rectangle area, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
