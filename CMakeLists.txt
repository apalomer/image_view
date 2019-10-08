# Minimum CMAKE version
cmake_minimum_required (VERSION 3.0)
project (image_view LANGUAGES CXX)

# Version
set(IMAGE_VIEW_MAJOR_VERSION 0)
set(IMAGE_VIEW_MINOR_VERSION 1)
set(IMAGE_VIEW_PATCH_VERSION 0)
set(IMAGE_VIEW_VERSION ${IMAGE_VIEW_MAJOR_VERSION}.${IMAGE_VIEW_MINOR_VERSION}.${IMAGE_VIEW_PATCH_VERSION})
message(STATUS "${PROJECT_NAME} version ${IMAGE_VIEW_VERSION}")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

################################################
# DEPENDENCIES OF THE LIBRARY
################################################

# Qt 5
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#################################################
# Code
#################################################
add_library(image_view_widget SHARED src/image_view.cpp src/image_view.h src/image_view.ui src/image_view_exports.h)
target_compile_definitions(image_view_widget PRIVATE IMAGE_VIEW)
target_link_libraries(image_view_widget Qt5::Core Qt5::Widgets ${OpenCV_LIBS})

add_executable(image_view src/main.cpp)
target_link_libraries(image_view image_view_widget)