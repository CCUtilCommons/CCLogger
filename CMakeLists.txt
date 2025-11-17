cmake_minimum_required(VERSION 3.25)
project(CCLogger LANGUAGES CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    CCThreadPool
    GIT_REPOSITORY https://github.com/CCUtilCommons/CCThreadPool.git
    GIT_TAG main
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/middlewares
)

option(USE_STANDARD_FORMATTER "Use Standard Formatter" ON)
message("Requesting All static library -fPIC...")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
message("==================== Get the Third Party Middlewares ====================")
FetchContent_MakeAvailable(CCThreadPool)
message("==================== Get the Third Party Middlewares End ====================")

message("==================== Configuring the Logger Basic Components ====================")
add_subdirectory(logger)
message("==================== Configuring the Logger Basic Components End ====================")

message("==================== Configuring the Example ====================")
add_subdirectory(example)
message("==================== Configuring the Example End ====================")

message("==================== Configuring the Test ====================")
add_subdirectory(test)
message("==================== Configuring the Test End ====================")



