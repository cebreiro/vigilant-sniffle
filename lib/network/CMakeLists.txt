add_library(network)

target_link_libraries(network PUBLIC
common
)

target_sources(network PRIVATE
socket.cpp
session.cpp
buffer.cpp
acceptor.cpp
connector.cpp
receive_buffer.cpp
network_executor.cpp
utility.cpp
)
