#pragma once
#include <raylib.h>
#include <raymath.h>

// Vector2 construction utility
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

// Vector3 construction utility
template<typename T, typename Y, typename U>
constexpr inline Vector3 V3(T x, Y y, U z) {
   return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)};
}

template<>
constexpr inline Vector3 V3(float x, float y, float z) {
   return {x, y, z};
}

constexpr inline Vector3 V3(Color color) {
   return V3(color.r, color.g, color.b) / 255.0f;
}

template<typename T>
constexpr inline Vector3 V3(T value) {
   float v = static_cast<float>(value);
   return {v, v, v};
}

template<>
constexpr inline Vector3 V3(float value) {
   return {value, value, value};
}

constexpr inline Vector3 V3() {
   return {0.0f, 0.0f, 0.0f};
}

// Vector4 construction utility
template<typename T, typename Y, typename U, typename I>
constexpr inline Vector4 V4(T x, Y y, U z, I w) {
   return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w)};
}

template<>
constexpr inline Vector4 V4(float x, float y, float z, float w) {
   return {x, y, z, w};
}

constexpr inline Vector4 V4(Color color) {
   return V4(color.r, color.g, color.b, color.a) / 255.0f;
}

template<typename T>
constexpr inline Vector4 V4(T value) {
   float v = static_cast<float>(value);
   return {v, v, v, v};
}

template<>
constexpr inline Vector4 V4(float value) {
   return {value, value, value, value};
}

constexpr inline Vector4 V4() {
   return {0.0f, 0.0f, 0.0f, 0.0f};
}

// Rectangle construction utility
template<typename T, typename Y, typename U, typename I>
constexpr inline Rectangle R4(T x, Y y, U w, I h) {
   return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h)};
}

template<>
constexpr inline Rectangle R4(float x, float y, float w, float h) {
   return {x, y, w, h};
}

constexpr inline Rectangle R4() {
   return {0.0f, 0.0f, 0.0f, 0.0f};
}

constexpr inline Rectangle R4(Vector2 position, Vector2 size) {
   return {position.x, position.y, size.x, size.y};
}

// Constexpr color fade
constexpr inline Color fadeColor(Color color, float a) {
   color.a = a * 255.0f;
   return color;
}

// Color construction utility
template<typename T, typename Y, typename U>
constexpr inline Color RGB(T r, Y g, U b) {
   return {static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), 255};
}

template<>
constexpr inline Color RGB(unsigned char r, unsigned char g, unsigned char b) {
   return {r, g, b, 255};
}

constexpr inline Color RGB(Vector3 color) {
   return RGB(color.x * 255.0f, color.y * 255.0f, color.z * 255.0f);
}

template<typename T, typename Y, typename U, typename I>
constexpr inline Color RGBA(T r, Y g, U b, I a) {
   return {static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), static_cast<unsigned char>(a)};
}

template<>
constexpr inline Color RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
   return {r, g, b, a};
}

constexpr inline Color RGBA(Vector4 color) {
   return RGBA(color.x * 255.0f, color.y * 255.0f, color.z * 255.0f, color.w * 255.0f);
}

constexpr inline Color RGBA(Color rgb, unsigned char a) {
   return {rgb.r, rgb.g, rgb.b, a};
}

// String must be in one of the formats: #rgb, #rgba, #rrggbb or #rrggbbaa, where symbols are 0-9, a-f or A-F.
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

constexpr inline Color HSL(float h, float s, float l) {
   h /= 360.0f;
   if (s == 0) {
      float v = l * 255.0f;
      return RGB(v, v, v);
   }

   auto hue = [](float p, float q, float t) {
      if (t < 0.0f) t += 1.0f;
      if (t > 1.0f) t -= 1.0f;
      if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
      if (t < 1.0f / 2.0f) return q;
      if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
      return p;
   };

   float q = (l < 0.5f ? l * (s + 1.0f) : l + s - l * s);
   float p = 2.0f * l - q;
   return RGB(
      hue(p, q, h + 1.0f / 3.0f) * 255.0f,
      hue(p, q, h) * 255.0f,
      hue(p, q, h - 1.0f / 3.0f) * 255.0f
   );
}

constexpr inline Color HSLA(float h, float s, float l, float a) {
   return fadeColor(HSL(h, s, l), a);
}

constexpr inline Color HSV(float h, float s, float v) {
   h /= 360.0f;
   int i = floor(h * 6.0f);
   float f = h * 6.0f - i;
   float p = v * (1.0f - s);
   float q = v * (1.0f - f * s);
   float t = v * (1.0f - (1.0f - f) * s);

   switch (i % 6) {
      case 0: return RGB(v * 255.0f, t * 255.0f, p * 255.0f);
      case 1: return RGB(q * 255.0f, v * 255.0f, p * 255.0f);
      case 2: return RGB(p * 255.0f, v * 255.0f, t * 255.0f);
      case 3: return RGB(p * 255.0f, q * 255.0f, v * 255.0f);
      case 4: return RGB(t * 255.0f, p * 255.0f, v * 255.0f);
      case 5: return RGB(v * 255.0f, p * 255.0f, q * 255.0f);
      default: return {};
   }
}

constexpr inline Color HSVA(float h, float s, float v, float a) {
   return fadeColor(HSV(h, s, v), a);
}
