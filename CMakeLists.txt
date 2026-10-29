cmake_minimum_required(VERSION 3.16)
project(Fanclub)

# C++ Standard festlegen (wähle 17 oder 20, hier beispielhaft C++17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug-Flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")

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

find_package(nlohmann_json REQUIRED)

# 2. Quelldateien ZUERST definieren (WICHTIG!)
set(SOURCE_FILES
        src/fanclub.cpp
        src/fanclub.hpp # falls vorhanden, sonst anpassen
        main.cpp
        spiele.cpp
        spiele.hpp
)

# 3. Executable erstellen
add_executable(Fanclub ${SOURCE_FILES})

# 4. Include-Verzeichnisse
target_include_directories(Fanclub PRIVATE ${PROJECT_SOURCE_DIR}/src)

# 5. Bibliotheken verknüpfen (Qt + nlohmann/json gebündelt für das Ziel "Fanclub")
target_link_libraries(Fanclub PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        nlohmann_json::nlohmann_json
)