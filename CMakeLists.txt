cmake_minimum_required(VERSION 2.8.12)
project(Babel)

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SRC_AUDIO
    ./srcs/main.cpp
    ./srcs/Babel.cpp
    ./srcs/Audio.cpp
    ./srcs/ADataTransfer.cpp
    ./srcs/network/Socket.cpp
)

set(SRC_SERVER
    ./srcs/server/main.cpp
    ./srcs/server/Client.cpp
    ./srcs/network/Socket.cpp
)

set(SRC_CLIENT
    ./srcs/client/main.cpp
    ./srcs/network/Socket.cpp
)

add_executable(audio_bin ${SRC_AUDIO})
add_executable(server_bin ${SRC_SERVER})
add_executable(client_bin ${SRC_CLIENT})
target_link_libraries(audio_bin ${CONAN_LIBS})
target_link_libraries(server_bin ${CONAN_LIBS})
target_link_libraries(client_bin ${CONAN_LIBS})