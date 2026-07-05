#pragma once
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
