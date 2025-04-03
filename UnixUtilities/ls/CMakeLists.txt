


cmake_minimum_required(VERSION 3.10)

project(ls VERSION 1.0)

set(SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR}/ls.c)





add_executable(ls ${SOURCEFILES} )
set_target_properties(ls PROPERTIES LINKER_LANGUAGE C)