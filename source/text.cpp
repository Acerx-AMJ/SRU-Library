#include "SRU/text.hpp"
#include <algorithm>
#include <iterator>
#include <sstream>

std::string wrap(const std::string &string, Font font, float maxWidth, float fontSize, float spacing) {
   std::string wrappedString = string;
   wrapInPlace(wrappedString, font, maxWidth, fontSize, spacing);
   return wrappedString;
}

std::string truncate(const std::string &string, Font font, float maxWidth, float fontSize, float spacing) {
   std::string truncatedString = string;
   truncateInPlace(truncatedString, font, maxWidth, fontSize, spacing);
   return truncatedString;
}

std::string fitInside(const std::string &string, Font font, Vector2 maxSize, float fontSize, float spacing) {
   std::string fittedString = string;
   fitInsideInPlace(fittedString, font, maxSize, fontSize, spacing);
   return fittedString;
}

std::string toRomanNumeral(size_t number) {
   std::string numeral;
   numeral.reserve(5);
   toRomanNumeralInPlace(numeral, number);
   return numeral;
}

std::string toUpper(const std::string &string) {
   std::string upperString = string;
   toUpperInPlace(upperString);
   return upperString;
}

std::string toLower(const std::string &string) {
   std::string lowerString = string;
   toLowerInPlace(lowerString);
   return lowerString;
}

std::string trim(const std::string &string) {
   std::string trimmedString = string;
   trimInPlace(trimmedString);
   return trimmedString;
}

std::string trimLeft(const std::string &string) {
   std::string trimmedString = string;
   trimLeftInPlace(trimmedString);
   return trimmedString;
}

std::string trimRight(const std::string &string) {
   std::string trimmedString = string;
   trimRightInPlace(trimmedString);
   return trimmedString;
}

std::vector<std::string> split(const std::string &string, char delimiter) {
   std::vector<std::string> pieces;
   splitInPlace(pieces, string, delimiter);
   return pieces;
}

std::vector<std::string> split(const std::string &string, const std::string &delimiter) {
   std::vector<std::string> pieces;
   splitInPlace(pieces, string, delimiter);
   return pieces;
}

std::vector<std::string> splitOnWhiteSpace(const std::string &string) {
   std::vector<std::string> pieces;
   splitOnWhiteSpaceInPlace(pieces, string);
   return pieces;
}

std::string join(const std::vector<std::string> &parts, const std::string &delimiter) {
   std::string joinedString;
   joinInPlace(joinedString, parts, delimiter);
   return joinedString;
}

std::string join(const std::vector<std::string> &parts) {
   std::string joinedString;
   joinInPlace(joinedString, parts);
   return joinedString;
}

void wrapInPlace(std::string &string, Font font, float maxWidth, float fontSize, float spacing) {
   auto shouldWrap = [font, maxWidth, fontSize, spacing](const std::string &s) -> bool {
      return MeasureTextEx(font, s.c_str(), fontSize, spacing).x > maxWidth;
   };

   if (string.empty() || !shouldWrap(string)) {
      return;
   }

   std::string original = string;
   std::string_view split = original; // string cannot be viewed because it gets changed
   string.clear();

   while (!split.empty()) {
      std::string current (split);
      if (!shouldWrap(current)) {
         string += split;
         break;
      }

      size_t left = 0;
      size_t right = split.size();

      while (left < right) {
         size_t mid = (left + right) / 2;
         std::string temp = std::string(split.substr(0, mid)) + "-";

         if (shouldWrap(temp)) {
            right = mid;
         } else {
            left = mid + 1;
         }
      }

      size_t cut = left > 0 ? left - 1 : 0;
      bool punctuation = (cut < split.size() && std::ispunct(split[cut]));
      if (punctuation) cut += 1;

      std::string_view truncated = split.substr(0, cut);
      std::string_view remainder = split.substr(cut);

      if (!remainder.empty() && std::isspace(remainder.front())) {
         remainder = remainder.substr(1);
      }

      bool dash = !truncated.empty() && !remainder.empty() && std::isalpha(truncated.back()) && std::isalpha(split.front());
      string += truncated;
      string += (dash ? "-\n" : "\n");
      split = remainder;
   }
}

void truncateInPlace(std::string &string, Font font, float maxWidth, float fontSize, float spacing) {
   auto shouldTruncate = [font, maxWidth, fontSize, spacing](const std::string &s) -> bool {
      return MeasureTextEx(font, s.c_str(), fontSize, spacing).x > maxWidth;
   };

   if (string.empty() || !shouldTruncate(string)) {
      return;
   }
   else if (shouldTruncate("...")) {
      string = "...";
      return;
   }

   std::string original = string;
   std::string_view split = original; // string cannot be viewed because it gets changed
   string.clear();

   size_t left = 0;
   size_t right = split.size();

   while (left < right) {
      size_t mid = (left + right) / 2;
      string = split.substr(0, mid);

      if (shouldTruncate(string + "...")) {
         right = mid;
      } else {
         left = mid + 1;
      }
   }

   string = split.substr(0, left - 1);
   string += "...";
}

void fitInsideInPlace(std::string &string, Font font, Vector2 maxSize, float fontSize, float spacing) {
   auto shouldWrap = [font, maxSize, fontSize, spacing](const std::string &s) -> bool {
      return MeasureTextEx(font, s.c_str(), fontSize, spacing).x > maxSize.x;
   };
   auto shouldTruncate = [font, maxSize, fontSize, spacing](const std::string &s) -> bool {
      return MeasureTextEx(font, s.c_str(), fontSize, spacing).y > maxSize.y;
   };

   if (string.empty() || (!shouldWrap(string) && !shouldTruncate(string))) {
      return;
   }
   else if (maxSize.x <= 3 * MeasureTextEx(font, "-", fontSize, spacing).x) {
      string = "...";
      return;
   }
   else if (shouldTruncate(string) && !shouldWrap(string)) {
      truncateInPlace(string, font, maxSize.x, fontSize, spacing);
      return;
   }

   std::string original = string;
   std::string_view split = original;
   string.clear();

   while (!split.empty()) {
      if (!shouldWrap(std::string(split))) {
         std::string candidate = string + std::string(split);

         if (shouldTruncate(candidate)) {
            std::string finalLine(split);
            truncateInPlace(finalLine, font, maxSize.x, fontSize, spacing);
            string += finalLine;
         } else {
            string = candidate;
         }
         break;
      }

      size_t left = 0;
      size_t right = split.size();

      while (left < right) {
         size_t mid = (left + right) / 2;
         std::string temp = std::string(split.substr(0, mid)) + "-";

         if (shouldWrap(temp)) {
            right = mid;
         } else {
            left = mid + 1;
         }
      }
      size_t cut = left > 0 ? left - 1 : 0;
      bool punctuation = (cut < split.size() && std::ispunct(static_cast<unsigned char>(split[cut])));
      if (punctuation) cut += 1;

      std::string_view truncated = split.substr(0, cut);
      std::string_view remainder = split.substr(cut);
      if (!remainder.empty() && std::isspace(static_cast<unsigned char>(remainder.front()))) {
         remainder = remainder.substr(1);
      }

      bool dash = !truncated.empty() && !remainder.empty() && std::isalpha(truncated.back()) && std::isalpha(split.front());
      std::string line = std::string(truncated) + (dash ? "-" : "");
      std::string candidate = string + line + "\n";

      if (shouldTruncate(candidate)) {
         std::string finalLine = std::string(truncated) + std::string(remainder);
         truncateInPlace(finalLine, font, maxSize.x, fontSize, spacing);
         string += finalLine;
         break;
      }

      string = candidate;
      split = remainder;
   }
}

void toRomanNumeralInPlace(std::string &string, size_t number) {
   // from http://rosettacode.org/wiki/Roman_numerals/Encode#C.2B.2B
   struct romandata_t {
      size_t value;
      char const *numeral;
   };

   static constexpr romandata_t romandata[] {
      {1000, "M"}, {900, "CM"},
      { 500, "D"}, {400, "CD"},
      { 100, "C"}, { 90, "XC"},
      {  50, "L"}, { 40, "XL"},
      {  10, "X"}, {  9, "IX"},
      {   5, "V"}, {  4, "IV"},
      {   1, "I"}, {  0, ""}
   };

   for (const romandata_t *current = romandata; current->value > 0; current += 1) {
      while (number >= current->value) {
         string += current->numeral;
         number -= current->value;
      }
   }
}

void toUpperInPlace(std::string &string) {
   std::transform(string.begin(), string.end(), string.begin(), ::toupper);
}

void toLowerInPlace(std::string &string) {
   std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}

void trimInPlace(std::string &string) {
   trimLeftInPlace(string);
   trimRightInPlace(string);
}

void trimLeftInPlace(std::string &string) {
   string.erase(0, string.find_first_not_of(" \n\r\t\v\f"));
}

void trimRightInPlace(std::string &string) {
   string.erase(string.find_last_not_of(" \n\r\t\v\f") + 1);
}

void splitInPlace(std::vector<std::string> &output, const std::string &string, char delimiter) {
   size_t delimiterCount = std::count(string.begin(), string.end(), delimiter);
   output.reserve(output.size() + delimiterCount + 1);

   std::stringstream stream (string);
   std::string piece;

   while (std::getline(stream, piece, delimiter)) {
      output.push_back(piece);
   }

   if (string.back() == delimiter) {
      output.push_back("");
   }
}

void splitInPlace(std::vector<std::string> &output, const std::string &string, const std::string &delimiter) {
   size_t delimiterCount = 0;
   for (size_t offset = string.find(delimiter); offset != std::string::npos; offset = string.find(delimiter, offset + delimiter.length())) {
      delimiterCount += 1;
   }
   output.reserve(output.size() + delimiterCount + 1);

   size_t last = 0;
   for (size_t pos = string.find(delimiter); pos != std::string::npos; pos = string.find(delimiter, last)) {
      output.emplace_back(string.begin() + last, string.begin() + pos);
      last = pos + delimiter.size();
   }
   
   if (last != string.size()) {
      output.emplace_back(string.begin() + last, string.end());
   }
   else {
      output.push_back("");
   }
}

void splitOnWhiteSpaceInPlace(std::vector<std::string> &output, const std::string &string) {
   std::string input = string;
   trimInPlace(input);

   std::stringstream stream (input);
   size_t delimiterCount = std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
   output.reserve(output.size() + delimiterCount + 1);
   stream.clear();
   stream.str(input);

   std::string piece;
   while (stream >> piece) {
      output.push_back(piece);
   }
}

void joinInPlace(std::string &output, const std::vector<std::string> &parts, const std::string &delimiter) {
   size_t size = delimiter.size() * (parts.empty() ? 0 : parts.size() - 1);
   for (const std::string &string: parts) {
      size += string.size();
   }
   output.reserve(size);

   for (size_t i = 0; i < parts.size(); ++i) {
      output += parts[i];
      if (i + 1 < parts.size()) {
         output += delimiter;
      }
   }
}

void joinInPlace(std::string &output, const std::vector<std::string> &parts) {
   size_t size = 0;
   for (const std::string &string: parts) {
      size += string.size();
   }
   output.reserve(size);

   for (const std::string &string: parts) {
      output += string;   
   }
}

float fitFontSize(const char *string, Font font, float maxWidth, float spacing) {
   float low = 1.0f;
   float high = maxWidth;
   float best = 1.0f;

   while (high - low > 0.1f) {
      float mid = (low + high) / 2.0f;
      float width = MeasureTextEx(font, string, mid, spacing).x;

      if (width <= maxWidth) {
         best = mid;
         low = mid;
      } else {
         high = mid;
      }
   }
   return best;
}

float fitFontSize(const std::string &string, Font font, float maxWidth, float spacing) {
   return fitFontSize(string.c_str(), font, maxWidth, spacing);
}
