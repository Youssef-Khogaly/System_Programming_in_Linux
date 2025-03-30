


cmake_minimum_required(VERSION 3.10)

project(cp VERSION 1.0)

set(SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR}/cp.c)





add_executable(cp ${SOURCEFILES} )
set_target_properties(cp PROPERTIES LINKER_LANGUAGE C)