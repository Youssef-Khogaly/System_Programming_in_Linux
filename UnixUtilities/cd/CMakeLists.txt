


cmake_minimum_required(VERSION 3.10)

project(cd VERSION 1.0)

set(SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR}/cd.c)





add_executable(cd ${SOURCEFILES} )
set_target_properties(cd PROPERTIES LINKER_LANGUAGE C)