#include "SRU/render.hpp"
#include "SRU/random.hpp"
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
   DrawRectanglePro(R4(mapRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), V2(), rotation, color);
}

void drawRectCenteredResponsiveCubic(Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   Vector2 size = mapCubicRatioToScreen(sizeRatio);
   DrawRectanglePro(R4(mapRatioToScreen(ratio), size), getOrigin(size), rotation, color);
}

void drawRectOriginResponsiveCubic(Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color, float rotation) {
   DrawRectanglePro(R4(mapRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), origin, rotation, color);
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
   DrawTexturePro(texture, getSource(texture), R4(mapRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), V2(), rotation, color);
}

void drawTextureCenteredResponsiveCubic(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   Vector2 size = mapCubicRatioToScreen(sizeRatio);
   DrawTexturePro(texture, getSource(texture), R4(mapRatioToScreen(ratio), size), getOrigin(size), rotation, color);
}

void drawTextureOriginResponsiveCubic(Texture texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color, float rotation) {
   DrawTexturePro(texture, getSource(texture), R4(mapRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), origin, rotation, color);
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

// Animation render utility
static std::vector<AnimationConfig> animationConfig;

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
   if (ID >= animationConfig.size()) {
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
   return R4(
      (config.frameWidth + config.gapX) * animation.frame,
      (config.frameHeight + config.gapY) * config.frameY,
      config.frameWidth * (animation.flipX ? -1 : 1),
      config.frameHeight * (animation.flipY ? -1 : 1)
   );
}

Rectangle getAnimationSource(Animation animation, AnimationConfig config) {
   return R4(
      (config.frameWidth + config.gapX) * animation.frame,
      (config.frameHeight + config.gapY) * config.frameY,
      config.frameWidth * (animation.flipX ? -1 : 1),
      config.frameHeight * (animation.flipY ? -1 : 1)
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

void drawTextureAnimated(Animation animation, Vector2 position, Vector2 size, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(position, size), V2(), rotation, color);
}

void drawTextureAnimatedCentered(Animation animation, Vector2 position, Vector2 size, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(position, size), getOrigin(size), rotation, color);
}

void drawTextureAnimatedOrigin(Animation animation, Vector2 position, Vector2 origin, Vector2 size, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(position, size), origin, rotation, color);
}

void drawTextureAnimatedResponsive(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(mapRatioToScreen(ratio), mapRatioToScreen(sizeRatio)), V2(), rotation, color);
}

void drawTextureAnimatedCenteredResponsive(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   Vector2 size = mapRatioToScreen(sizeRatio);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(mapRatioToScreen(ratio), size), getOrigin(size), rotation, color);
}

void drawTextureAnimatedOriginResponsive(Animation animation, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(mapRatioToScreen(ratio), mapRatioToScreen(sizeRatio)), origin, rotation, color);
}

void drawTextureAnimatedResponsiveCubic(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(mapRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), V2(), rotation, color);
}

void drawTextureAnimatedCenteredResponsiveCubic(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   Vector2 size = mapCubicRatioToScreen(sizeRatio);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(mapRatioToScreen(ratio), size), getOrigin(size), rotation, color);
}

void drawTextureAnimatedOriginResponsiveCubic(Animation animation, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color, float rotation) {
   AnimationConfig &config = getAnimation(animation.ID);
   DrawTexturePro(config.texture, getAnimationSource(animation, config), R4(mapRatioToScreen(ratio), mapCubicRatioToScreen(sizeRatio)), origin, rotation, color);
}
