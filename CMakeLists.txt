cmake_minimum_required(VERSION 3.22)
project(NewFrontiersEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(CMAKE_PREFIX_PATH "D:/Qt/5.15.2/mingw81_64/lib/cmake") ### CHANGE THIS PATH IF YOU ARE UNDER WINDOWS
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(CMAKE_PREFIX_PATH "/Users/$ENV{USER}/Qt/5.15.2/macos/lib/cmake") ### CHANGE THIS PATH IF YOU ARE UNDER MACOS
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_PREFIX_PATH "/home/$ENV{USER}/Qt/5.15.2/gcc_64/lib/cmake") ### CHANGE THIS PATH IF YOU ARE UNDER LINUX
endif()

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        OpenGL
        REQUIRED)

# Has to be seperate, because the first find_package only looks for Qt components
find_package(OpenGL REQUIRED)

# Include engine source code
include_directories(${CMAKE_SOURCE_DIR}/Engine/Source)

add_executable(NewFrontiersEngine Engine/Source/Editor/EditorCore/Private/main.cpp Engine/Source/Editor/OpenGL/Public/EditorOpenGLWidget.h Engine/Source/Editor/OpenGL/Private/EditorOpenGLWidget.cpp Engine/Source/Editor/EditorCore/Public/EditorMain.h Engine/Source/Editor/EditorCore/Private/EditorMain.cpp Engine/Source/Editor/EditorFramework/Public/EditorViewport.h Engine/Source/Editor/EditorFramework/Private/EditorViewport.cpp Engine/Source/Editor/EditorFramework/Public/EditorMenu.h Engine/Source/Editor/EditorFramework/Private/EditorMenu.cpp Engine/Source/Editor/EditorFramework/Public/EditorError.h Engine/Source/Editor/EditorFramework/Private/EditorError.cpp Engine/Source/Editor/General/nf_error.h Engine/Source/Runtime/RendererCore/Public/Shader.h Engine/Source/Runtime/RendererCore/Private/Shader.cpp)
target_link_libraries(NewFrontiersEngine
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::OpenGL
        ${OPENGL_LIBRARIES}
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()