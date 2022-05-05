# whatever-1623-nwp2-jeewonk2-aaghosh2

![header](https://capsule-render.vercel.app/api?type=soft&&color=timeAuto&height=200&section=header&text=US%20Road%20Map&fontSize=60&fontAlignY=43&desc=+What+is+the+most+efficient+way+to+traverse+the+United+States+by+road?&descAlign=50&descAlignY=70&animation=twinkling)


# Team 
> Nicholas Phillips (nwp2@illinois.edu)
>
> Jeewon Koo (jeewonk2@illinois.edu)
> 
> Akshay Ghosh (aaghosh2@illinois.edu)


# Github Organization 
- Code for main application: Locates in [src](https://github-dev.cs.illinois.edu/hdeep2/whatever-1623-nwp2-jeewonk2-aaghosh2/tree/main/src) folder
- Code for visualization: Locates in [vis](https://github-dev.cs.illinois.edu/hdeep2/whatever-1623-nwp2-jeewonk2-aaghosh2/tree/main/vis) folder
- Tests: Locates in [tests](https://github-dev.cs.illinois.edu/hdeep2/whatever-1623-nwp2-jeewonk2-aaghosh2/tree/main/tests) folder
- Data: Locates in [data](https://github-dev.cs.illinois.edu/hdeep2/whatever-1623-nwp2-jeewonk2-aaghosh2/tree/main/data) folder
- Development Weekly Log (log.md): Locates in [documents](https://github-dev.cs.illinois.edu/hdeep2/whatever-1623-nwp2-jeewonk2-aaghosh2/tree/main/documents) folder
- Written Report (results.md): Locates [here](https://github-dev.cs.illinois.edu/hdeep2/whatever-1623-nwp2-jeewonk2-aaghosh2/blob/main/documents/results.md)
- Presentation Video: Locates [here](https://drive.google.com/file/d/1BGJcbniiKzRWmkzaajew9BuRUCyQTONr/view?usp=sharing)


# Compile Instructions for local

<div align=center>

<img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=Windows&logoColor=white"> <img src="https://img.shields.io/badge/mac%20OS-000000?style=for-the-badge&logo=MacOS&logoColor=white"> 

```
mkdir build
cd build
cmake ..
make
```

run the executable in the project root folder for the default paths to be correct

</div>

# Compile Instructions for Web

<div align=center>

<img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=Windows&logoColor=white"> <img src="https://img.shields.io/badge/mac%20OS-000000?style=for-the-badge&logo=MacOS&logoColor=white">

In the vis folder
```
emcc ../src/main.cpp ../src/RoadGraph.cpp -I ../rapidcsv/src -std=c++17 -s WASM=1 -O3 -s ALLOW_MEMORY_GROWTH=1
```

