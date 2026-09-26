add_library(constants constants.h constants.c)

add_executable(server server.c)
target_link_libraries(server PRIVATE constants)

add_executable(client client.c)
target_link_libraries(client PRIVATE constants)
