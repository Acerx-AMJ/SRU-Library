#pragma once

typedef void(*SRULibCallback)(const char *msg);
enum class SRULibLogLevel {
   all, error, none
};

void setSRULibErrorCallback(SRULibCallback callback);
void setSRULibWarningCallback(SRULibCallback callback);
void setSRULibLogLevel(SRULibLogLevel level);

void SRULibError(const char *msg);
void SRULibWarning(const char *msg);
