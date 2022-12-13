add_library(zlog "")

target_sources(zlog
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc/zlog.h
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/zlog.cpp
  )
target_include_directories(zlog
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
  )

set_target_properties(zlog PROPERTIES LINKER_LANGUAGE CXX)
