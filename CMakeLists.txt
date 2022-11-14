cmake_minimum_required(VERSION 3.6)

project(mikubot)

add_subdirectory(mikubot)

# copy token file to build dir
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/token
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/mikubot
)
