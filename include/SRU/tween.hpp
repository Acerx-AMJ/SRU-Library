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
typedef float(*Formula)(float);
enum class TweenValue: char {
   none, integer, floating, v2, v3, v4, r4, color
};

enum class TweenType: char {
   automatic, manual, loop, pingpong
};

struct TweenID {
   size_t ID = 0;
   int generation = 0;

   constexpr TweenID() = default;
   constexpr TweenID(size_t ID): ID(ID) {}
   constexpr TweenID(size_t ID, int generation): ID(ID), generation(generation) {}

   // chain
   TweenID chain(int *value, int target, float time, Formula formula = linear);
   TweenID chain(float *value, float target, float time, Formula formula = linear);
   TweenID chain(Vector2 *value, Vector2 target, float time, Formula formula = linear);
   TweenID chain(Vector3 *value, Vector3 target, float time, Formula formula = linear);
   TweenID chain(Vector4 *value, Vector4 target, float time, Formula formula = linear);
   TweenID chain(Rectangle *value, Rectangle target, float time, Formula formula = linear);
   TweenID chain(Color *value, Color target, float time, Formula formula = linear);

   // parallel
   TweenID parallel(int *value, int target, float time, Formula formula = linear);
   TweenID parallel(float *value, float target, float time, Formula formula = linear);
   TweenID parallel(Vector2 *value, Vector2 target, float time, Formula formula = linear);
   TweenID parallel(Vector3 *value, Vector3 target, float time, Formula formula = linear);
   TweenID parallel(Vector4 *value, Vector4 target, float time, Formula formula = linear);
   TweenID parallel(Rectangle *value, Rectangle target, float time, Formula formula = linear);
   TweenID parallel(Color *value, Color target, float time, Formula formula = linear);

   // methods
   void stop();
   void resume();
   void toggleStopped();
   void restart();
   void reverse();
   void kill();

   bool isStopped();
   bool isKilled();
   bool isPlaying();
   bool isFinished();
   bool isReversed();
   bool isValid();
   bool isRoot();

   struct Tween &tween();
   struct Tween &root();
};

struct Tween {
   Formula formula = linear;
   TweenID id = 0;
   TweenID root = 0;
   TweenID chained = 0;
   TweenID paralleled = 0;
   TweenValue value = TweenValue::none;
   TweenType type = TweenType::automatic;

   bool reversed = false;
   bool stopped = false;
   bool killed = false;
   bool started = false;
   bool finished = false;

   float timer = 0.0f;
   float time = 0.0f;
   float progress = 0.0f;
   int generation = 0;

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
TweenID createTween(int *value, int target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(float *value, float target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(Vector2 *value, Vector2 target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(Vector3 *value, Vector3 target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(Vector4 *value, Vector4 target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(Rectangle *value, Rectangle target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(Color *value, Color target, float time, Formula formula = linear, TweenType type = TweenType::automatic);

// update tweens
void updateTweens(float DT);
void killAllTweens();
void killFinishedTweens();

size_t getTweenCount();
size_t getTweenFreeSpotCount();
