cmake_minimum_required(VERSION 3.5 FATAL_ERROR) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#set(GTEST_ROOT "~/../../usr/local/gtest/")

enable_testing()

list(APPEND _flags "-fPIC" "-g" "-Werror" "-Wpedantic" "-Wextra")
if(${DEBUG})
    message(STATUS "MODE = DEBUG")
    list(APPEND _flags "-g")
else()
    list(APPEND _flags  "-g" )
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(gtest REQUIRED gtest>=1.8.1)
#pkg_check_modules(googletest REQUIRED gmock>=1.8.1)
include_directories(${gtest_INCLUDE_DIRS})
message(STATUS "PATH TO GTEST : ${gtest_INCLUDE_DIRS}")

add_executable(2.out 
                2_dependencyInjection.cpp
               )

target_link_libraries(2.out ${gtest_LIBRARIES} )

target_compile_options(2.out
                       PRIVATE
                       ${_flags}
                       )


add_test(NAME test COMMAND 2.out)
