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

# 1. Pakete finden
find_package(Qt6 REQUIRED COMPONENTS
        Core
        Gui
        Widgets
)

# nlohmann/json: zuerst auf dem System suchen (ohne REQUIRED!),
# andernfalls automatisch herunterladen.
find_package(nlohmann_json 3.11 QUIET)
if(NOT nlohmann_json_FOUND)
    message(STATUS "nlohmann_json nicht gefunden - wird per FetchContent geladen")
    include(FetchContent)
    FetchContent_Declare(
            nlohmann_json
            URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
            DOWNLOAD_EXTRACT_TIMESTAMP ON
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

# 2. Quelldateien
set(SOURCE_FILES
        src/fanclub.cpp
        src/fanclub.hpp
        main.cpp
        spiele.cpp
        spiele.hpp
)

# 3. Executable erstellen (WIN32: unter Windows ohne Konsolenfenster, sonst ignoriert)
add_executable(Fanclub WIN32 ${SOURCE_FILES})

# 4. Include-Verzeichnisse
target_include_directories(Fanclub PRIVATE ${PROJECT_SOURCE_DIR}/src)

# 5. Compiler-Optionen (nur für GCC/Clang, MSVC kennt -O0/-g3 nicht)
if(NOT MSVC)
    target_compile_options(Fanclub PRIVATE
            $<$<CONFIG:Debug>:-O0 -g3>
    )
endif()

# 6. Bibliotheken verknüpfen
target_link_libraries(Fanclub PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        nlohmann_json::nlohmann_json
)