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
        Xml
        Core5Compat
        REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(PROJECT_SOURCES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/XmlSaxHandler.cpp
        ${INCLUDE_DIR}/XmlSaxHandler.h
        ${INCLUDE_DIR}/Service.h
        ${SRC_DIR}/Service.cpp)

add_executable(XmlQt ${PROJECT_SOURCES})

target_include_directories(XmlQt PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(XmlQt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Xml
        Qt6::Core5Compat
        )