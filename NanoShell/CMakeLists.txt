


cmake_minimum_required(VERSION 3.10)


project(shell VERSION 1.0)
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/shell.h   ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer.h ${CMAKE_CURRENT_SOURCE_DIR}/list.h)
set(SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR}/shell.c  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer.c ${CMAKE_CURRENT_SOURCE_DIR}/list.c)
set(COMPILER_FLAGS -Wall -Wextra -O0)

add_compile_options(${COMPILER_FLAGS})



add_executable(shell ${SOURCEFILES} )
target_include_directories(shell PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          ${CMAKE_CURRENT_SOURCE_DIR}
                          )
set_target_properties(shell PROPERTIES LINKER_LANGUAGE C)