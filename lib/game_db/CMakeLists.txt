add_library(game_db)

target_link_libraries(game_db PUBLIC
common
game_base
)

target_sources(game_db PRIVATE
game_db.cpp
)

add_subdirectory(entity)
add_subdirectory(generated)