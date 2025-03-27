cmake_minimum_required(VERSION 3.10)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(wanbeiyu VERSION 0.1.0)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_EXTENSIONS OFF)

add_library(wanbeiyu INTERFACE)
target_include_directories(wanbeiyu INTERFACE include)
target_compile_options(wanbeiyu INTERFACE -Wall -Wextra -Wpedantic -Werror)

enable_testing()
add_executable(wanbeiyu_test test/main.c)
target_link_libraries(wanbeiyu_test wanbeiyu)
add_test(NAME wanbeiyu_test COMMAND wanbeiyu_test)

add_executable(wanbeiyu_test_helper test/helper.c)
target_link_libraries(wanbeiyu_test_helper wanbeiyu)
add_test(NAME wanbeiyu_test_helper COMMAND wanbeiyu_test_helper)