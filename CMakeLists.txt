cmake_minimum_required(VERSION 3.16)
project(CarPanel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.2.2/mingw_64/lib/cmake")
else()
    set(CMAKE_PREFIX_PATH /home/blair/Qt/6.3.0/gcc_64)
endif(WIN32)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

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
        )

add_executable(CarPanel ${source_gui})

target_link_libraries(CarPanel
        include
)
