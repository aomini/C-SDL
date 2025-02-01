# Build with CMakeLists.txt

# SDL2 is installed with brew `brew install sdl2`

### Compile_commands.json is generated using cmake, so that the nvim lsp will recognize the sdl2 header files.

```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
```

# - Dependencies Installation

1. Navigate to build directory
2. Create a directory SDL2_ttf, reference `CMakeLists.txt`
3. Run `cmake ../../vendored/SDL_ttf`
4. Run `make`
5. Optionallym Run `make install` to install globally
