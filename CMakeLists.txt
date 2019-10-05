cmake_minimum_required(VERSION 3.5)
project(Babel)

# NOTE Do not remove
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.13.1/gcc_64)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SRC_AUDIO
    # ./srcs/audio/main.cpp
    ./srcs/audio/Audio.cpp
    ./srcs/audio/ADataTransfer.cpp
    ./srcs/audio/Encoder.cpp
    ./srcs/audio/Decoder.cpp
)

set(SRC_SERVER
    ./srcs/server/main.cpp
    ./srcs/server/Server.cpp
    ./srcs/server/Client.cpp
    ./srcs/server/Server.cpp
    ./srcs/server/sql/Connector.cpp
    ./srcs/network/Socket.cpp
)

set(SRC_CLIENT
    # ./srcs/client/main.cpp
    ./srcs/client/Client.cpp
    ./srcs/client/Client_call.cpp
    ./srcs/client/Client_friend.cpp
    ./srcs/client/AudioModule.cpp
    ./srcs/audio/ADataTransfer.cpp
    ./srcs/audio/Audio.cpp
    ./srcs/audio/Receiver.cpp
    ./srcs/audio/Sender.cpp
    ./srcs/audio/Encoder.cpp
    ./srcs/audio/Decoder.cpp
    ./srcs/network/Socket.cpp
    ./srcs/client/AudioModule.cpp
)

set(SRC_GUI
    ./srcs/gui/CPP/main.cpp
    ./srcs/gui/CPP/Messager.cpp
    ./srcs/gui/CPP/Call.cpp
    ./srcs/gui/CPP/Worker.cpp
    ./srcs/gui/CPP/Contacts.cpp
    ./srcs/gui/CPP/Login.cpp
    ./srcs/gui/CPP/Network.cpp
    ./srcs/gui/CPP/Settings.cpp
    ./srcs/gui/CPP/Engine.cpp
)

set(RESSOURCES_GUI
    ./srcs/gui/qml.qrc
)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5QuickControls2 REQUIRED)
find_package(Qt5Test REQUIRED)

qt5_add_resources(RESOURCES ${RESSOURCES_GUI})

# add_executable(audio_bin ${SRC_AUDIO})
add_executable(babel_server ${SRC_SERVER})
# add_executable(babel_client ${SRC_CLIENT})
add_executable(babel_gui ${SRC_GUI} ${SRC_CLIENT} ${SRC_AUDIO} ${RESOURCES})

# target_link_libraries(audio_bin ${CONAN_LIBS})
target_link_libraries(babel_server ${CONAN_LIBS})
# target_link_libraries(babel_client ${CONAN_LIBS})

target_link_libraries(babel_gui ${CONAN_LIBS})
target_link_libraries(babel_gui Qt5::Core)
target_link_libraries(babel_gui Qt5::Quick)
target_link_libraries(babel_gui Qt5::Qml)
target_link_libraries(babel_gui Qt5::QuickControls2)
target_link_libraries(babel_gui Qt5::Test)