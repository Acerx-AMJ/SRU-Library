#pragma once
#include <raylib.h>
#include <raymath.h>

template<typename T, typename Y>
constexpr inline Vector2 V2(T x, Y y) {
   return {static_cast<float>(x), static_cast<float>(y)};
}

template<>
constexpr inline Vector2 V2(float x, float y) {
   return {x, y};
}

template<typename T>
constexpr inline Vector2 V2(T value) {
   float v = static_cast<float>(value);
   return {v, v};
}

template<>
constexpr inline Vector2 V2(float value) {
   return {value, value};
}

constexpr inline Vector2 V2() {
   return {0.0f, 0.0f};
}

template<typename T, typename Y, typename U>
constexpr inline Vector3 V3(T x, Y y, U z) {
   return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)};
}

template<>
constexpr inline Vector3 V3(float x, float y, float z) {
   return {x, y, z};
}

template<typename T>
constexpr inline Vector3 V3(T value) {
   float v = static_cast<float>(value);
   return {value, value, value};
}

template<>
constexpr inline Vector3 V3(float value) {
   return {value, value, value};
}

constexpr inline Vector3 V3() {
   return {0.0f, 0.0f, 0.0f};
}

template<typename T, typename Y, typename U, typename I>
constexpr inline Vector4 V4(T x, Y y, U z, I w) {
   return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)};
}

template<>
constexpr inline Vector4 V4(float x, float y, float z, float w) {
   return {x, y, z, w};
}

template<typename T>
constexpr inline Vector4 V4(T value) {
   float v = static_cast<float>(value);
   return {value, value, value, value};
}

template<>
constexpr inline Vector4 V4(float value) {
   return {value, value, value, value};
}

constexpr inline Vector4 V4() {
   return {0.0f, 0.0f, 0.0f, 0.0f};
}

template<typename T, typename Y, typename U, typename I>
constexpr inline Rectangle R4(T x, Y y, U h, I w) {
   return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h)};
}

template<>
constexpr inline Rectangle R4(float x, float y, float h, float w) {
   return {x, y, h, w};
}

constexpr inline Rectangle R4() {
   return {0.0f, 0.0f, 0.0f, 0.0f};
}

template<typename T, typename Y, typename U, typename I>
constexpr inline Color RGBA(T r, Y g, U b, I a) {
   return {static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), static_cast<unsigned char>(a)};
}

template<>
constexpr inline Color RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
   return {r, g, b, a};
}

template<typename T, typename Y, typename U>
constexpr inline Color RGB(T r, Y g, U b) {
   return {static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), 255};
}

template<>
constexpr inline Color RGB(unsigned char r, unsigned char g, unsigned char b) {
   return {r, g, b, 255};
}

constexpr inline Color HEX(const char *hex) {
   size_t len = 0;
   while (hex[len] != '\0') len += 1;
   
   if ((len != 4 && len != 5 && len != 7 && len != 9) || hex[0] != '#') {
      return BLACK;
   }

   auto valueFromChar = [](char c) -> int {
      if (c >= '0' && c <= '9') return c - '0';
      if (c >= 'a' && c <= 'f') return c - 'a' + 10;
      if (c >= 'A' && c <= 'F') return c - 'A' + 10;
      return 0;
   };
   
   // short format
   if (len == 4 || len == 5) {
      int red = valueFromChar(hex[1]);
      int green = valueFromChar(hex[2]);
      int blue = valueFromChar(hex[3]);
      int alpha = valueFromChar(len == 4 ? 'f' : hex[4]); // alpha is 255 by default

      return RGBA(red * 17, green * 17, blue * 17, alpha * 17);
   }
   // long format
   else {
      int red1 = valueFromChar(hex[1]);
      int red2 = valueFromChar(hex[2]);
      int green1 = valueFromChar(hex[3]);
      int green2 = valueFromChar(hex[4]);
      int blue1 = valueFromChar(hex[5]);
      int blue2 = valueFromChar(hex[6]);
      int alpha1 = valueFromChar(len == 7 ? 'f' : hex[7]); // alpha is 255 by default
      int alpha2 = valueFromChar(len == 7 ? 'f' : hex[8]);

      return RGBA(red1 * 16 + red2, green1 * 16 + green2, blue1 * 16 + blue2, alpha1 * 16 + alpha2);
   }
}
