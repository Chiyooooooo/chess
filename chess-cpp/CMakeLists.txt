cmake_minimum_required(VERSION 3.21.2)

project(chessengine)


add_library(chessengine SHARED src/main.cc)

set_target_properties(chessengine PROPERTIES OUTPUT_NAME chess)
set_target_properties(chessengine PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)

target_compile_options(chessengine PRIVATE -Wall -Wextra -Werror -pedantic -fno-builtin -fsanitize=address)

target_include_directories(chessengine PUBLIC "include/")

find_library(YAML-CPP NAMES libyaml-cpp yaml-cpp REQUIRED)

target_link_libraries(chessengine PRIVATE ${YAML-CPP})

#subdirs(src)
# subdir c'est la ou je met les cmaklist 
add_subdirectory(zorkxplorer)
add_subdirectory(tests)
