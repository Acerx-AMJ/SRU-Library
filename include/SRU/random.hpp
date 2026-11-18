#pragma once
#include "SRU/error.hpp"
#include <raylib.h>
#include <random>

inline std::mt19937 &getRNG() {
   static thread_local std::mt19937 rng {std::random_device{}()};
   return rng;
}

inline void seedRandom(int seed) {
   getRNG().seed(seed);
}

inline void seedRandomFromTime() {
   getRNG().seed(std::random_device{}());
}

inline size_t randomIndex(size_t size) {
   if (size == 0) {
      SRULibError("srulib::randomIndex: Cannot get random index from size %zu.\n", size);
      return 0;
   }
   return std::uniform_int_distribution<size_t>{0, size-1}(getRNG());
}

inline int randomInt(int min, int max) {
   if (min > max) {
      SRULibError("srulib::randomInt: Min cannot be larger than Max. %d <= %d failed.\n", min, max);
      return 0;
   }
   return std::uniform_int_distribution<int>{min, max}(getRNG());
}

inline float randomFloat(float min, float max) {
   if (min > max) {
      SRULibError("srulib::randomFloat: Min cannot be larger than Max. %f <= %f failed.\n", min, max);
      return 0.0f;
   }
   return std::uniform_real_distribution<float>{min, max}(getRNG());
}

inline bool chance(int percent) {
   return randomInt(0, 99) < percent;
}

inline bool chancePrecise(float percent) {
   return randomFloat(0.0f, 1.0f) < percent;
}

inline Vector2 randomV2(Vector2 min, Vector2 max) {
   return {randomFloat(min.x, max.x), randomFloat(min.y, max.y)};
}

inline Vector2 randomV2(float min, float max) {
   return {randomFloat(min, max), randomFloat(min, max)};
}

inline Vector2 randomV2Value(float min, float max) {
   float value = randomFloat(min, max);
   return {value, value};
}

inline Vector3 randomV3(Vector3 min, Vector3 max) {
   return {randomFloat(min.x, max.x), randomFloat(min.y, max.y), randomFloat(min.z, max.z)};
}

inline Vector3 randomV3(float min, float max) {
   return {randomFloat(min, max), randomFloat(min, max), randomFloat(min, max)};
}

inline Vector3 randomV3Value(float min, float max) {
   float value = randomFloat(min, max);
   return {value, value, value};
}

inline Vector4 randomV4(Vector4 min, Vector4 max) {
   return {randomFloat(min.x, max.x), randomFloat(min.y, max.y), randomFloat(min.z, max.z), randomFloat(min.w, max.w)};
}

inline Vector4 randomV4(float min, float max) {
   return {randomFloat(min, max), randomFloat(min, max), randomFloat(min, max), randomFloat(min, max)};
}

inline Vector4 randomV4Value(float min, float max) {
   float value = randomFloat(min, max);
   return {value, value, value, value};
}

template<class T>
inline auto &randomElement(T &range) {
   return range[randomIndex(range.size())];
}
