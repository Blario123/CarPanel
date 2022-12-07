cmake_minimum_required(VERSION 3.16)
project(CarPanel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(PkgConfig REQUIRED)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

pkg_check_modules(LIBXMLXX REQUIRED IMPORTED_TARGET libxml++-5.0)

include_directories("/usr/include/libxml++-5.0")

qt6_add_resources(resources resources.qrc)

include_directories(include)
add_subdirectory(include)

set(source_gui
        ${resources}
        src/main.cpp
        src/CarPanel.cpp
        src/Control.cpp
        src/Display.cpp
        src/Speedometer.cpp
        src/RevCounter.cpp
        src/Dial.cpp
        src/Indicator.cpp
        src/XMLParser.cpp
        )

add_executable(CarPanel ${source_gui})

target_link_libraries(CarPanel
        include
)
