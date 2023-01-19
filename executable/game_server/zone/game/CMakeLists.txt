target_sources(game_server PRIVATE
zone.cpp
)

add_subdirectory(component)
add_subdirectory(controller)
add_subdirectory(domain)
add_subdirectory(event)
add_subdirectory(stage)
add_subdirectory(object)