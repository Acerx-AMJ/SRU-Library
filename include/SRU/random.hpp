#pragma once
#include <raylib.h>

#ifdef SRULIB_USE_RAND
#include <cstdlib>
#include <ctime>

inline void seedRandom(int seed) {
   srand(seed);
}

inline void seedRandomFromTime() {
   srand(time(nullptr));
}

inline size_t randomIndex(size_t size) {
   return rand() % size;
}

inline int randomInt(int min, int max) {
   return min + (rand() % (max - min + 1));
}

inline float randomFloat(float min, float max) {
   return min + (float)rand() / (float)RAND_MAX * (max - min);
}

inline bool chance(int percent) {
   return (rand() % 101) <= percent;
}

inline bool chancePrecise(float percent) {
   return (float)rand() / (float)RAND_MAX <= percent;
}

#else
#include <random>

inline std::mt19937 &getRNG() {
   static std::mt19937 rng {std::random_device{}()};
   return rng;
}

inline void seedRandom(int seed) {
   getRNG().seed(seed);
}

inline void seedRandomFromTime() {
   getRNG().seed(std::random_device{}());
}

inline size_t randomIndex(size_t size) {
   return std::uniform_int_distribution<size_t>{0, size-1}(getRNG());
}

inline int randomInt(int min, int max) {
   return std::uniform_int_distribution<int>{min, max}(getRNG());
}

inline float randomFloat(float min, float max) {
   return std::uniform_real_distribution<float>{min, max}(getRNG());
}

inline bool chance(int percent) {
   return randomInt(0, 100) <= percent;
}

inline bool chancePrecise(float percent) {
   return randomFloat(0.0f, 1.0f) <= percent;
}

#endif // #ifdef SRULIB_USE_RAND

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
