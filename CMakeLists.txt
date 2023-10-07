cmake_minimum_required(VERSION 3.5)

project(SmartReckoner VERSION 0.1 LANGUAGES CXX)

# set(CMAKE_PREFIX_PATH "~/Qt/6.4.1/gcc_64")
# set(CMAKE_PREFIX_PATH "/Users/thedolaxom/Qt/6.4.1/macos/lib/cmake")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_compile_definitions(QT_MACRO)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PROJECT_ARCH_TARGET "amd64")    # x64
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PROJECT_ARCH_TARGET "i386")     # x86
else()
    message(FATAL_ERROR "Unkwnown architecture, CMake will exit.")
endif()

set(PROJECT_SOURCES
        view/main.cc
        view/application/reckoner.cc
        view/application/reckoner.h
        view/application/reckoner.ui
        model/model.h
        model/model.cc
        controller/controller.h
        controller/controller.cc
)

set(PROJECT_BUILD_OUTPUT ${CMAKE_SOURCE_DIR}/build/output/${PROJECT_ARCH_TARGET}/${CMAKE_BUILD_TYPE})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BUILD_OUTPUT}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/view/qcp)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/view/qcp)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/view/qcp)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartReckoner
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(SmartReckoner SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(SmartReckoner
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SmartReckoner PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(SmartReckoner PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SmartReckoner
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartReckoner)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE qcustomplot)

# Compile needed definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE QCUSTOMPLOT_USE_LIBRARY)

add_subdirectory(view/qcp)
