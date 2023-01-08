target_sources(game_server PRIVATE
login_server.cpp
)

add_subdirectory(handler)
add_subdirectory(security)