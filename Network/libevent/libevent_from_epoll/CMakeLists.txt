set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(libevent_demo.exe libevent_demo.c)
target_link_libraries(libevent_demo.exe event)