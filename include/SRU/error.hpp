#pragma once

typedef void(*SRULibCallback)(const char *msg);
enum SRULibLogLevel {
   SRULIB_LOG_LEVEL_ALL, SRULIB_LOG_LEVEL_ERROR, SRULIB_LOG_LEVEL_NONE
};

void setSRULibErrorCallback(SRULibCallback callback);
void setSRULibWarningCallback(SRULibCallback callback);
void setSRULibLogLevel(SRULibLogLevel level);

void SRULibError(const char *msg, ...);
void SRULibWarning(const char *msg, ...);
