add_library(include Background.h CarPanel.h Control.h Dial.h Display.h Global.h Indicator.h RevCounter.h Speedometer.h)

target_link_libraries(include Qt::Core Qt::Gui Qt::Widgets)
target_include_directories(include PUBLIC ${PROJECT_SOURCE_DIR})