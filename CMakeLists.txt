cmake_minimum_required(VERSION 3.20)
project(XmlQt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(PROJECT_SOURCES
        ${SRC_DIR}/main.cpp)

add_executable(XmlQt ${PROJECT_SOURCES})
target_link_libraries(XmlQt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

