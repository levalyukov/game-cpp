cmake_minimum_required(VERSION 3.16)
project(soup)

# .:: Libraries ::.
add_subdirectory(libs/sfml)
add_subdirectory(libs/catch2)

# .:: Setup tests ::.
file(GLOB_RECURSE TESTS "tests/*.cpp")
add_executable(tests ${TESTS})
target_link_libraries(tests PRIVATE 
  Catch2::Catch2WithMain
  sfml-graphics 
  sfml-window 
  sfml-system
)

# .:: Setup main ::.
file(GLOB_RECURSE src 
  "src/*.cpp" 
  "src/*.hpp"
)

file(GLOB_RECURSE engine_src "src/engine/*.cpp")
add_library(engine STATIC ${engine_src})
list(REMOVE_ITEM SRC_EXECUTABLE ${ENGINE_SOURCES})
include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
add_executable(soup ${src})
target_link_libraries(soup PRIVATE 
  sfml-graphics 
  sfml-window 
  sfml-system
  engine
)

# .:: Copying DLL ::.
add_custom_command(TARGET soup POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:sfml-system>"
    "$<TARGET_FILE:sfml-window>"
    "$<TARGET_FILE:sfml-graphics>"
    $<TARGET_FILE_DIR:soup>
)

add_custom_command(TARGET tests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:Catch2::Catch2>"
    "$<TARGET_FILE:Catch2::Catch2WithMain>"
    "$<TARGET_FILE:sfml-system>"
    "$<TARGET_FILE:sfml-window>"
    "$<TARGET_FILE:sfml-graphics>"
     $<TARGET_FILE_DIR:tests>
)