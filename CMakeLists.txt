cmake_minimum_required(VERSION 3.5)

project(MXKJ_Detection VERSION 0.1 LANGUAGES CXX)

# 输出项目名称和当前平台/架构信息
message(STATUS "Project Name: " ${PROJECT_NAME})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "HOME_DIR: $ENV{HOME}")

# 判断某个字符串是否在变量中
IF("$ENV{HOME}" MATCHES "Spring")
    set(THIRD_PARTY_LIB_PATH "E:\\share\\runtime\\win")
ELSE()
    # 设置其他路径
    set(THIRD_PARTY_LIB_PATH "C:\\Code\\runtime")
ENDIF()


# OpenCV
set(OpenCV_DIR "${THIRD_PARTY_LIB_PATH}\\opencv\\build")
# FastDeploy
 set(FastDeploy_DIR "${THIRD_PARTY_LIB_PATH}/fastdeploy-win-x64-gpu")
 # CUDA
 set(CUDA_DIRECTORY "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.8")
 #ncnn
 set(ncnn_DIR "${THIRD_PARTY_LIB_PATH}\\ncnn\\x64\\lib\\cmake\\ncnn")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# find_package(OpenCV REQUIRED)
find_package(FastDeploy REQUIRED)
find_package(ncnn REQUIRED)


include_directories("C:\\Code\\runtime\\ncnn\\x64\\include\\ncnn")
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ccamera.h ccamera.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ccamera.h ccamera.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)

        add_library(${PROJECT_NAME} SHARED

            ${PROJECT_SOURCES}
        )
# Define properties forA Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets )
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FastDeploy_LIBS}) # 添加FastDeploy库依赖
target_link_libraries(${PROJECT_NAME} PRIVATE ncnn)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME})
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
