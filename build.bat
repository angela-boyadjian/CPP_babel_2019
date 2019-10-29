mkdir build
cd build
conan install ..
cmake -G "Visual Studio 15 2017" ..
cd ..