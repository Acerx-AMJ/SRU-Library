#include "SRU/text.hpp"
#include <algorithm>

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
   std::transform(string.begin(), string.end(), string.begin(), ::toupper);
}

void trimInPlace(std::string &string) {
   trimLeftInPlace(string);
   trimRightInPlace(string);
}

void trimLeftInPlace(std::string &string) {
   string.erase(0, string.find_first_not_of(" \n\r\t\v\f"));
}

void trimRightInPlace(std::string &string) {
   string.erase(string.find_last_not_of(" \n\r\t\v\f"));
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
