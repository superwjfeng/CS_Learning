set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(buffer_server.exe server.c)
target_link_libraries(buffer_server.exe event)
add_executable(buffer_client.exe client.c)
target_link_libraries(buffer_client.exe event)