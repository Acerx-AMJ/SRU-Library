#pragma once
#include "raylib.h"
#include <string>
#include <vector>

// Text altering functions
std::string wrap(const std::string &string, Font font, float maxWidth, float fontSize);
std::string truncate(const std::string &string, Font font, float maxWidth, float fontSize);
std::string fitInside(const std::string &string, Font font, Vector2 maxSize, float fontSize);
std::vector<std::string> divideText(const std::string &string, Font font, float maxWidth, float fontSize);
std::string toRomanNumeral(size_t number);

std::string toUpper(const std::string &string);
std::string toLower(const std::string &string);
std::string toTitle(const std::string &string);
std::string capitalize(const std::string &string);
std::string trim(const std::string &string);
std::string trimLeft(const std::string &string);
std::string trimRight(const std::string &string);

std::vector<std::string> split(const std::string &string, char delimiter);
std::vector<std::string> split(const std::string &string, const std::string &delimiter);
std::vector<std::string> splitOnWhiteSpace(const std::string &string);
std::string join(const std::vector<std::string> &parts, const std::string &delimiter);
std::string join(const std::vector<std::string> &parts);
std::vector<std::string> clean(const std::vector<std::string> &strings);

// Text altering in place functions
void wrapInPlace(std::string &string, Font font, float maxWidth, float fontSize);
void truncateInPlace(std::string &string, Font font, float maxWidth, float fontSize);
void fitInsideInPlace(std::string &string, Font font, Vector2 maxSize, float fontSize);
void divideTextInPlace(std::vector<std::string> &output, const std::string &string, Font font, float maxWidth, float fontSize);
void toRomanNumeralInPlace(std::string &string, size_t number);

void toUpperInPlace(std::string &string);
void toLowerInPlace(std::string &string);
void toTitleInPlace(std::string &string);
void capitalizeInPlace(std::string &string);
void trimInPlace(std::string &string);
void trimLeftInPlace(std::string &string);
void trimRightInPlace(std::string &string);

void splitInPlace(std::vector<std::string> &output, const std::string &string, char delimiter);
void splitInPlace(std::vector<std::string> &output, const std::string &string, const std::string &delimiter);
void splitOnWhiteSpaceInPlace(std::vector<std::string> &output, const std::string &string);
void joinInPlace(std::string &output, const std::vector<std::string> &parts, const std::string &delimiter);
void joinInPlace(std::string &output, const std::vector<std::string> &parts);
void cleanInPlace(std::vector<std::string> &strings);

// Non-altering text functions
bool contains(const std::string &string, const std::string &substring);
bool startsWith(const std::string &string, const std::string &substring);
bool endsWith(const std::string &string, const std::string &substring);
