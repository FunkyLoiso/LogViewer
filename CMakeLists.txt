cmake_minimum_required(VERSION 3.1.0)

project(LogViewer VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(
  Qt5 
  COMPONENTS Core Gui Widgets 
  REQUIRED
)

file(GLOB HEADER_FILES *.h)
file(GLOB SRC_FILES *.cpp)
file(GLOB QT_FILES *.ui *.qrc)

source_group("Header Files" FILES ${HEADER_FILES})

add_executable(
  ${PROJECT_NAME}
    ${SRC_FILES}
    ${HEADER_FILES}
    ${QT_FILES}
)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_link_libraries(
  ${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

if(WIN32)
  add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin>
      $<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms/
)
ENDIF()