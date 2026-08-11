#pragma once
#include "raylib.h"
#include <string>
#include <unordered_map>
#include <vector>

// File getter functions
std::vector<std::string> getLinesFromFile(const std::string &path);
std::vector<std::string> getRawLinesFromFile(const std::string &path);
std::vector<std::string> getLinesFromFileIgnoringComments(const std::string &path, const std::string &comment);

std::string getRandomLineFromFile(const std::string &path);
std::string getRandomRawLineFromFile(const std::string &path);
std::string getRandomLineFromFileIgnoringComments(const std::string &path, const std::string &comment);

std::unordered_map<std::string, std::string> getKeyValuePairFromFile(const std::string &path, const std::string &delimiter);
std::unordered_map<std::string, std::string> getRawKeyValuePairFromFile(const std::string &path, const std::string &delimiter);
std::unordered_map<std::string, std::string> getKeyValuePairFromFileIgnoringComments(const std::string &path, const std::string &delimiter, const std::string &comment);

std::string getFileContents(const std::string &path);

// File getter in place functions
void getLinesFromFileInPlace(std::vector<std::string> &output, const std::string &path);
void getRawLinesFromFileInPlace(std::vector<std::string> &output, const std::string &path);
void getLinesFromFileIgnoringCommentsInPlace(std::vector<std::string> &output, const std::string &path, const std::string &comment);

void getRandomLineFromFileInPlace(std::string &output, const std::string &path);
void getRandomRawLineFromFileInPlace(std::string &output, const std::string &path);
void getRandomLineFromFileIgnoringCommentsInPlace(std::string &output, const std::string &path, const std::string &comment);

void getKeyValuePairFromFileInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter);
void getRawKeyValuePairFromFileInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter);
void getKeyValuePairFromFileIgnoringCommentsInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter, const std::string &comment);

void getFileContentsInPlace(std::string &output, const std::string &path);

// File writing
bool writeKeyValuePairToFile(const std::string &path, const std::unordered_map<std::string, std::string> &map, const std::string &delimiter);
bool writeFile(const std::string &path, const std::string &contents);
bool writeFileLines(const std::string &path, const std::vector<std::string> &lines);
bool appendFile(const std::string &path, const std::string &contents);
bool appendFileLines(const std::string &path, const std::vector<std::string> &lines);

// Utility parser
struct Line {
   Line() = default;
   Line(const std::string &field, const std::string &value)
      : field(field), value(value) {}

   std::string field;
   std::string value;
};

struct Header {
   Header() = default;
   Header(const std::string &name, const std::vector<Line> &lines)
      : name(name), lines(lines) {}

   std::string name;
   std::vector<Line> lines;
};

std::vector<Header> getHeadersFromConfig(const std::string &path, const std::string &comment, const std::string &headerStart, const std::string &headerEnd, char delimiter);
int getIntValue(const std::string &value);
float getFloatValue(const std::string &value);
bool getBoolValue(const std::string &value);
std::string getStringValue(const std::string &value);
Vector2 getV2Value(const std::string &value);
Vector3 getV3Value(const std::string &value);
Vector4 getV4Value(const std::string &value);
Color getColorValue(const std::string &value);
std::vector<int> getIntArrayValue(const std::string &value);
std::vector<float> getFloatArrayValue(const std::string &value);
std::vector<bool> getBoolArrayValue(const std::string &value);
std::vector<std::string> getArrayValue(const std::string &value);
std::vector<Line> getDictionaryValue(const std::string &value, char delimiter);
