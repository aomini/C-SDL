cmake_minimum_required(VERSION 3.16)
project(sdlProject)

# Set the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Add source files
#file(GLOB SOURCES "src/*.cpp")
file(GLOB SOURCES "*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SD2 library
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

