add_executable(game_server)
target_include_directories(game_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_precompile_headers(game_server PRIVATE
<cctype>
<cstdint>
<cassert>
<string>
<sstream>
<fstream>
<iostream>
<tuple>
<array>
<bitset>
<vector>
<list>
<forward_list>
<map>
<set>
<unordered_map>
<unordered_set>
<queue>
<stack>
<regex>
<random>
<memory>
<chrono>
<stdexcept>
<optional>
<variant>
<any>
<filesystem>
<mutex>
<atomic>
<future>
<shared_mutex>
<condition_variable>
<numeric>
<algorithm>
<ranges>
<coroutine>
<type_traits>
<typeinfo>
<typeindex>
<format>
<tbb/concurrent_hash_map.h>
<boost/container/small_vector.hpp>
<boost/container/flat_map.hpp>
<lib/common/global.h>
<lib/common/execution/future.h>
<lib/common/execution/future_await.h>
<lib/common/execution/executor_await.h>
<lib/common/stacktrace_exception.h>
)

find_package(TBB CONFIG REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(game_server PRIVATE
common
network
game_base
game_data
game_db
game_service
TBB::tbb
nlohmann_json::nlohmann_json
)

target_sources(game_server PRIVATE
main.cpp
game_server.cpp
)

add_subdirectory(config)
add_subdirectory(login)
add_subdirectory(gateway)
add_subdirectory(service)
add_subdirectory(world)
add_subdirectory(zone)