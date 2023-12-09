set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(server.exe server.c)
target_link_libraries(server.exe event)
add_executable(client.exe client.c)
target_link_libraries(client.exe event)