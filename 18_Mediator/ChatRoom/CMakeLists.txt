cmake_minimum_required(VERSION 3.5)
project(MediatorPattern LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "configuring ${PROJECT_NAME} project with ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} version")

list(APPEND _flags "-fPIC" "-Wall" "-Werror" "-Wpedantic" "-Wextra")
set(USE_LIBRARY ON)
set(BUILD_SHARED_LIBRARY ON)

list(APPEND
    _chatRoom
    Person.cpp
    ChatRoom.cpp
    )

add_library(chatroom
            SHARED
            ${_chatRoom}
            )

set_target_properties(chatroom
                     PROPERTIES
                     POSITION_INDEPENDENT_CODE 1)

target_compile_options(chatroom
                      PUBLIC
                      ${_flags}
                      )

target_include_directories(chatroom PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(exeChat
               main.cpp
               )
target_link_libraries(exeChat PRIVATE chatroom)
