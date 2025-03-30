


cmake_minimum_required(VERSION 3.10)

project(pwd VERSION 1.0)

set(SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR}/pwd.c)





add_executable(pwd ${SOURCEFILES} )
set_target_properties(pwd PROPERTIES LINKER_LANGUAGE C)