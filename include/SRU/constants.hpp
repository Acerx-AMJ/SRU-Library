#pragma once
#include <raylib.h>

// Constants
constexpr inline Vector2 TOP_LEFT = {0.0f, 0.0f};
constexpr inline Vector2 TOP_CENTER = {0.5f, 0.0f};
constexpr inline Vector2 TOP_RIGHT = {1.0f, 0.0f};
constexpr inline Vector2 CENTER_LEFT = {0.0f, 0.5f};
constexpr inline Vector2 CENTER = {0.5f, 0.5f};
constexpr inline Vector2 CENTER_RIGHT = {1.0f, 0.5f};
constexpr inline Vector2 BOTTOM_LEFT = {0.0f, 1.0f};
constexpr inline Vector2 BOTTOM_CENTER = {0.5f, 1.0f};
constexpr inline Vector2 BOTTOM_RIGHT = {1.0f, 1.0f};

constexpr inline Rectangle FULL_SOURCE = {0, 0, 0, 0};
constexpr inline Rectangle WINDOW_AREA = {0, 0, 0, 0};
constexpr inline Vector2 GRID_CELL_INVALID = {-1.0f, -1.0f};

constexpr inline int RATIO = 0;
constexpr inline int CUBIC_RATIO = 1;
constexpr inline int FILL_RATIO = 2;

constexpr inline int FILE_TRIMMED = 0;
constexpr inline int FILE_TRIMMED_COMMENTS = 1;
constexpr inline int FILE_RAW = 2;
