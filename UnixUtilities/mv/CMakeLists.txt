


cmake_minimum_required(VERSION 3.10)

project(mv VERSION 1.0)

set(SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR}/mv.c)





add_executable(mv ${SOURCEFILES} ${HEADERFILES} )
set_target_properties(mv PROPERTIES LINKER_LANGUAGE C)