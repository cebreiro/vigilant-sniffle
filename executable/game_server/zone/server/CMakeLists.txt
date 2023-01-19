target_sources(game_server PRIVATE
zone_server.cpp
)

add_subdirectory(handler)
add_subdirectory(security)