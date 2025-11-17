#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef CCLOG_BUILD_SHARED
// Building CCLogger as a DLL
#define CCLOG_API __declspec(dllexport)
#elif defined(CCLOG_USE_SHARED)
// Using CCLogger DLL
#define CCLOG_API __declspec(dllimport)
#else
// Static library or no DLL
#define CCLOG_API
#endif
#else
// Linux/macOS
#ifdef CCLOG_BUILD_SHARED
#define CCLOG_API __attribute__((visibility("default")))
#else
#define CCLOG_API
#endif
#endif
