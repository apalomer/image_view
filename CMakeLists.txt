# Minimum CMAKE version
cmake_minimum_required (VERSION 3.0)
project (image_view LANGUAGES CXX)

# Check that it is windows
if (NOT MSVC)
  message(FATAL_ERROR "This project can only be compiled with MSVC")
endif()

# Version
set(IMAGE_VIEW_MAJOR_VERSION 0)
set(IMAGE_VIEW_MINOR_VERSION 1)
set(IMAGE_VIEW_PATCH_VERSION 0)
set(IMAGE_VIEW_VERSION ${IMAGE_VIEW_MAJOR_VERSION}.${IMAGE_VIEW_MINOR_VERSION}.${IMAGE_VIEW_PATCH_VERSION})
message(STATUS "${PROJECT_NAME} version ${IMAGE_VIEW_VERSION}")
string(TIMESTAMP TODAY "%Y-%m-%d")
message(STATUS "Today: ${TODAY}")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up installer
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/installer/packages/com.vendor.image_view/data")

################################################
# DEPENDENCIES OF THE LIBRARY
################################################

# Qt 5
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#################################################
# Code
#################################################
add_library(image_view_widget SHARED src/image_view.cpp src/image_view.h src/image_view.ui src/image_view_exports.h src/qt_resources.qrc)
target_compile_definitions(image_view_widget PRIVATE IMAGE_VIEW)
target_link_libraries(image_view_widget Qt5::Core Qt5::Widgets)

add_executable(image_view WIN32 src/main.cpp)
target_link_libraries(image_view image_view_widget)

install(TARGETS image_view_widget image_view
  EXPORT ImageViewTargets
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}" COMPONENT shlib
  COMPONENT dev)

if(CMAKE_INSTALL_PREFIX MATCHES "${CMAKE_SOURCE_DIR}/installer/packages/com.vendor.image_view/data")
  # Configure files
  set(ApplicationsDirX64 "@ApplicationsDirX64@")
  configure_file("${CMAKE_SOURCE_DIR}/installer/config/config.xml.in" "${CMAKE_SOURCE_DIR}/installer/config/config.xml" @ONLY)
  configure_file("${CMAKE_SOURCE_DIR}/installer/packages/com.vendor.image_view/meta/package.xml.in" "${CMAKE_SOURCE_DIR}/installer/packages/com.vendor.image_view/meta/package.xml" @ONLY)
  configure_file("${CMAKE_SOURCE_DIR}/installer/packages/com.vendor.image_view_data/meta/package.xml.in" "${CMAKE_SOURCE_DIR}/installer/packages/com.vendor.image_view_data/meta/package.xml" @ONLY)
  
  # Run windeploy qt
  install(CODE "MESSAGE(\"Running windeployqt ${CMAKE_INSTALL_PREFIX}\")")
  install(CODE "execute_process(COMMAND windeployqt \"${CMAKE_INSTALL_PREFIX}\")")

  # Run qt installer framework generator
  install(CODE "MESSAGE(\"Generating installer with qt framework (make sure binarycreator from QtInstallerFramework is added to the path)\")")
  install(CODE "execute_process(COMMAND binarycreator -c \"${CMAKE_SOURCE_DIR}/installer/config/config.xml\" -p \"${CMAKE_SOURCE_DIR}/installer/packages\" \"${CMAKE_SOURCE_DIR}/installer/ImageViewInstaller_${IMAGE_VIEW_VERSION}_windows_${CMAKE_HOST_SYSTEM_PROCESSOR}\")")
endif()