cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(person_builder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "configuring ${PROJECT_NAME} project with ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} version")

list(APPEND _flags "-fPIC" "-Wall" "-Werror" "-Wpedantic" "-Wextra")
set(USE_LIBRARY ON)
set(BUILD_SHARED_LIBRARY ON)

list(APPEND
    _drink_src
    HotDrink.cpp
    HotDrinkFactory.cpp
    #DrinkFactory.cpp
    )

add_library(HotDrinkFactory
            SHARED
            ${_drink_src}
            )

set_target_properties(HotDrinkFactory
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE 1)

target_compile_options(HotDrinkFactory
                           PUBLIC
                           ${_flags}
                           )
target_include_directories(HotDrinkFactory PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(drink.out
               main.cpp
              )

target_link_libraries(drink.out PRIVATE HotDrinkFactory)
