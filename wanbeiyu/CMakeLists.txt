cmake_minimum_required(VERSION 3.10)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(wanbeiyu VERSION 0.1.0)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_EXTENSIONS OFF)

set(WANBEIYU_WARNINGS -Wall -Wextra -Wpedantic -Werror)

add_library(wanbeiyu_buttons STATIC src/buttons.c)
target_include_directories(wanbeiyu_buttons PUBLIC include)
target_compile_options(wanbeiyu_buttons PUBLIC ${WANBEIYU_WARNINGS})

add_library(wanbeiyu_touch_screen STATIC src/touch_screen.c)
target_include_directories(wanbeiyu_touch_screen PUBLIC include)
target_compile_options(wanbeiyu_touch_screen PUBLIC ${WANBEIYU_WARNINGS})

add_library(wanbeiyu_c_stick STATIC src/c_stick.c)
target_include_directories(wanbeiyu_c_stick PUBLIC include)
target_compile_options(wanbeiyu_c_stick PUBLIC ${WANBEIYU_WARNINGS})

add_library(wanbeiyu_circle_pad STATIC src/circle_pad.c)
target_include_directories(wanbeiyu_circle_pad PUBLIC include)
target_compile_options(wanbeiyu_circle_pad PUBLIC ${WANBEIYU_WARNINGS})

add_library(wanbeiyu_state STATIC src/state.c)
target_include_directories(wanbeiyu_state PUBLIC include)
target_compile_options(wanbeiyu_state PUBLIC ${WANBEIYU_WARNINGS})

add_library(wanbeiyu_parser STATIC src/parser.c)
target_include_directories(wanbeiyu_parser PUBLIC include)
target_compile_options(wanbeiyu_parser PUBLIC ${WANBEIYU_WARNINGS})

add_library(wanbeiyu STATIC src/wanbeiyu.c)
target_include_directories(wanbeiyu PUBLIC include)
target_compile_options(wanbeiyu PUBLIC ${WANBEIYU_WARNINGS})
target_link_libraries(wanbeiyu
    wanbeiyu_buttons
    wanbeiyu_touch_screen
    wanbeiyu_c_stick
    wanbeiyu_circle_pad
    wanbeiyu_state
    wanbeiyu_parser
)

enable_testing()
add_executable(wanbeiyu_test test/main.c)
target_link_libraries(wanbeiyu_test wanbeiyu)
add_test(NAME wanbeiyu_test COMMAND wanbeiyu_test)

add_executable(wanbeiyu_test_helper test/helper.c)
target_link_libraries(wanbeiyu_test_helper wanbeiyu)
add_test(NAME wanbeiyu_test_helper COMMAND wanbeiyu_test_helper)