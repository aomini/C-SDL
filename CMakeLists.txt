cmake_minimum_required(VERSION 3.16)
project(sdlProject)

# Set the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Find SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Include SDL2 headers
# includes sdl2 header files to the list of include paths
# similar g++ -I /usr/include/SDL2 -c main.cpp
# Modern target_include_directories()
include_directories(${SDL2_INCLUDE_DIRS})

# Add source files
#file(GLOB SOURCES "src/*.cpp")
file(GLOB SOURCES "*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})


# SDL2 header files
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/vendored/SDL_image/include)


# Link SD2 library
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)

# Link SDL2_image library (manually specify the built library path)
#target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/build/vendored/SDL_image)


