
# Collect all sources in formatter and io
message("Collecting the sources in logger/io and logger/formatter")

if(USE_STANDARD_FORMATTER)
    add_definitions(-DUSE_STANDARD_FORMATTER)
endif()

file(GLOB_RECURSE LoggerBasicComponentsSrc
    "${CMAKE_CURRENT_SOURCE_DIR}/io/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/io/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/formater/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/formater/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/decorator/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/decorator/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.hpp"
)

message("Requesting All static library -fPIC...")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
message("Configuring the must library of CCLogger: LoggerBasicComponents")
add_library(LoggerBasicComponents ${LoggerBasicComponentsSrc})
target_include_directories(LoggerBasicComponents PUBLIC .)
message("Configuring the must library of CCLogger: LoggerBasicComponents OK")

message("Configuring the library of CCLogger: CCLogger")
set(LoggerSrc CCLogger.cc CCLogger.hpp formater.cpp CCLogger_default_behave.cpp)
add_library(CCLogger SHARED ${LoggerSrc})
target_link_libraries(CCLogger PUBLIC LoggerBasicComponents CCXXThreadPool)
message("Configuring the library of CCLogger: CCLogger OK")

# EXPORT macro: export when building
target_compile_definitions(CCLogger PRIVATE CCLOG_BUILD_SHARED)

# Optional: hide all symbols except CCLOG_API
if(NOT WIN32)
    target_compile_options(CCLogger PRIVATE "-fvisibility=hidden")
endif()

