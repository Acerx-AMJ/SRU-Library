#pragma once
#include "SRU/constants.hpp"
#include "raylib.h"
#include <string>
#include <unordered_map>
#include <vector>

// File getter functions
std::vector<std::string> getLinesFromFile(const std::string &path, int type = FILE_TRIMMED, const std::string &comment = "");
std::string getRandomLineFromFile(const std::string &path, int type = FILE_TRIMMED, const std::string &comment = "");
std::unordered_map<std::string, std::string> getKeyValuePairFromFile(const std::string &path, const std::string &delimiter = "=", int type = FILE_TRIMMED, const std::string &comment = "");
std::string getFileContents(const std::string &path);

// File getter in place functions
void getLinesFromFileInPlace(std::vector<std::string> &output, const std::string &path, int type = FILE_TRIMMED, const std::string &comment = "");
void getRandomLineFromFileInPlace(std::string &output, const std::string &path, int type = FILE_TRIMMED, const std::string &comment = "");
void getKeyValuePairFromFileInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter = "=", int type = FILE_TRIMMED, const std::string &comment = "");
void getFileContentsInPlace(std::string &output, const std::string &path);

// File editing
bool writeKeyValuePairToFile(const std::string &path, const std::unordered_map<std::string, std::string> &map, const std::string &delimiter = "=");
bool writeFile(const std::string &path, const std::string &contents);
bool writeFile(const std::string &path, const std::vector<std::string> &lines);
bool appendFile(const std::string &path, const std::string &contents);
bool appendFile(const std::string &path, const std::vector<std::string> &lines);

bool createDirectory(const std::string &path);
bool deleteFile(const std::string &path);
bool copyFile(const std::string &path, const std::string &destination);
bool moveFile(const std::string &path, const std::string &destination);

// File getters
bool pathExists(const std::string &path);
bool fileExists(const std::string &path);
bool directoryExists(const std::string &path);

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

std::vector<Header> getHeadersFromConfig(const std::string &path, const std::string &comment = "#", const std::string &headerStart = "[", const std::string &headerEnd = "]", char delimiter = '=');

int getIntValue(const std::string &value, bool *ok = nullptr);
float getFloatValue(const std::string &value, bool *ok = nullptr);
bool getBoolValue(const std::string &value, bool *ok = nullptr);
std::string getStringValue(const std::string &value, bool *ok = nullptr);
Vector2 getV2Value(const std::string &value, char delimiter = ',', bool *ok = nullptr);
Vector3 getV3Value(const std::string &value, char delimiter = ',', bool *ok = nullptr);
Vector4 getV4Value(const std::string &value, char delimiter = ',', bool *ok = nullptr);
Color getColorValue(const std::string &value, char delimiter = ',', bool *ok = nullptr);
std::vector<int> getIntArrayValue(const std::string &value, char delimiter = ',', bool *ok = nullptr);
std::vector<float> getFloatArrayValue(const std::string &value, char delimiter = ',', bool *ok = nullptr);
std::vector<char> getBoolArrayValue(const std::string &value, char delimiter = ',', bool *ok = nullptr);
std::vector<std::string> getArrayValue(const std::string &value, char delimiter = ',', bool *ok = nullptr);
std::vector<Line> getDictionaryValue(const std::string &value, char delimiter = ',', char keyValueDelimiter = '=', bool *ok = nullptr);
