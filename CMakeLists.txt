cmake_minimum_required(VERSION 3.20)
project(XmlQt)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        Core5Compat
        REQUIRED)

# Compile CSharp code that will be embedded
add_custom_target(LinqToXmlCSharp ALL
        COMMAND mcs -out:${PROJECT_SOURCE_DIR}/Embedded/LinqToXml.dll
            /reference:System.Xml.Linq
        ${PROJECT_SOURCE_DIR}/Embedded/LinqToXml.cs
        COMMENT "Compiling CSharp code..."
        VERBATIM
        )

message("MSC OUTPUT: ${MSC_OUTPUT}")

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(PROJECT_SOURCES
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/XmlSaxHandler.cpp
        ${INCLUDE_DIR}/XmlSaxHandler.h
        ${INCLUDE_DIR}/Service.h
        ${SRC_DIR}/Service.cpp
        ${SRC_DIR}/XmlDomReader.cpp
        ${INCLUDE_DIR}/XmlDomReader.h)

add_executable(XmlQt ${PROJECT_SOURCES})

target_include_directories(XmlQt PRIVATE ${PROJECT_SOURCE_DIR}/include /usr/include/mono-2.0/)

target_link_libraries(XmlQt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Xml
        Qt6::Core5Compat
        mono-2.0
        -lm
        -lrt
        -ldl
        -lpthread
        )