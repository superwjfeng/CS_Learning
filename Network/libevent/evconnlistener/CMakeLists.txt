set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(evconnlistener_server.exe server.c)
target_link_libraries(evconnlistener_server.exe event)
add_executable(evconnlistener_client.exe client.c)
target_link_libraries(evconnlistener_client.exe event)