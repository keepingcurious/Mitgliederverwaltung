cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")
project(Fanclub)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include standard directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Find the nlohmann/json header file (optional, if you're using it)
find_package(nlohmann_json REQUIRED)

# Add the main source files and headers
set(SOURCE_FILES
        src/Fanclub.cpp
        main.cpp
)

add_executable(Fanclub ${SOURCE_FILES})

# Link any required libraries (e.g., nlohmann/json)
target_link_libraries(Fanclub PRIVATE nlohmann_json::nlohmann_json)