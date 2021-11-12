cmake_minimum_required(VERSION 3.20)
project(XmlQt)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(FetchContent)
FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum
        GIT_TAG 5bc2689fa5dbfe543b70b87fc63b0d3bdaef963d
)

FetchContent_MakeAvailable(magic_enum)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        Core5Compat
        REQUIRED)

find_package(LibXml2 REQUIRED)
find_package(LibXslt REQUIRED)

# Compile CSharp code that will be embedded
add_custom_target(LinqToXmlCSharp ALL
        COMMAND mcs -out:${PROJECT_SOURCE_DIR}/Embedded/LinqToXml.dll
            /reference:System.Xml.Linq
        ${PROJECT_SOURCE_DIR}/Embedded/LinqToXml.cs
        COMMENT "Compiling CSharp code..."
        VERBATIM
        )

set(PROJECT_SOURCES
        src/main.cpp
        src/XmlSaxFilterer.cpp
        include/XmlSaxFilterer.h
        include/Service.h
        src/Service.cpp
        src//XmlDomFilterer.cpp
        include/XmlDomFilterer.h
        src/XmlLinqFilterer.cpp
        include/XmlLinqFilterer.h
        src/MainWindow.cpp
        include/MainWindow.h
        src/ComboBoxPopulator.cpp
        include/ComboBoxPopulator.h
        include/XmlFiltererStrategy.h)

add_executable(XmlQt ${PROJECT_SOURCES})

target_include_directories(XmlQt PRIVATE ${PROJECT_SOURCE_DIR}/include /usr/include/mono-2.0/
        ${LIBXSLT_INCLUDE_DIRS} ${LIBXML2_INCLUDE_DIRS})

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
        ${LIBXML2_LIBRARIES}
        ${LIBXSLT_LIBRARIES}
        )

target_compile_definitions(XmlQt PRIVATE PROJECT_DIRECTORY="${PROJECT_SOURCE_DIR}" ${LIBXML2_DEFINITIONS} ${LIBXSLT_DEFINITIONS})