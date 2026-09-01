cmake_minimum_required(VERSION 3.20)

project(console_chess LANGUAGES C)

add_executable(console_chess
    "src/main.c"
    "src/game.c"
    "src/rules.c"
    "src/console_ui.c"
)

target_include_directories(console_chess PRIVATE "src")
target_compile_features(console_chess PRIVATE c_std_11)

if(MSVC)
    target_compile_options(console_chess PRIVATE /W4 /utf-8)
endif()
