cmake_minimum_required(VERSION 3.4)
project(print)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)

target_include_directories(print PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Примеры всегда собираются
add_executable(example1 examples/example1.cpp)
add_executable(example2 examples/example2.cpp)
target_link_libraries(example1 print)
target_link_libraries(example2 print)

install(TARGETS print example1 example2
    EXPORT print-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT print-config DESTINATION cmake)
