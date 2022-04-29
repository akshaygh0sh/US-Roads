# whatever-1623-nwp2-jeewonk2-aaghosh2
Fianl project for nwp2, jeewonk2, aaghosh2


# how to compile for local

```
mkdir build
cd build
cmake ..
make
```

# how to compile for web

In the vis folder
```
emcc ../src/main.cpp ../src/RoadGraph.cpp -I ../rapidcsv/src -std=c++17 -s WASM=1 -O3 -s ALLOW_MEMORY_GROWTH=1
```