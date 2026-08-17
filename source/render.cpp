#include "SRU/render.hpp"
#include "SRU/assets.hpp"
#include "SRU/random.hpp"
#include "SRU/text.hpp"
#include "SRU/util.hpp"

// helper functions
Rectangle getSource(Rectangle source, Texture texture) {
   return source == FULL_SOURCE ? getSource(texture) : source;
}

Rectangle getArea(Rectangle area) {
   return area == WINDOW_AREA ? getWindowArea() : area;
}

Vector2 getSizeFromRatioType(float width, float height, int type) {
   if (type == CUBIC_RATIO) {
      return V2(fminf(width, height));
   }
   else if (type == FILL_RATIO) {
      return V2(fmaxf(width, height));
   }
   return V2(width, height);
}

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

Vector2 getCubicWindowSize() {
   return V2(fminf(GetScreenWidth(), GetScreenHeight()));
}

Vector2 getWindowCenter() {
   return getWindowSize() / 2.0f;
}

Rectangle getWindowArea() {
   return R4(0, 0, GetScreenWidth(), GetScreenHeight());
}

// Responsiveness utilities
Rectangle mapRatioToArea(Rectangle ratio, Vector2 origin, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   Vector2 position = mapRatioToArea(R4pos(ratio), realArea, RATIO);
   Vector2 size = mapSizeRatioToArea(R4size(ratio), realArea, type);
   return R4(position - size * origin, size);
}

Rectangle mapRatioToArea(Vector2 startRatio, Vector2 endRatio, Vector2 origin, Rectangle area, int type) {
   return mapRatioToArea(R4(startRatio, endRatio - startRatio), origin, area, type);
}

Vector2 mapRatioToArea(Vector2 ratio, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   Vector2 size = getSizeFromRatioType(realArea.width, realArea.height, type);
   return ratio * size + R4pos(realArea);
}

Vector2 mapRatioToArea(float ratioX, float ratioY, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   Vector2 size = getSizeFromRatioType(realArea.width, realArea.height, type);
   return V2(ratioX * size.x + realArea.x, ratioY * size.y + realArea.y);
}

Vector2 mapSizeRatioToArea(Vector2 ratio, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   Vector2 size = getSizeFromRatioType(realArea.width, realArea.height, type);
   return ratio * size;
}

Vector2 mapSizeRatioToArea(float ratioX, float ratioY, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   Vector2 size = getSizeFromRatioType(realArea.width, realArea.height, type);
   return V2(ratioX * size.x, ratioY * size.y);
}

Rectangle mapAreaToRatio(Rectangle rect, Vector2 origin, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   Vector2 size = R4size(rect);
   Vector2 anchor = R4pos(rect) + size * origin;
   return R4(mapAreaToRatio(anchor, realArea, RATIO), mapAreaToSizeRatio(size, realArea, type));
}

Rectangle mapAreaToRatio(Vector2 start, Vector2 end, Vector2 origin, Rectangle area, int type) {
   return mapAreaToRatio(R4(start, end - start), origin, area, type);
}

Vector2 mapAreaToRatio(Vector2 position, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   Vector2 size = getSizeFromRatioType(realArea.width, realArea.height, type);
   return (position - R4pos(realArea)) / size;
}

Vector2 mapAreaToRatio(float x, float y, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   Vector2 size = getSizeFromRatioType(realArea.width, realArea.height, type);
   return V2(x - realArea.x, y - realArea.y) / size;
}

Vector2 mapAreaToSizeRatio(Vector2 size, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   Vector2 scale = getSizeFromRatioType(realArea.width, realArea.height, type);
   return size / scale;
}

Vector2 mapAreaToSizeRatio(float width, float height, Rectangle area, int type) {
   return mapAreaToSizeRatio(V2(width, height), area, type);
}

float mapRatioToX(float ratioX, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   float size = getSizeFromRatioType(realArea.width, realArea.height, type).x;
   return ratioX * size + realArea.x;
}

float mapRatioToY(float ratioY, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   float size = getSizeFromRatioType(realArea.width, realArea.height, type).y;
   return ratioY * size + realArea.y;
}

float mapRatioToWidth(float ratioX, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   float size =getSizeFromRatioType(realArea.width, realArea.height, type).x;
   return ratioX * size;
}

float mapRatioToHeight(float ratioY, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   float size = getSizeFromRatioType(realArea.width, realArea.height, type).y;
   return ratioY * size;
}

float mapXToRatio(float x, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   float size = getSizeFromRatioType(realArea.width, realArea.height, type).x;
   return (x - realArea.x) / size;
}

float mapYToRatio(float y, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   float size = getSizeFromRatioType(realArea.width, realArea.height, type).y;
   return (y - realArea.y) / size;
}

float mapWidthToRatio(float width, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   float size = getSizeFromRatioType(realArea.width, realArea.height, type).x;
   return width / size;
}

float mapHeightToRatio(float height, Rectangle area, int type) {
   Rectangle realArea = getArea(area);
   float size = getSizeFromRatioType(realArea.width, realArea.height, type).y;
   return height / size;
}

// Grid utility
Vector2 gridPosition(Rectangle grid, int columns, int rows, int column, int row, Vector2 origin) {
   return V2((grid.width / columns) * (column + origin.x) + grid.x, (grid.height / rows) * (row + origin.y) + grid.y);
}

Vector2 gridRatio(Rectangle grid, int columns, int rows, int column, int row, Vector2 origin) {
   return mapAreaToRatio(gridPosition(grid, columns, rows, column, row, origin));
}

Rectangle gridRectangle(Vector2 size, Rectangle grid, int columns, int rows, int column, int row, Vector2 origin) {
   return R4(gridPosition(grid, columns, rows, column, row, origin), size);
}

Rectangle gridRatioRectangle(Vector2 sizeRatio, Rectangle grid, int columns, int rows, int column, int row, Vector2 origin) {
   return R4(gridRatio(grid, columns, rows, column, row, origin), sizeRatio);
}

Vector2 getGridCellSize(Rectangle grid, int columns, int rows) {
   return V2(grid.width / columns, grid.height / rows);
}

Vector2 getGridCellRatio(Rectangle grid, int columns, int rows, int type) {
   return mapAreaToSizeRatio(getGridCellSize(grid, columns, rows), WINDOW_AREA, type);
}

Vector2 getGridCell(Rectangle grid, int columns, int rows, Vector2 position) {
   if (!CheckCollisionPointRec(position, grid)) {
      return GRID_CELL_INVALID;
   }
   Vector2 local = position - R4pos(grid);
   return V2(fminf(local.x / (grid.width / columns), columns - 1), fminf(local.y / (grid.height / rows), rows - 1));
}

Vector2 snapToGrid(Rectangle grid, int columns, int rows, Vector2 position, Vector2 origin) {
   Vector2 cell = getGridCell(grid, columns, rows, position);
   if (cell == GRID_CELL_INVALID) {
      return position;
   }
   return gridPosition(grid, columns, rows, cell.x, cell.y, origin);
}

// Origin/source utility
Vector2 getTextSize(Font font, const char *text, float fontSize, float spacing) {
   return MeasureTextEx(font, text, fontSize, spacing);
}

Vector2 getTextOrigin(Font font, const char *text, float fontSize, float spacing, Vector2 origin) {
   return MeasureTextEx(font, text, fontSize, spacing) * origin;
}

// Render utility
void drawText(Font font, Vector2 position, const char *text, float fontSize, Vector2 origin, Color color, float rotation) {
   float spacing = fitSpacing(fontSize);
   Vector2 textOrigin = getTextOrigin(font, text, fontSize, spacing, origin);
   DrawTextPro(font, text, position, textOrigin, rotation, fontSize, spacing, color);
}

void drawTextResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Vector2 origin, Color color, Rectangle area, float rotation) {
   float fontSizeScaled = getFontSizeScaled(fontSize);
   float spacingScaled = fitSpacing(fontSizeScaled);
   Vector2 textOrigin = getTextOrigin(font, text, fontSizeScaled, spacingScaled, origin);
   Vector2 position = mapRatioToArea(ratio, getArea(area));
   DrawTextPro(font, text, position, textOrigin, rotation, fontSizeScaled, spacingScaled, color);
}

void drawText(const std::string &font, Vector2 position, const char *text, float fontSize, Vector2 origin, Color color, float rotation) {
   drawText(getFont(font), position, text, fontSize, origin, color, rotation);
}

void drawTextResponsive(const std::string &font, Vector2 ratio, const char *text, float fontSize, Vector2 origin, Color color, Rectangle area, float rotation) {
   drawTextResponsive(getFont(font), ratio, text, fontSize, origin, color, area, rotation);
}

void drawRect(Vector2 position, Vector2 size, Vector2 origin, Color color, float rotation) {
   DrawRectanglePro(R4(position, size), getOrigin(size, origin), rotation, color);
}

void drawRect(Rectangle rect, Vector2 origin, Color color, float rotation) {
   DrawRectanglePro(rect, R4origin(rect, origin), rotation, color);
}

void drawRectResponsive(Vector2 ratio, Vector2 sizeRatio, Vector2 origin, Color color, Rectangle area, int type, float rotation) {
   Rectangle realArea = getArea(area);
   Vector2 size = mapSizeRatioToArea(sizeRatio, realArea, type);
   Vector2 position = mapRatioToArea(ratio, realArea, RATIO);
   DrawRectanglePro(R4(position, size), getOrigin(size, origin), rotation, color);
}

void drawRectResponsive(Rectangle ratios, Vector2 origin, Color color, Rectangle area, int type, float rotation) {
   Rectangle realArea = getArea(area);
   Vector2 size = mapSizeRatioToArea(R4size(ratios), realArea, type);
   Vector2 position = mapRatioToArea(R4pos(ratios), realArea, RATIO);
   DrawRectanglePro(R4(position, size), getOrigin(size, origin), rotation, color);
}

void drawTexture(Texture texture, Vector2 position, Vector2 size, Vector2 origin, Color color, Rectangle source, float rotation) {
   DrawTexturePro(texture, getSource(source, texture), R4(position, size), getOrigin(size, origin), rotation, color);
}

void drawTexture(Texture texture, Rectangle rect, Vector2 origin, Color color, Rectangle source, float rotation) {
   DrawTexturePro(texture, getSource(source, texture), rect, R4origin(rect, origin), rotation, color);
}

void drawTextureResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Vector2 origin, Color color, Rectangle source, Rectangle area, int type, float rotation) {
   Rectangle realArea = getArea(area);
   Vector2 size = mapSizeRatioToArea(sizeRatio, realArea, type);
   Vector2 position = mapRatioToArea(ratio, realArea, RATIO);
   DrawTexturePro(texture, getSource(source, texture), R4(position, size), getOrigin(size, origin), rotation, color);
}

void drawTextureResponsive(Texture texture, Rectangle ratios, Vector2 origin, Color color, Rectangle source, Rectangle area, int type, float rotation) {
   Rectangle realArea = getArea(area);
   Vector2 size = mapSizeRatioToArea(R4size(ratios), realArea, type);
   Vector2 position = mapRatioToArea(R4pos(ratios), realArea, RATIO);
   DrawTexturePro(texture, getSource(source, texture), R4(position, size), getOrigin(size, origin), rotation, color);
}

void drawTexture(const std::string &texture, Vector2 position, Vector2 size, Vector2 origin, Color color, Rectangle source, float rotation) {
   drawTexture(getTexture(texture), position, size, origin, color, source, rotation);
}

void drawTexture(const std::string &texture, Rectangle rect, Vector2 origin, Color color, Rectangle source, float rotation) {
   drawTexture(getTexture(texture), rect, origin, color, source, rotation);
}

void drawTextureResponsive(const std::string &texture, Vector2 ratio, Vector2 sizeRatio, Vector2 origin, Color color, Rectangle source, Rectangle area, int type, float rotation) {
   drawTextureResponsive(getTexture(texture), ratio, sizeRatio, origin, color, source, area, type, rotation);
}

void drawTextureResponsive(const std::string &texture, Rectangle ratios, Vector2 origin, Color color, Rectangle source, Rectangle area, int type, float rotation) {
   drawTextureResponsive(getTexture(texture), ratios, origin, color, source, area, type, rotation);
}

// Animation render utility
static std::vector<AnimationConfig> animationConfig {{}};

AnimationConfig::AnimationConfig(Texture texture, size_t frameWidth, size_t frameHeight, size_t gap, size_t frameY, size_t frameCount, float frameTime, bool loop)
   : texture(texture), frameWidth(frameWidth), frameHeight(frameHeight), gapX(gap), gapY(gap), frameY(frameY), frameCount(frameCount), frameTime(frameTime), loop(loop) {}

AnimationConfig::AnimationConfig(Texture texture, size_t frameSize, size_t gap, size_t frameY, size_t frameCount, float frameTime, bool loop)
   : texture(texture), frameWidth(frameSize), frameHeight(frameSize), gapX(gap), gapY(gap), frameY(frameY), frameCount(frameCount), frameTime(frameTime), loop(loop) {}

AnimationConfig::AnimationConfig(Texture texture, size_t frameSize, size_t frameCount, float frameTime, bool loop)
   : texture(texture), frameWidth(frameSize), frameHeight(frameSize), gapX(0), gapY(0), frameY(0), frameCount(frameCount), frameTime(frameTime), loop(loop) {}

Animation::Animation(size_t ID, bool paused, bool flipX, bool flipY, bool randomStart)
   : ID(ID), frame(0), timer(0.0f), paused(paused), flipX(flipX), flipY(flipY), finished(false) {
   if (randomStart) {
      AnimationConfig &config = getAnimation(ID);
      timer = randomFloat(0.0f, config.frameTime);
   }
}

Animation::Animation(size_t ID, bool randomStart)
   : ID(ID), frame(0), timer(0.0f), paused(false), flipX(false), flipY(false), finished(false) {
   if (randomStart) {
      AnimationConfig &config = getAnimation(ID);
      timer = randomFloat(0.0f, config.frameTime);
   }
}

AnimationID pushAnimation(AnimationConfig config) {
   animationConfig.push_back(config);
   return animationConfig.size() - 1;
}

AnimationConfig &getAnimation(AnimationID ID) {
   if (ID <= 0 || ID >= animationConfig.size()) {
      printf("srulib::getAnimation: ID out of bounds. ID is %llu and animation config count is %llu.\n", ID, animationConfig.size());
      exit(EXIT_FAILURE);
   }
   return animationConfig[ID];
}

std::vector<AnimationConfig> &getAnimationContainer() {
   return animationConfig;
}

Rectangle getAnimationSource(Animation animation) {
   AnimationConfig &config = getAnimation(animation.ID);
   return getAnimationSource(animation, config);
}

Rectangle getAnimationSource(Animation animation, AnimationConfig config) {
   return R4(
      (config.frameWidth + config.gapX) * animation.frame,
      (config.frameHeight + config.gapY) * config.frameY,
      (float)config.frameWidth * (animation.flipX ? -1.0f : 1.0f),
      (float)config.frameHeight * (animation.flipY ? -1.0f : 1.0f)
   );
}

bool isAnimationPlaying(Animation &animation, AnimationID ID) {
   AnimationConfig &config = getAnimation(animation.ID);
   return animation.ID == ID && !(animation.finished && !config.loop);
}

void setAnimationState(Animation &animation, AnimationID ID) {
   if (animation.ID == ID) {
      return;
   }
   animation.ID = ID;
   animation.frame = 0;
   animation.timer = 0.0f;
   animation.finished = false;
}

void forceAnimationState(Animation &animation, AnimationID ID) {
   animation.ID = ID;
   animation.frame = 0;
   animation.timer = 0.0f;
   animation.finished = false;
}

void animate(Animation &animation, float DT) {
   AnimationConfig &config = getAnimation(animation.ID);
   if (animation.paused || (animation.finished && !config.loop)) {
      return;
   }

   animation.timer += DT;
   if (animation.timer >= config.frameTime) {
      animation.timer -= config.frameTime;
      animation.frame = (animation.frame + 1) % config.frameCount;
      if (animation.frame == 0) {
         animation.finished = true;
      }
   }
}

void drawTextureAnimated(Animation animation, Vector2 position, Vector2 size, Vector2 origin, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(position, size), getOrigin(size, origin), rotation, color);
}

void drawTextureAnimated(Animation animation, Rectangle rect, Vector2 origin, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), rect, getOrigin(R4size(rect), origin), rotation, color);
}

void drawTextureAnimatedResponsive(Animation animation, Vector2 ratio, Vector2 sizeRatio, Vector2 origin, Color color, Rectangle area, int type, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   Rectangle realArea = getArea(area);
   Vector2 size = mapSizeRatioToArea(sizeRatio, realArea, type);
   Vector2 position = mapRatioToArea(ratio, realArea, RATIO);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(position, size), getOrigin(size, origin), rotation, color);
}

void drawTextureAnimatedResponsive(Animation animation, Rectangle ratios, Vector2 origin, Color color, Rectangle area, int type, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   Rectangle realArea = getArea(area);
   Vector2 size = mapSizeRatioToArea(R4size(ratios), realArea, type);
   Vector2 position = mapRatioToArea(R4pos(ratios), realArea, RATIO);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(position, size), getOrigin(size, origin), rotation, color);
}
