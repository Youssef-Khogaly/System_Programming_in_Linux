


cmake_minimum_required(VERSION 3.10)

project(echo VERSION 1.0)

set(SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR}/echo.c)





add_executable(echo ${SOURCEFILES} )
set_target_properties(echo PROPERTIES LINKER_LANGUAGE C)