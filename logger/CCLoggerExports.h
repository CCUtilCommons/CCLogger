#pragma once

// Detect Windows
#if defined(_WIN32) || defined(_WIN64)
#define CCLOG_PLATFORM_WINDOWS
#endif

#if defined(CCLOG_PLATFORM_WINDOWS)
#if defined(CCLOG_BUILD_SHARED)
#define CCLOG_API __declspec(dllexport)
#else
#define CCLOG_API __declspec(dllimport)
#endif
#else
// GCC/Clang: use visibility attributes
#if defined(CCLOG_BUILD_SHARED)
#define CCLOG_API __attribute__((visibility("default")))
#else
#define CCLOG_API
#endif
#endif
