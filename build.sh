##
## EPITECH PROJECT, 2019
## CPP_babel_2019
## File description:
## build
##

mkdir -p build && cd build && conan install --build=missing .. && cmake .. -G "Unix Makefiles" && cmake –build . && make && cp ./bin/* ..