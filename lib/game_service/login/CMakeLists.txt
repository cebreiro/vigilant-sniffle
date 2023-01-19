target_sources(game_service PRIVATE
auth_token.cpp
)

add_subdirectory(event)
add_subdirectory(method)