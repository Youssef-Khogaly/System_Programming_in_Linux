


cmake_minimum_required(VERSION 3.10)


project(shell VERSION 1.0)
#Header Files 
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/shell.h   ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer.h ${CMAKE_CURRENT_SOURCE_DIR}/list.h
${CMAKE_CURRENT_SOURCE_DIR}/utilities/cat.h ${CMAKE_CURRENT_SOURCE_DIR}/utilities/cd.h ${CMAKE_CURRENT_SOURCE_DIR}/utilities/cp.h 
${CMAKE_CURRENT_SOURCE_DIR}/utilities/echo.h ${CMAKE_CURRENT_SOURCE_DIR}/utilities/ls.h ${CMAKE_CURRENT_SOURCE_DIR}/utilities/mv.h
${CMAKE_CURRENT_SOURCE_DIR}/utilities/pwd.h)
#source files 
set(SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR}/shell.c  ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer.c ${CMAKE_CURRENT_SOURCE_DIR}/list.c
${CMAKE_CURRENT_SOURCE_DIR}/utilities/cat.c ${CMAKE_CURRENT_SOURCE_DIR}/utilities/cd.c ${CMAKE_CURRENT_SOURCE_DIR}/utilities/cp.c 
${CMAKE_CURRENT_SOURCE_DIR}/utilities/echo.c ${CMAKE_CURRENT_SOURCE_DIR}/utilities/ls.c ${CMAKE_CURRENT_SOURCE_DIR}/utilities/mv.c
${CMAKE_CURRENT_SOURCE_DIR}/utilities/pwd.c)


set(COMPILER_FLAGS -g -Wall -Wextra -O0)

add_compile_options(${COMPILER_FLAGS})



add_executable(shell ${SOURCEFILES} ${HEADER_FILES})
target_include_directories(shell PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          ${CMAKE_CURRENT_SOURCE_DIR}
                          ${CMAKE_CURRENT_SOURCE_DIR}/utilities
                          )
set_target_properties(shell PROPERTIES LINKER_LANGUAGE C)