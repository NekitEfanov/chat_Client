cmake_minimum_required(VERSION 3.5)

project(Qt5Client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui Network REQUIRED)

set( INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include )
set( SRC_DIR ${CMAKE_SOURCE_DIR}/src )

include_directories( ${INCLUDE_DIR} )

file( GLOB HEADERS "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp" "${INCLUDE_DIR}/*.ui" )
file( GLOB FORMS "${INCLUDE_DIR}/*.ui" )
file( GLOB SOURCES "${SRC_DIR}/*.c" "${SRC_DIR}/*.cpp" )

set( PROJECT_SOURCES ${SOURCES} ${HEADERS} ${FORMS} )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Qt5Client
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Qt5Client SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Qt5Client
            ${PROJECT_SOURCES}
        )
    endif()
endif()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
target_link_libraries(Qt5Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)
