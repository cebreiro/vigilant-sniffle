add_library(game_base STATIC)

target_link_libraries(game_base PUBLIC
common
odbc
)

add_subdirectory(data)
add_subdirectory(db)
add_subdirectory(network)
add_subdirectory(type)