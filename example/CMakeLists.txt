
add_executable(example example.cc)
target_link_libraries(example PRIVATE CCLogger)

add_executable(example_multi_backend example_multi_backend.cc)
target_link_libraries(example_multi_backend PRIVATE CCLogger)

add_executable(example_stream example_stream.cc)
target_link_libraries(example_stream PRIVATE CCLogger)
