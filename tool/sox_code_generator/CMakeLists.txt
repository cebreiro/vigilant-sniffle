add_executable(sox_code_generator)

find_package(spdlog REQUIRED)

target_link_libraries(sox_code_generator PRIVATE
common
game_base
spdlog::spdlog
)

target_precompile_headers(sox_code_generator PRIVATE
<cstdint>
<string>
<vector>
<sstream>
<filesystem>
<ranges>
<fstream>
)


target_sources(sox_code_generator PRIVATE
main.cpp
sox_name_util.cpp
sox_class_generator.cpp
text_writer.cpp
)