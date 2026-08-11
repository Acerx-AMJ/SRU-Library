#include "SRU/file.hpp"
#include "SRU/random.hpp"
#include "SRU/text.hpp"
#include "SRU/util.hpp"
#include <filesystem>
#include <fstream>

// File getter functions
std::vector<std::string> getLinesFromFile(const std::string &path) {
   std::vector<std::string> lines;
   lines.reserve(32);
   getLinesFromFileInPlace(lines, path);
   return lines;
}

std::vector<std::string> getRawLinesFromFile(const std::string &path) {
   std::vector<std::string> lines;
   lines.reserve(32);
   getRawLinesFromFileInPlace(lines, path);
   return lines;
}

std::vector<std::string> getLinesFromFileIgnoringComments(const std::string &path, const std::string &comment) {
   std::vector<std::string> lines;
   lines.reserve(32);
   getLinesFromFileIgnoringCommentsInPlace(lines, path, comment);
   return lines;
}

std::string getRandomLineFromFile(const std::string &path) {
   std::vector<std::string> lines = getLinesFromFile(path);
   return randomElement(lines);
}

std::string getRandomRawLineFromFile(const std::string &path) {
   std::vector<std::string> lines = getRawLinesFromFile(path);
   return randomElement(lines);
}

std::string getRandomLineFromFileIgnoringComments(const std::string &path, const std::string &comment) {
   std::vector<std::string> lines = getLinesFromFileIgnoringComments(path, comment);
   return randomElement(lines);
}

std::unordered_map<std::string, std::string> getKeyValuePairFromFile(const std::string &path, const std::string &delimiter) {
   std::unordered_map<std::string, std::string> map;
   getKeyValuePairFromFileInPlace(map, path, delimiter);
   return map;
}

std::unordered_map<std::string, std::string> getRawKeyValuePairFromFile(const std::string &path, const std::string &delimiter) {
   std::unordered_map<std::string, std::string> map;
   getRawKeyValuePairFromFileInPlace(map, path, delimiter);
   return map;
}

std::unordered_map<std::string, std::string> getKeyValuePairFromFileIgnoringComments(const std::string &path, const std::string &delimiter, const std::string &comment) {
   std::unordered_map<std::string, std::string> map;
   getKeyValuePairFromFileIgnoringCommentsInPlace(map, path, delimiter, comment);
   return map;
}

std::string getFileContents(const std::string &path) {
   std::string output;
   output.reserve(8192);
   getFileContentsInPlace(output, path);
   return output;
}

// File getter in place functions
void getLinesFromFileInPlace(std::vector<std::string> &output, const std::string &path) {
   std::fstream file (path);
   if (!file.is_open()) {
      printf("srulib::getLinesFromFileInPlace/srulib::getLinesFromFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return;
   }

   std::string line;
   while (std::getline(file, line)) {
      trimInPlace(line);
      if (!line.empty()) {
         output.push_back(line);
      }
   }
}

void getRawLinesFromFileInPlace(std::vector<std::string> &output, const std::string &path) {
   std::fstream file (path);
   if (!file.is_open()) {
      printf("srulib::getRawLinesFromFileInPlace/srulib::getRawLinesFromFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return;
   }

   std::string line;
   while (std::getline(file, line)) {
      output.push_back(line);
   }
}

void getLinesFromFileIgnoringCommentsInPlace(std::vector<std::string> &output, const std::string &path, const std::string &comment) {
   std::fstream file (path);
   if (!file.is_open()) {
      printf("srulib::getLinesFromFileIgnoringCommentsInPlace/srulib::getLinesFromFileIgnoringComments: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return;
   }

   std::string line;
   while (std::getline(file, line)) {
      if (size_t pos = line.find_first_of(comment); pos != std::string::npos) {
         line.erase(pos);
      }
      trimInPlace(line);

      if (!line.empty()) {
         output.push_back(line);
      }
   }
}

void getRandomLineFromFileInPlace(std::string &output, const std::string &path) {
   std::vector<std::string> lines = getLinesFromFile(path);
   output = randomElement(lines);
}

void getRandomRawLineFromFileInPlace(std::string &output, const std::string &path) {
   std::vector<std::string> lines = getRawLinesFromFile(path);
   output = randomElement(lines);
}

void getRandomLineFromFileIgnoringCommentsInPlace(std::string &output, const std::string &path, const std::string &comment) {
   std::vector<std::string> lines = getLinesFromFileIgnoringComments(path, comment);
   output = randomElement(lines);
}

void getKeyValuePairFromFileInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter) {
   std::fstream file (path);
   if (!file.is_open()) {
      printf("srulib::getKeyValuePairFromFileInPlace/srulib::getKeyValuePairFromFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return;
   }

   std::string line;
   while (std::getline(file, line)) {
      size_t pos = line.find(delimiter);

      // There's no delimiter, treat it as a C macro and push line with no value
      if (pos == std::string::npos) {
         trimInPlace(line);
         if (!line.empty()) {
            output[line] = "";
         }
         continue;
      }

      std::string key = line.substr(0, pos);
      std::string value = line.substr(pos + delimiter.size());

      trimInPlace(key);
      trimInPlace(value);

      if (!key.empty()) {
         output[key] = value;
      }
   }
}

void getRawKeyValuePairFromFileInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter) {
   std::fstream file (path);
   if (!file.is_open()) {
      printf("srulib::getRawKeyValuePairFromFileInPlace/srulib::getRawKeyValuePairFromFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return;
   }

   std::string line;
   while (std::getline(file, line)) {
      size_t pos = line.find(delimiter);

      // There's no delimiter, treat it as a C macro and push line with no value
      if (pos == std::string::npos) {
         output[line] = "";
         continue;
      }

      std::string key = line.substr(0, pos);
      std::string value = line.substr(pos + delimiter.size());
      output[key] = value;
   }
}

void getKeyValuePairFromFileIgnoringCommentsInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter, const std::string &comment) {
   std::fstream file (path);
   if (!file.is_open()) {
      printf("srulib::getKeyValuePairFromFileIgnoringCommentsInPlace/srulib::getKeyValuePairFromFileIgnoringComments: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return;
   }

   std::string line;
   while (std::getline(file, line)) {
      if (size_t pos = line.find(comment); pos != std::string::npos) {
         line.erase(pos);
      }
      size_t pos = line.find(delimiter);

      // There's no delimiter, treat it as a C macro and push line with no value
      if (pos == std::string::npos) {
         trimInPlace(line);
         if (!line.empty()) {
            output[line] = "";
         }
         continue;
      }

      std::string key = line.substr(0, pos);
      std::string value = line.substr(pos + delimiter.size());

      trimInPlace(key);
      trimInPlace(value);

      if (!key.empty()) {
         output[key] = value;
      }
   }
}

void getFileContentsInPlace(std::string &output, const std::string &path) {
   std::fstream file (path);
   if (!file.is_open()) {
      printf("srulib::getFileContentsInPlace/srulib::getFileContents: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return;
   }

   std::string line;
   while (std::getline(file, line)) {
      output += line;
      output += '\n';
   }
}

// File writing
bool writeKeyValuePairToFile(const std::string &path, const std::unordered_map<std::string, std::string> &map, const std::string &delimiter) {
   std::ofstream file (path);
   if (!file.is_open()) {
      printf("srulib::writeKeyValuePairToFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return false;
   }

   for (const auto &[key, value]: map) {
      file << key << delimiter << value << '\n';
   }
   return true;
}

bool writeFile(const std::string &path, const std::string &contents) {
   std::ofstream file (path);
   if (!file.is_open()) {
      printf("srulib::writeFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return false;
   }

   file << contents;
   return true;
}

bool writeFileLines(const std::string &path, const std::vector<std::string> &lines) {
   std::ofstream file (path);
   if (!file.is_open()) {
      printf("srulib::writeFileLines: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return false;
   }

   for (const std::string &line: lines) {
      file << line;
   }
   return true;
}

bool appendFile(const std::string &path, const std::string &contents) {
   std::ofstream file (path, std::ios::app);
   if (!file.is_open()) {
      printf("srulib::appendFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return false;
   }

   file << contents;
   return true;
}

bool appendFileLines(const std::string &path, const std::vector<std::string> &lines) {
   std::ofstream file (path, std::ios::app);
   if (!file.is_open()) {
      printf("srulib::appendFileLines: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path));
      return false;
   }

   for (const std::string &line: lines) {
      file << line;
   }
   return true;
}

// Utility parser
std::vector<Header> getHeadersFromConfig(const std::string &path, const std::string &comment, const std::string &headerStart, const std::string &headerEnd, char delimiter) {
   std::vector<std::string> lines = getLinesFromFileIgnoringComments(path, comment);
   std::vector<Header> headers;
   headers.reserve(lines.size() / 8);

   Header header;
   bool initialized = false;
   
   for (const std::string &line: lines) {
      size_t start = line.find(headerStart);
      size_t end = line.find(headerEnd);

      if ((headerStart.empty() || start == 0) && (headerEnd.empty() || end == line.size() - headerEnd.size())) {
         if (initialized) {
            headers.push_back(header);
            header = {};
         }

         size_t nameStart = start + headerStart.size();
         header.name = line.substr(nameStart, end - nameStart);
         initialized = true;
         continue;
      }

      size_t delim = line.find(delimiter);
      if (delim == std::string::npos) {
         printf("srulib::getHeadersFromConfig: Malformed line: '%s'. Expected 'FIELD%cVALUE' or '%sNAME%s'.\n", line.c_str(), delimiter, headerStart.c_str(), headerEnd.c_str());
         continue;
      }
      std::string field = line.substr(0, delim);
      std::string value = line.substr(delim + 1);
      trimRightInPlace(field);
      trimLeftInPlace(value);
      header.lines.emplace_back(field, value);
   }

   if (initialized) {
      headers.push_back(header);
   }
   return headers;
}

int getIntValue(const std::string &value) {
   try {
      return std::stoi(value);
   } catch (...) {
      printf("srulib::getIntValue: Expected integer, got '%s' instead. Returning default - %d.\n", value.c_str(), 0);
      return 0;
   }
}

float getFloatValue(const std::string &value) {
   try {
      return std::stof(value);
   } catch (...) {
      printf("srulib::getFloatValue: Expected float, got '%s' instead. Returning default - %f.\n", value.c_str(), 0.0f);
      return 0.0f;
   }
}

bool getBoolValue(const std::string &value) {
   if (value != "true" && value != "false") {
      printf("srulib::getBoolValue: Expected true/false, got '%s' instead. Returning default - %s.\n", value.c_str(), "false");
      return false;
   }
   return value == "true";
}

std::string getStringValue(const std::string &value) {
   return value;
}

Vector2 getV2Value(const std::string &value) {
   std::vector<std::string> values = getArrayValue(value);
   if (values.size() != 2) {
      printf("srulib::getV2Value: Expected Vector2 {float,float}, got '%s' instead. Returning default - {%f, %f}.\n", value.c_str(), 0.0f, 0.0f);
      return V2();
   }
   return V2(getFloatValue(values[0]), getFloatValue(values[1]));
}

Vector3 getV3Value(const std::string &value) {
   std::vector<std::string> values = getArrayValue(value);
   if (values.size() != 3) {
      printf("srulib::getV3Value: Expected Vector3 {float,float,float}, got '%s' instead. Returning default - {%f, %f, %f}.\n", value.c_str(), 0.0f, 0.0f, 0.0f);
      return V3();
   }
   return V3(getFloatValue(values[0]), getFloatValue(values[1]), getFloatValue(values[2]));
}

Vector4 getV4Value(const std::string &value) {
   std::vector<std::string> values = getArrayValue(value);
   if (values.size() != 4) {
      printf("srulib::getV4Value: Expected Vector4 {float,float,float,float}, got '%s' instead. Returning default - {%f, %f, %f, %f}.\n", value.c_str(), 0.0f, 0.0f, 0.0f, 0.0f);
      return V4();
   }
   return V4(getFloatValue(values[0]), getFloatValue(values[1]), getFloatValue(values[2]), getFloatValue(values[3]));
}

Color getColorValue(const std::string &value) {
   std::vector<std::string> values = getArrayValue(value);
   if (values.size() != 4 && values.size() != 3) {
      printf("srulib::getColorValue: Expected Color {float,float,float,float?}, got '%s' instead. Returning default - {%f, %f, %f, %f}.\n", value.c_str(), 0.0f, 0.0f, 0.0f, 1.0f);
      return BLACK;
   }
   return RGBAF(getFloatValue(values[0]), getFloatValue(values[1]), getFloatValue(values[2]), values.size() == 3 ? 1.0 : getFloatValue(values[3]));
}

std::vector<int> getIntArrayValue(const std::string &value) {
   std::vector<std::string> values = getArrayValue(value);
   std::vector<int> intArray;
   intArray.reserve(values.size());

   for (const std::string &value: values) {
      intArray.push_back(getIntValue(value));
   }
   return intArray;
}

std::vector<float> getFloatArrayValue(const std::string &value) {
   std::vector<std::string> values = getArrayValue(value);
   std::vector<float> floatArray;
   floatArray.reserve(values.size());

   for (const std::string &value: values) {
      floatArray.push_back(getFloatValue(value));
   }
   return floatArray;
}

std::vector<bool> getBoolArrayValue(const std::string &value) {
   std::vector<std::string> values = getArrayValue(value);
   std::vector<bool> boolArray;
   boolArray.reserve(values.size());

   for (const std::string &value: values) {
      boolArray.push_back(getBoolValue(value));
   }
   return boolArray;
}

std::vector<std::string> getArrayValue(const std::string &value) {
   return clean(split(value, ','));
}

std::vector<Line> getDictionaryValue(const std::string &value, char delimiter) {
   std::vector<std::string> values = getArrayValue(value);
   std::vector<Line> lines;
   lines.reserve(values.size());

   for (const std::string &val: values) {
      size_t equals = val.find(delimiter);
      if (equals == std::string::npos) {
         printf("srulib::getDictionaryValue: Expected dictionary, but there's no '%c' in '%s'.\n", delimiter, val.c_str());
         continue;
      }

      std::string field = val.substr(0, equals);
      std::string value = val.substr(equals + 1);
      trimRightInPlace(field);
      trimLeftInPlace(value);
      lines.emplace_back(field, value);
   }
   return lines;
}
