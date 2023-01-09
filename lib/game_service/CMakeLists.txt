add_library(game_service STATIC)

target_link_libraries(game_service PUBLIC
common
game_base
game_data
game_db
)

add_subdirectory(login)
add_subdirectory(world)