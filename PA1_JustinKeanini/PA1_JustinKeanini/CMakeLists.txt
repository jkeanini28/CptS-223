# CMakeList.txt : CMake project for PA1_JustinKeanini, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (PA1_JustinKeanini "main.cpp" "PA1_JustinKeanini.h" "Linked_List.h" "user.h")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/commands.csv
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/profiles.csv
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

# TODO: Add tests and install targets if needed.
