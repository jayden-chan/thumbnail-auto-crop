cmake_minimum_required(VERSION 3.10)

project(ThumbnailAutoCrop)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -Wshadow -Wconversion")
set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb -DFULLDEBUG -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -flto")
set (CMAKE_C_STANDARD 99)

include_directories(inc)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")
add_executable(
    main
    ${SOURCES}
)

target_link_libraries(main ${OpenCV_LIBS})
