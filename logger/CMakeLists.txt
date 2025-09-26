
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

message("Configuring the must library of CCLogger: LoggerBasicComponents")
add_library(LoggerBasicComponents ${LoggerBasicComponentsSrc})
target_include_directories(LoggerBasicComponents PUBLIC .)
message("Configuring the must library of CCLogger: LoggerBasicComponents OK")

message("Configuring the library of CCLogger: CCLogger")
set(LoggerSrc CCLogger.cc CCLogger.hpp formater.cpp CCLogger_default_behave.cpp CCLoggerStream.cc)
add_library(CCLogger ${LoggerSrc})
target_link_libraries(CCLogger PUBLIC LoggerBasicComponents CCXXThreadPool)
message("Configuring the library of CCLogger: CCLogger OK")

