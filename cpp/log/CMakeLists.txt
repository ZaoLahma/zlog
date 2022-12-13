add_library(log "")

target_sources(log
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc/log.h
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/log.cpp
  )
target_include_directories(log
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
  )

set_target_properties(log PROPERTIES LINKER_LANGUAGE CXX)
