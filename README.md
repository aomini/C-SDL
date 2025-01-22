# Build with CMakeLists.txt

# SDL2 is installed with brew `brew install sdl2`

### Compile_commands.json is generated using cmake, so that the nvim lsp will recognize the sdl2 header files.

```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
```
