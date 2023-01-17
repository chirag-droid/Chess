# Chess in C++ with SDL2

This is an implementation of chess game in C++ using SDL2 graphics. A custom fork of Stockfish is used to create the chess engine AI.
All the 3rd party libraries are inside the `vendor/` directory and all the game source files in `src/`

## Steps to build yourself

### Clone the repo

Clone the repo recursively

```sh
git clone --recursive https://github.com/chirag-droid/Chess
```

### Use CMake to generate build files

If you are on windows, you can just open the project in Visual Studio.
Use b flag to specify build location and G to specify the generator.

You can also specify your build type (Debug/Release)

```sh
cmake -b build/ -G <generator>
```

### Compile the code

Go to the build directory and just compile the code with whichever generator you used

```sh
cd build
```
