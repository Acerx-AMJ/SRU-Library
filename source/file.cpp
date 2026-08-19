#include "SRU/error.hpp"
#include "SRU/file.hpp"
#include "SRU/random.hpp"
#include "SRU/text.hpp"
#include "SRU/util.hpp"
#include <filesystem>
#include <fstream>

// File getter functions
std::vector<std::string> getLinesFromFile(const std::string &path, int type, const std::string &comment) {
   std::vector<std::string> lines;
   lines.reserve(32);
   getLinesFromFileInPlace(lines, path, type, comment);
   return lines;
}

std::string getRandomLineFromFile(const std::string &path, int type, const std::string &comment) {
   std::string line;
   getRandomLineFromFileInPlace(line, path, type, comment);
   return line;
}

std::unordered_map<std::string, std::string> getKeyValuePairFromFile(const std::string &path, const std::string &delimiter, int type, const std::string &comment) {
   std::unordered_map<std::string, std::string> map;
   getKeyValuePairFromFileInPlace(map, path, delimiter, type, comment);
   return map;
}

std::string getFileContents(const std::string &path) {
   std::string output;
   output.reserve(8192);
   getFileContentsInPlace(output, path);
   return output;
}

// File getter in place functions
void getLinesFromFileInPlace(std::vector<std::string> &output, const std::string &path, int type, const std::string &comment) {
   std::ifstream file (path);
   if (!file.is_open()) {
      SRULibWarning(TextFormat("srulib::getLinesFromFileInPlace/srulib::getLinesFromFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path)));
      return;
   }

   std::string line;
   while (std::getline(file, line)) {
      if (type == FILE_TRIMMED_COMMENTS && !comment.empty()) {
         if (size_t pos = line.find_first_of(comment); pos != std::string::npos) {
            line.erase(pos);
         }
      }

      if (type == FILE_RAW) {
         output.push_back(line);
      }
      else {
         trimInPlace(line);
         if (!line.empty()) {
            output.push_back(line);
         }
      }
   }
}

void getRandomLineFromFileInPlace(std::string &output, const std::string &path, int type, const std::string &comment) {
   std::ifstream file (path);
   if (!file.is_open()) {
      SRULibWarning(TextFormat("srulib::getRandomLineFromFileInPlace/srulib::getRandomLineFromFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path)));
      return;
   }
   std::string line;
   size_t count = 0;

   while (std::getline(file, line)) {
      if (type == FILE_TRIMMED_COMMENTS && !comment.empty()) {
         if (size_t pos = line.find_first_of(comment); pos != std::string::npos) {
            line.erase(pos);
         }
      }

      if (type != FILE_RAW) {
         trimInPlace(line);
         if (line.empty()) continue;
      }

      if (randomInt(0, count) == 0) {
         output = line;
      }
      count += 1;
   }
}

void getKeyValuePairFromFileInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter, int type, const std::string &comment) {
   std::ifstream file (path);
   if (!file.is_open()) {
      SRULibWarning(TextFormat("srulib::getKeyValuePairFromFileInPlace/srulib::getKeyValuePairFromFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path)));
      return;
   }

   std::string line;
   while (std::getline(file, line)) {
      if (type == FILE_TRIMMED_COMMENTS && !comment.empty()) {
         if (size_t pos = line.find_first_of(comment); pos != std::string::npos) {
            line.erase(pos);
         }
      }
      size_t pos = line.find(delimiter);

      // There's no delimiter, push line with no value
      if (pos == std::string::npos) {
         if (type == FILE_RAW) {
            output[line] = "";
         }
         else {
            trimInPlace(line);
            if (!line.empty()) {
               output[line] = "";
            }
         }
         continue;
      }

      std::string key = line.substr(0, pos);
      std::string value = line.substr(pos + delimiter.size());

      if (type == FILE_RAW) {
         output[key] = value;
      }
      else {
         trimInPlace(key);
         trimInPlace(value);

         if (!key.empty()) {
            output[key] = value;
         }
      }
   }
}

void getFileContentsInPlace(std::string &output, const std::string &path) {
   std::ifstream file (path);
   if (!file.is_open()) {
      SRULibWarning(TextFormat("srulib::getFileContentsInPlace/srulib::getFileContents: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path)));
      return;
   }
   output = {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

// File writing
bool writeKeyValuePairToFile(const std::string &path, const std::unordered_map<std::string, std::string> &map, const std::string &delimiter) {
   std::ofstream file (path);
   if (!file.is_open()) {
      SRULibWarning(TextFormat("srulib::writeKeyValuePairToFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path)));
      return false;
   }

   for (const auto &[key, value]: map) {
      file << key << delimiter << value << '\n';
   }
   return file.good();
}

bool writeFile(const std::string &path, const std::string &contents) {
   std::ofstream file (path);
   if (!file.is_open()) {
      SRULibWarning(TextFormat("srulib::writeFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path)));
      return false;
   }

   file << contents;
   return file.good();
}

bool writeFile(const std::string &path, const std::vector<std::string> &lines) {
   std::ofstream file (path);
   if (!file.is_open()) {
      SRULibWarning(TextFormat("srulib::writeFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path)));
      return false;
   }

   for (const std::string &line: lines) {
      file << line << '\n';
   }
   return file.good();
}

bool appendFile(const std::string &path, const std::string &contents) {
   std::ofstream file (path, std::ios::app);
   if (!file.is_open()) {
      SRULibWarning(TextFormat("srulib::appendFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path)));
      return false;
   }

   file << contents;
   return file.good();
}

bool appendFile(const std::string &path, const std::vector<std::string> &lines) {
   std::ofstream file (path, std::ios::app);
   if (!file.is_open()) {
      SRULibWarning(TextFormat("srulib::appendFile: Could not open file '%s'. Path exists: %d. Path is file: %d. If both are true check your permissions.\n", path.c_str(), std::filesystem::exists(path), std::filesystem::is_regular_file(path)));
      return false;
   }

   for (const std::string &line: lines) {
      file << line << '\n';
   }
   return file.good();
}

bool createDirectory(const std::string &path) {
   try {
      std::filesystem::create_directories(path);
      return true;
   }
   catch (...) {
      return false;
   }
}

bool deleteFile(const std::string &path) {
   try {
      return std::filesystem::remove_all(path) > 0;
   }
   catch (...) {
      SRULibWarning(TextFormat("srulib::deleteFile: Could not delete file '%s'. Path exists: %d. If it is true check your permissions.\n", path.c_str(), std::filesystem::exists(path)));
      return false;
   }
}

bool copyFile(const std::string &path, const std::string &destination) {
   try {
      std::filesystem::copy(path, destination, std::filesystem::copy_options::recursive | std::filesystem::copy_options::update_existing);
      return true;
   }
   catch (...) {
      SRULibWarning(TextFormat("srulib::copyFile: Could not copy file '%s' to '%s'. Path exists: %d. If it is true check your permissions.\n", path.c_str(), destination.c_str(), std::filesystem::exists(path)));
      return false;
   }
}

bool moveFile(const std::string &path, const std::string &destination) {
   try {
      std::filesystem::rename(path, destination);
      return true;
   }
   catch (...) {
      SRULibWarning(TextFormat("srulib::moveFile: Could not move file '%s' to '%s'. Path exists: %d. If it is true check your permissions.\n", path.c_str(), destination.c_str(), std::filesystem::exists(path)));
      return false;
   }
}

// File getters
bool pathExists(const std::string &path) {
   try {
      return std::filesystem::exists(path);
   }
   catch (...) {
      return false;
   }
}

bool fileExists(const std::string &path) {
   try {
      return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
   }
   catch (...) {
      return false;
   }
}

bool directoryExists(const std::string &path) {
   try {
      return std::filesystem::exists(path) && std::filesystem::is_directory(path);
   }
   catch (...) {
      return false;
   }
}

// Utility parser
std::vector<Header> getHeadersFromConfig(const std::string &path, const std::string &comment, const std::string &headerStart, const std::string &headerEnd, char delimiter) {
   std::vector<std::string> lines = getLinesFromFile(path, FILE_TRIMMED_COMMENTS, comment);
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
         SRULibWarning(TextFormat("srulib::getHeadersFromConfig: Malformed line: '%s'. Expected 'FIELD%cVALUE' or '%sNAME%s'.\n", line.c_str(), delimiter, headerStart.c_str(), headerEnd.c_str()));
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

int getIntValue(const std::string &value, bool *ok) {
   try {
      if (ok) *ok = true;
      return std::stoi(value);
   } catch (...) {
      if (ok) *ok = false;
      SRULibWarning(TextFormat("srulib::getIntValue: Expected integer, got '%s' instead. Returning default - %d.\n", value.c_str(), 0));
      return 0;
   }
}

float getFloatValue(const std::string &value, bool *ok) {
   try {
      if (ok) *ok = true;
      return std::stof(value);
   } catch (...) {
      if (ok) *ok = false;
      SRULibWarning(TextFormat("srulib::getFloatValue: Expected float, got '%s' instead. Returning default - %f.\n", value.c_str(), 0.0f));
      return 0.0f;
   }
}

bool getBoolValue(const std::string &value, bool *ok) {
   if (value != "true" && value != "false") {
      if (ok) *ok = false;
      SRULibWarning(TextFormat("srulib::getBoolValue: Expected true/false, got '%s' instead. Returning default - %s.\n", value.c_str(), "false"));
      return false;
   }
   if (ok) *ok = true;
   return value == "true";
}

std::string getStringValue(const std::string &value, bool *ok) {
   if (ok) *ok = true;
   return value;
}

Vector2 getV2Value(const std::string &value, char delimiter, bool *ok) {
   std::vector<std::string> values = getArrayValue(value, delimiter);
   if (values.size() != 2) {
      if (ok) *ok = false;
      SRULibWarning(TextFormat("srulib::getV2Value: Expected Vector2 {float,float}, got '%s' instead. Returning default - {%f, %f}.\n", value.c_str(), 0.0f, 0.0f));
      return V2();
   }
   bool ok1, ok2;
   Vector2 result = V2(getFloatValue(values[0], &ok1), getFloatValue(values[1], &ok2));
   if (ok) *ok = (ok1 && ok2);
   return result;
}

Vector3 getV3Value(const std::string &value, char delimiter, bool *ok) {
   std::vector<std::string> values = getArrayValue(value, delimiter);
   if (values.size() != 3) {
      if (ok) *ok = false;
      SRULibWarning(TextFormat("srulib::getV3Value: Expected Vector3 {float,float,float}, got '%s' instead. Returning default - {%f, %f, %f}.\n", value.c_str(), 0.0f, 0.0f, 0.0f));
      return V3();
   }
   bool ok1, ok2, ok3;
   Vector3 result = V3(getFloatValue(values[0], &ok1), getFloatValue(values[1], &ok2), getFloatValue(values[2], &ok3));
   if (ok) *ok = (ok1 && ok2 && ok3);
   return result;
}

Vector4 getV4Value(const std::string &value, char delimiter, bool *ok) {
   std::vector<std::string> values = getArrayValue(value, delimiter);
   if (values.size() != 4) {
      if (ok) *ok = false;
      SRULibWarning(TextFormat("srulib::getV4Value: Expected Vector4 {float,float,float,float}, got '%s' instead. Returning default - {%f, %f, %f, %f}.\n", value.c_str(), 0.0f, 0.0f, 0.0f, 0.0f));
      return V4();
   }
   bool ok1, ok2, ok3, ok4;
   Vector4 result = V4(getFloatValue(values[0], &ok1), getFloatValue(values[1], &ok2), getFloatValue(values[2], &ok3), getFloatValue(values[3], &ok4));
   if (ok) *ok = (ok1 && ok2 && ok3 && ok4);
   return result;
}

Color getColorValue(const std::string &value, char delimiter, bool *ok) {
   std::vector<std::string> values = getArrayValue(value, delimiter);
   if (values.size() != 4 && values.size() != 3) {
      if (ok) *ok = false;
      SRULibWarning(TextFormat("srulib::getColorValue: Expected Color {float,float,float,float?}, got '%s' instead. Returning default - {%f, %f, %f, %f}.\n", value.c_str(), 0.0f, 0.0f, 0.0f, 1.0f));
      return BLACK;
   }
   bool ok1, ok2, ok3, ok4 = true; // intended
   Color result = RGBAF(getFloatValue(values[0], &ok1), getFloatValue(values[1], &ok2), getFloatValue(values[2], &ok3), values.size() == 3 ? 1.0 : getFloatValue(values[3], &ok4));
   if (ok) *ok = (ok1 && ok2 && ok3 && ok4);
   return result;
}

std::vector<int> getIntArrayValue(const std::string &value, char delimiter, bool *ok) {
   std::vector<std::string> values = getArrayValue(value, delimiter);
   std::vector<int> intArray;
   intArray.reserve(values.size());

   if (ok) *ok = true;
   for (const std::string &value: values) {
      bool ok2;
      intArray.push_back(getIntValue(value, &ok2));
      if (ok) *ok = (*ok && ok2);
   }
   return intArray;
}

std::vector<float> getFloatArrayValue(const std::string &value, char delimiter, bool *ok) {
   std::vector<std::string> values = getArrayValue(value, delimiter);
   std::vector<float> floatArray;
   floatArray.reserve(values.size());

   if (ok) *ok = true;
   for (const std::string &value: values) {
      bool ok2;
      floatArray.push_back(getFloatValue(value, &ok2));
      if (ok) *ok = (*ok && ok2);
   }
   return floatArray;
}

std::vector<char> getBoolArrayValue(const std::string &value, char delimiter, bool *ok) {
   std::vector<std::string> values = getArrayValue(value, delimiter);
   std::vector<char> boolArray;
   boolArray.reserve(values.size());

   if (ok) *ok = true;
   for (const std::string &value: values) {
      bool ok2;
      boolArray.push_back(getBoolValue(value, &ok2));
      if (ok) *ok = (*ok && ok2);
   }
   return boolArray;
}

std::vector<std::string> getArrayValue(const std::string &value, char delimiter, bool *ok) {
   if (ok) *ok = true;
   return clean(split(value, delimiter));
}

std::vector<Line> getDictionaryValue(const std::string &value, char delimiter, char keyValueDelimiter, bool *ok) {
   std::vector<std::string> values = getArrayValue(value, delimiter);
   std::vector<Line> lines;
   lines.reserve(values.size());

   if (ok) *ok = true;
   for (const std::string &val: values) {
      size_t equals = val.find(keyValueDelimiter);
      if (equals == std::string::npos) {
         if (ok) *ok = false;
         SRULibWarning(TextFormat("srulib::getDictionaryValue: Expected dictionary, but there's no '%c' in '%s'.\n", keyValueDelimiter, val.c_str()));
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
