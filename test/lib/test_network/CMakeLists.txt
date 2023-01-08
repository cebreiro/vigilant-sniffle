add_executable(test_network)

find_package(GTest CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)

target_link_libraries(test_network PRIVATE 
common
network
TBB::tbb
GTest::gtest
GTest::gtest_main
)

target_sources(test_network PRIVATE
main.cpp
test_receive_buffer.cpp
)

add_subdirectory(integrate)