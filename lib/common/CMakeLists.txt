add_library(common)
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR})

target_compile_options(common PUBLIC 
/std:c++latest
/W4
/WX
)

if (WIN32)
    target_compile_definitions(common PUBLIC _WIN32_WINNT=0x0A00)
endif()

find_package(Boost REQUIRED)
find_package(TBB REQUIRED)

target_link_libraries(common PUBLIC
Boost::boost
TBB::tbb
)

 target_compile_definitions(common PUBLIC
 WIN32_LEAN_AND_MEAN
 NOMINMAX
 )

target_sources(common PRIVATE
finally.cpp
snowflake.cpp
stacktrace_exception.cpp
time_util.cpp
string_util.cpp
file_util.cpp
 "global.h")

add_subdirectory(execution)
add_subdirectory(log)
add_subdirectory(math)
add_subdirectory(stream)