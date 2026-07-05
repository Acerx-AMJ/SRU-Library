#include "SRU/file.hpp"
#include "SRU/random.hpp"
#include "SRU/text.hpp"
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
