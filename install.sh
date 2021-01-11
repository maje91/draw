mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target draw
sudo cmake --install .
rm -rf build

