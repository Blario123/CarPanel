add_library(
        include
        Background.h
        CarPanel.h
        Control.h
        Dial.h
        Display.h
        Global.h
        Indicator.h
        RevCounter.h
        Speedometer.h
        XMLParser.h
)

target_link_libraries(include Qt::Core Qt::Gui Qt::Widgets PkgConfig::LIBXMLXX)
target_include_directories(include PUBLIC ${PROJECT_SOURCE_DIR})