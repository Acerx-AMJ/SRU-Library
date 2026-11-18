#include "SRU/error.hpp"
#include <cstdarg>
#include <stdio.h>
#include <stdlib.h>

static SRULibLogLevel level = SRULIB_LOG_LEVEL_ALL;
static SRULibCallback errorCallback = [](const char *msg) {
   printf("%s", msg);
   exit(EXIT_FAILURE);
};
static SRULibCallback warningCallback = [](const char *msg) {
   printf("%s", msg);
};

void setSRULibErrorCallback(SRULibCallback callback) {
   errorCallback = callback;
}

void setSRULibWarningCallback(SRULibCallback callback) {
   warningCallback = callback;
}

void setSRULibLogLevel(SRULibLogLevel newLevel) {
   level = newLevel;
}

void SRULibError(const char *msg, ...) {
   if (level != SRULIB_LOG_LEVEL_NONE) {
      va_list args, copy;
      va_start(args, msg);
      va_copy(copy, args);
      int len = vsnprintf(nullptr, 0, msg, copy) + 1; // null-terminator
      va_end(copy);
      char *message = (char*)malloc(len);
      vsnprintf(message, len, msg, args);
      va_end(args);

      errorCallback(message);
      free(message);
   }
}

void SRULibWarning(const char *msg, ...) {
   if (level != SRULIB_LOG_LEVEL_ERROR && level != SRULIB_LOG_LEVEL_NONE) {
      va_list args, copy;
      va_start(args, msg);
      va_copy(copy, args);
      int len = vsnprintf(nullptr, 0, msg, copy) + 1; // null-terminator
      va_end(copy);
      char *message = (char*)malloc(len);
      vsnprintf(message, len, msg, args);
      va_end(args);

      warningCallback(message);
      free(message);
   }
}
