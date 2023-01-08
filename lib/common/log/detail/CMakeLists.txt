target_sources(common PRIVATE
spd_log_service.cpp
)

find_package(spdlog REQUIRED)

target_link_libraries(common PRIVATE
spdlog::spdlog
)