add_library(odbc)

find_package(ODBC REQUIRED)

target_link_libraries(odbc PUBLIC
common
ODBC::ODBC
)

target_sources(odbc PRIVATE
data_source.cpp
connection.cpp
statement.cpp
result_set.cpp
)

add_subdirectory(detail)