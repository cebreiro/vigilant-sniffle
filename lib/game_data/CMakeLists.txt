add_library(game_data)

find_package(TBB REQUIRED)

target_link_libraries(game_data PUBLIC
common
game_base
TBB::tbb
)

target_sources(game_data PRIVATE
game_data_source.cpp
)

add_subdirectory(generated)
add_subdirectory(refined)
add_subdirectory(utility)