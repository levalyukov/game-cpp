cmake_minimum_required(VERSION 3.24)
project(miren)

file(GLOB_RECURSE engine_src "*.cpp")
list(FILTER engine_src EXCLUDE REGEX ".*tests.*")
add_library(engine STATIC ${engine_src})
list(REMOVE_ITEM SRC_EXECUTABLE ${ENGINE_SOURCES})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE engine_tests "tests/*.cpp")
add_executable(mirentests ${engine_tests})
target_link_libraries(mirentests PRIVATE 
  engine
  sfml-graphics 
  sfml-window 
  sfml-system
  Catch2::Catch2WithMain
)

add_custom_command(TARGET mirentests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:Catch2::Catch2>"
    "$<TARGET_FILE:Catch2::Catch2WithMain>"
    "$<TARGET_FILE:sfml-graphics>"
    "$<TARGET_FILE:sfml-window>"
    "$<TARGET_FILE:sfml-system>"
     $<TARGET_FILE_DIR:mirentests>
)