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
    _person_src
    Person.cpp
    PersonBuilder.cpp
    PersonAddressBuilder.cpp
    PersonJobBuilder.cpp
    )

add_library(PersonBuilder
            SHARED
            ${_person_src}
            )

set_target_properties(PersonBuilder
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE 1)

target_compile_options(PersonBuilder
                           PUBLIC
                           ${_flags}
                           )
target_include_directories(PersonBuilder PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(person.out
               main.cpp
              )

target_link_libraries(person.out PRIVATE PersonBuilder)
