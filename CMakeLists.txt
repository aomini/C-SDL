cmake_minimum_required(VERSION 3.16)
project(sdlProject)

# Set the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Build directory packages
set(SDL2_TTF_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/vendored/SDL2_ttf-2.24.0")
set(SDL2_TTF_LIBRARY "${CMAKE_SOURCE_DIR}/build/SDL2_ttf/libSDL2_ttf.dylib")



# Add source files
file(GLOB SOURCES "*.cpp" "src/*.cpp")
# print sources
message(STATUS "source files: ${SOURCES}")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include SDL2 headers
# includes sdl2 header files to the list of include paths
# similar g++ -I /usr/include/SDL2 -c main.cpp
# Modern target_include_directories()
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_TTF_INCLUDE_DIRS})

# Link SD2 library
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image ${SDL2_TTF_LIBRARY})


