


cmake_minimum_required(VERSION 3.10)

project(shell VERSION 1.0)
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/echo.h)
set(SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR}/shell.c ${CMAKE_CURRENT_SOURCE_DIR}/echo.c)





add_executable(shell ${SOURCEFILES} )
target_include_directories(shell PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          ${CMAKE_CURRENT_SOURCE_DIR}
                          )
set_target_properties(shell PROPERTIES LINKER_LANGUAGE C)