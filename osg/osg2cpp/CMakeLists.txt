cmake_minimum_required(VERSION 3.5)

project(osg2cpp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/usr/local/osg/include)
link_directories(/usr/local/osg/lib)

set(Qt5_DIR /opt/Qt5.12.4/5.12.4/gcc_64/lib/cmake/Qt5)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(osg2cpp
      osg2cpp.cpp
  )

target_link_libraries(osg2cpp PRIVATE Qt5::Widgets)
target_link_libraries(osg2cpp PRIVATE osgDB)
target_link_libraries(osg2cpp PRIVATE osgUtil)
target_link_libraries(osg2cpp PRIVATE osg)
target_link_libraries(osg2cpp PRIVATE osgText)
target_link_libraries(osg2cpp PRIVATE osgViewer)
target_link_libraries(osg2cpp PRIVATE osgGA)
