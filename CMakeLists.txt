cmake_minimum_required(VERSION 3.16)
project(Fanclub LANGUAGES CXX)

# C++ Standard festlegen
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt-Automation aktivieren
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 1. Qt Pakete finden
find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
)

# 2. nlohmann/json plattformunabhängig per FetchContent laden
include(FetchContent)
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(nlohmann_json)

# 3. Quelldateien
set(SOURCE_FILES
        src/fanclub.cpp
        src/fanclub.hpp
        main.cpp
        spiele.cpp
        spiele.hpp
)

# 4. Executable erstellen (WIN32: unter Windows ohne Konsolenfenster)
add_executable(Fanclub WIN32 ${SOURCE_FILES})

# 5. Include-Verzeichnisse
target_include_directories(Fanclub PRIVATE ${PROJECT_SOURCE_DIR}/src)

# 6. Compiler-Optionen (nur für GCC/Clang)
if(NOT MSVC)
    target_compile_options(Fanclub PRIVATE
            $<$<CONFIG:Debug>:-O0 -g3>
    )
endif()

# 7. Bibliotheken verknüpfen
target_link_libraries(Fanclub PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        nlohmann_json::nlohmann_json
)