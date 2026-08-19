#include "SRU/error.hpp"
#include <stdio.h>
#include <stdlib.h>

static SRULibLogLevel level = SRULibLogLevel::all;
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

void SRULibError(const char *msg) {
   if (level != SRULibLogLevel::none) {
      errorCallback(msg);
   }
}

void SRULibWarning(const char *msg) {
   if (level != SRULibLogLevel::error && level != SRULibLogLevel::none) {
      warningCallback(msg);
   }
}
