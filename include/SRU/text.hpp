#pragma once
#include "raylib.h"
#include <string>

std::string wrap(const std::string &string, Font font, float maxWidth, float fontSize, float spacing);
std::string truncate(const std::string &string, Font font, float maxWidth, float fontSize, float spacing);
std::string fitInside(const std::string &string, Font font, Vector2 maxSize, float fontSize, float spacing);
std::string toRomanNumeral(size_t number);

std::string toUpper(const std::string &string);
std::string toLower(const std::string &string);
std::string trim(const std::string &string);
std::string trimLeft(const std::string &string);
std::string trimRight(const std::string &string);

void wrapInPlace(std::string &string, Font font, float maxWidth, float fontSize, float spacing);
void truncateInPlace(std::string &string, Font font, float maxWidth, float fontSize, float spacing);
void fitInsideInPlace(std::string &string, Font font, Vector2 maxSize, float fontSize, float spacing);
void toRomanNumeralInPlace(std::string &string, size_t number);

void toUpperInPlace(std::string &string);
void toLowerInPlace(std::string &string);
void trimInPlace(std::string &string);
void trimLeftInPlace(std::string &string);
void trimRightInPlace(std::string &string);

float fitFontSize(const char *string, Font font, float maxWidth, float spacing);
float fitFontSize(const std::string &string, Font font, float maxWidth, float spacing);
