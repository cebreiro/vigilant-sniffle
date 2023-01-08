target_sources(game_server PRIVATE
gateway_server.cpp
)

add_subdirectory(handler)
add_subdirectory(security)