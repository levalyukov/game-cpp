cmake_minimum_required(VERSION 3.24)
project(soup)

# .:: Libraries ::.
add_subdirectory(libs/sfml)
add_subdirectory(libs/catch2)
add_subdirectory(src/engine)

# .:: Setup game tests ::.
file(GLOB_RECURSE tests "src/game/tests/*.cpp")
add_executable(gametests ${tests})
target_link_libraries(gametests PUBLIC 
  Catch2::Catch2WithMain
  sfml-graphics 
  sfml-window 
  sfml-system
)

# .:: Setup main ::.
file(GLOB_RECURSE src "src/*.cpp" "src/*.hpp")
add_executable(game ${src})
target_link_libraries(game PUBLIC 
  Catch2::Catch2WithMain
  sfml-graphics 
  sfml-window 
  sfml-system
  engine
)

# .:: Copying DLL ::.
add_custom_command(TARGET game POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:Catch2::Catch2>"
    "$<TARGET_FILE:Catch2::Catch2WithMain>"
    "$<TARGET_FILE:sfml-system>"
    "$<TARGET_FILE:sfml-window>"
    "$<TARGET_FILE:sfml-graphics>"
    $<TARGET_FILE_DIR:game>
)

add_custom_command(TARGET gametests POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:Catch2::Catch2>"
    "$<TARGET_FILE:Catch2::Catch2WithMain>"
    "$<TARGET_FILE:sfml-system>"
    "$<TARGET_FILE:sfml-window>"
    "$<TARGET_FILE:sfml-graphics>"
     $<TARGET_FILE_DIR:gametests>
)