#include <QApplication>

#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

#include "qmywidget.h"

int main( int argc, char *argv[])
{
  QApplication a( argc, argv );

  osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile("lz.osg");

  AdapterWidget* viewerWindow = new AdapterWidget;
  viewerWindow->setCameraManipulator(new osgGA::TrackballManipulator);
  viewerWindow->setSceneData(loadedModel.get());
  viewerWindow->show();

  return a.exec();
}
