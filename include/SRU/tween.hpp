#pragma once
#include <cmath>
#include <raylib.h>

// formulas
constexpr inline float linear(float t) {
   return t;
}

constexpr inline float quadratic(float t) {
   return t * t;
}

constexpr inline float quadraticOut(float t) {
   return t * (2.0f - t);
}

constexpr inline float quadraticInOut(float t) {
   t *= 2.0f;
   if (t < 1.0f) {
      return 0.5f * t * t;
   }
   t -= 1.0f;
   return -0.5f * (t * (t - 2.0f) - 1.0f);
}

constexpr inline float cubic(float t) {
   return t * t * t;
}

constexpr inline float cubicOut(float t) {
   t -= 1.0f;
   return t * t * t + 1;
}

constexpr inline float cubicInOut(float t) {
   t *= 2.0f;
   if (t < 1.0f) {
      return 0.5f * t * t * t;
   }
   t -= 2.0f;
   return 0.5f * (t * t * t + 2);
}

constexpr inline float sinusoidal(float t) {
   return 1.0f - std::cos(t * PI / 2.0f);
}

constexpr inline float sinusoidalOut(float t) {
   return std::sin(t * PI / 2.0f);
}

constexpr inline float sinusoidalInOut(float t) {
   return 0.5f * (1.0f - std::cos(PI * t));
}

constexpr inline float exponential(float t) {
   return t == 0.0f ? 0.0f : std::pow(1024.0f, t - 1.0f);
}

constexpr inline float exponentialOut(float t) {
   return t == 1.0f ? 1.0f : 1.0f - std::pow(2.0f, -10.0f * t);
}

constexpr inline float exponentialInOut(float t) {
   if (t == 0.0f) return 0.0f;
   if (t == 1.0f) return 1.0f;
   t *= 2.0f;
   if (t < 1.0f) return 0.5f * std::pow(1024.0f, t - 1.0f);
   return 0.5f * (-std::pow(2.0f, -10.0f * (t - 1.0f)) + 2.0f);
}

constexpr inline float circular(float t) {
   return 1.0f - std::sqrt(1.0f - t * t);
}

constexpr inline float circularOut(float t) {
   t -= 1.0f;
   return std::sqrt(1.0f - t * t);
}

constexpr inline float circularInOut(float t) {
   t *= 2.0f;
   if (t < 1.0f) {
      return -0.5f * (std::sqrt(1.0f - t * t) - 1.0f);
   }
   t -= 2.0f;
   return 0.5f * (std::sqrt(1.0f - t * t) + 1.0f);
}

constexpr inline float elastic(float t) {
   if (t == 0.0f) return 0.0f;
   if (t == 1.0f) return 1.0f;
   return -std::pow(2.0f, 10.0f * (t - 1.0f)) * std::sin((t - 1.1f) * 5.0f * PI);
}

constexpr inline float elasticOut(float t) {
   if (t == 0.0f) return 0.0f;
   if (t == 1.0f) return 1.0f;
   return std::pow(2.0f, -10.0f * t) * std::sin((t - 0.1f) * 5.0f * PI) + 1.0f;
}

constexpr inline float elasticInOut(float t) {
   if (t == 0.0f) return 0.0f;
   if (t == 1.0f) return 1.0f;
   t *= 2.0f;
   if (t < 1.0f) {
      return -0.5f * std::pow(2.0f, 10.0f * (t - 1.0f)) * std::sin((t - 1.1f) * 5.0f * PI);
   }
   return 0.5f * std::pow(2.0f, -10.0f * (t - 1.0f)) * std::sin((t - 1.1f) * 5.0f * PI) + 1.0f;
}

constexpr inline float back(float t) {
   float s = 1.70158f;
   return t * t * ((s + 1.0f) * t - s);
}

constexpr inline float backOut(float t) {
   float s = 1.70158f;
   t -= 1.0f;
   return t * t * ((s + 1.0f) * t + s) + 1.0f;
}

constexpr inline float backInOut(float t) {
   float s = 1.70158f * 1.525f;
   t *= 2.0f;
   if (t < 1.0f) {
      return 0.5f * (t * t * ((s + 1.0f) * t - s));
   }
   t -= 2.0f;
   return 0.5f * (t * t * ((s + 1.0f) * t + s) + 2.0f);
}

constexpr inline float bounceOut(float t);
constexpr inline float bounce(float t) {
   return 1.0f - bounceOut(1.0f - t);  
}

constexpr inline float bounceOut(float t) {
   if (t < (1.0f / 2.75f)) {
      return 7.5625f * t * t;
   } else if (t < (2.0f / 2.75f)) {
      t -= (1.5f / 2.75f);
      return 7.5625f * t * t + 0.75f;
   } else if (t < (2.5 / 2.75)) {
      t -= (2.25f / 2.75f);
      return 7.5625f * t * t + 0.9375f;
   } else {
      t -= (2.625f / 2.75f);
      return 7.5625f * t * t + 0.984375f;
   }
}

constexpr inline float bounceInOut(float t) {
   if (t < 0.5f) {
      return bounce(t * 2.0f) * 0.5f;
   }
   return bounceOut(t * 2.0f - 1.0f) * 0.5f + 0.5f;
}

// tweens
using TweenID = size_t;
using Formula = float(*)(float);

enum class TweenType {
   none, integer, floating, v2, v3, v4, r4, color
};

struct Tween {
   TweenType type = TweenType::none;
   Formula formula = linear;
   TweenID id = 0;
   TweenID sequenced = 0;

   float timer = 0.0f;
   float time = 0.0f;
   float progress = 0.0f;
   bool paused = false;
   bool finished = false;

   union {
      struct { int *ivalue, istart, iend; };
      struct { float *fvalue, fstart, fend; };
      struct { Vector2 *v2value, v2start, v2end; };
      struct { Vector3 *v3value, v3start, v3end; };
      struct { Vector4 *v4value, v4start, v4end; };
      struct { Rectangle *r4value, r4start, r4end; };
      struct { Color *cvalue, cstart, cend; };
   };
};

// create tweens
TweenID createTween(int *value, int target, float time, Formula formula = linear);
TweenID createTween(float *value, float target, float time, Formula formula = linear);
TweenID createTween(Vector2 *value, Vector2 target, float time, Formula formula = linear);
TweenID createTween(Vector3 *value, Vector3 target, float time, Formula formula = linear);
TweenID createTween(Vector4 *value, Vector4 target, float time, Formula formula = linear);
TweenID createTween(Rectangle *value, Rectangle target, float time, Formula formula = linear);
TweenID createTween(Color *value, Color target, float time, Formula formula = linear);

// create sequenced tweens
TweenID createSequencedTween(TweenID parentID, int *value, int target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, float *value, float target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, Vector2 *value, Vector2 target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, Vector3 *value, Vector3 target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, Vector4 *value, Vector4 target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, Rectangle *value, Rectangle target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, Color *value, Color target, float time, Formula formula = linear);

// tween functions
void pauseTween(TweenID ID);
void resumeTween(TweenID ID);
void killTween(TweenID ID);

Tween &getTween(TweenID ID);
float getTweenProgress(TweenID ID);
bool isTweenFinished(TweenID ID);
bool isTweenPaused(TweenID ID);
bool isTweenPlaying(TweenID ID);
bool isTweenValid(TweenID ID);

void updateTweens(float DT);
