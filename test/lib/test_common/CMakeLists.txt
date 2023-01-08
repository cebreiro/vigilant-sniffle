add_executable(test_common)

find_package(GTest CONFIG REQUIRED)

target_link_libraries(test_common PRIVATE 
common
GTest::gtest
GTest::gtest_main
)

target_precompile_headers(test_common PRIVATE
<cstdint>
)

target_sources(test_common PRIVATE
main.cpp
test_snowflake.cpp
test_stream_reader.cpp
test_stream_writer.cpp 
test_string_util.cpp
)

add_subdirectory(execution)