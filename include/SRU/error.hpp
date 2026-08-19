#pragma once

enum class SRULibLogLevel {
   all, error, none
};

using SRULibCallback = void(*)(const char *msg);
void setSRULibErrorCallback(SRULibCallback callback);
void setSRULibWarningCallback(SRULibCallback callback);
void setSRULibLogLevel(SRULibLogLevel level);

void SRULibError(const char *msg);
void SRULibWarning(const char *msg);
