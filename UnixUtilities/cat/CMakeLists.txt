


cmake_minimum_required(VERSION 3.10)

project(mcat VERSION 1.0)
set(SOURCEFILES ${CMAKE_CURRENT_SOURCE_DIR}/mcat.c)





add_executable(mcat ${SOURCEFILES})
set_target_properties(mcat PROPERTIES LINKER_LANGUAGE C)