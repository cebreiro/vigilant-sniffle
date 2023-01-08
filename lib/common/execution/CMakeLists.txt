target_sources(common PRIVATE
promise.cpp
executor.cpp
executor_await.cpp
thread_pool.cpp
future.cpp
)

add_subdirectory(detail)