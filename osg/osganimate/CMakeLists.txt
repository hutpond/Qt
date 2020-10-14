cmake_minimum_required(VERSION 3.5)

project(osganimate LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/usr/local/osg/include)
link_directories(/usr/local/osg/lib)

set(Qt5_DIR /opt/Qt5.14.2/5.14.2/gcc_64/lib/cmake/Qt5)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(osganimate
      main.cpp
      QAnimateWidget.cpp
      QAnimateWidget.h
  )

target_link_libraries(osganimate PRIVATE Qt5::Widgets)
target_link_libraries(osganimate PRIVATE osgDB)
target_link_libraries(osganimate PRIVATE osgUtil)
target_link_libraries(osganimate PRIVATE osg)
target_link_libraries(osganimate PRIVATE osgText)
target_link_libraries(osganimate PRIVATE osgViewer)
target_link_libraries(osganimate PRIVATE osgGA)
target_link_libraries(osganimate PRIVATE osgSim)
target_link_libraries(osganimate PRIVATE pthread)
