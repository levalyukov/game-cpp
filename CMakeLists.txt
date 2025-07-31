cmake_minimum_required(VERSION 3.15)
project(game)

# .:: Libraries ::.
add_subdirectory(third_party/sfml)
add_subdirectory(third_party/catch2)


# .:: Setup tests ::.
file(GLOB_RECURSE TESTS 
    "tests/*.cpp"
    "src/core/economy/economy.hpp"
    "src/core/resources/resources.hpp"
)

add_executable(tests ${TESTS})
target_link_libraries(tests PRIVATE 
    Catch2::Catch2WithMain
    sfml-graphics 
    sfml-window 
    sfml-system
)

# .:: Setup main ::.
file(GLOB_RECURSE GAME 
    "src/*.cpp" 
    "src/*.hpp"
)

add_executable(main ${GAME})
target_link_libraries(main PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system
)

# .:: Copying DLL ::.
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:sfml-system>"
        "$<TARGET_FILE:sfml-window>"
        "$<TARGET_FILE:sfml-graphics>"
        $<TARGET_FILE_DIR:main>
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