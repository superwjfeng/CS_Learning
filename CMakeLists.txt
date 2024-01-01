cmake_minimum_required(VERSION 3.2)
project(CS_LEARNING)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)


link_directories(/usr/local/include)

add_subdirectory(Network)
add_subdirectory(Linux)
# add_subdirectory(DesignPattern/20.ObserverPattern)