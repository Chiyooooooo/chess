cmake_minimum_required(VERSION 3.21.2)

project(chessengine)


add_executable(chessengine)

set_target_properties(chessengine PROPERTIES OUTPUT_NAME chessengine)
set_target_properties(chessengine PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)

target_compile_options(chessengine PRIVATE -Wall -Wextra -Werror -pedantic -fno-builtin -fsanitize=address)

target_link_options(chessengine PRIVATE -fsanitize=address)
target_include_directories(chessengine PUBLIC "include/")


# subdirs(src)

# subdir c'est la ou je met les cmaklist 
add_subdirectory(src)
# add_subdirectory(tests)
