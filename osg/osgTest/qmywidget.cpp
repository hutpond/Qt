#include "qmywidget.h"

#include <QKeyEvent>

AdapterWidget::AdapterWidget( QWidget *parent):
  QOpenGLWidget(parent)
{
  _gw = new osgViewer::GraphicsWindowEmbedded(0,0,width(),height());
  setFocusPolicy(Qt::ClickFocus);

  getCamera()->setViewport(new osg::Viewport(0,0,width(),height()));
  getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width())/static_cast<double>(height()), 1.0f, 10000.0f);
  getCamera()->setGraphicsContext(getGraphicsWindow());

  osgViewer::Viewer::setThreadingModel(osgViewer::Viewer::SingleThreaded);
}

AdapterWidget::~AdapterWidget()
{

}

void AdapterWidget::resizeGL( int width, int height )
{
  _gw->getEventQueue()->windowResize(0, 0, width, height );
  _gw->resized(0,0,width,height);
}

void AdapterWidget::paintGL()
{
  osgViewer::Viewer::frame();
}

void AdapterWidget::keyPressEvent( QKeyEvent* event )
{
  _gw->getEventQueue()->keyPress( (osgGA::GUIEventAdapter::KeySymbol) *(event->text().toLatin1().data() ) );
}

void AdapterWidget::keyReleaseEvent( QKeyEvent* event )
{
  _gw->getEventQueue()->keyRelease( (osgGA::GUIEventAdapter::KeySymbol) *(event->text().toLatin1().data() ) );
}

void AdapterWidget::mousePressEvent( QMouseEvent* event )
{
  int button = 0;
  switch(event->button())
  {
    case(Qt::LeftButton): button = 1; break;
    case(Qt::MidButton): button = 2; break;
    case(Qt::RightButton): button = 3; break;
    case(Qt::NoButton): button = 0; break;
    default: button = 0; break;
  }
  _gw->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
  update();
}

void AdapterWidget::mouseReleaseEvent( QMouseEvent* event )
{
  int button = 0;
  switch(event->button())
  {
    case(Qt::LeftButton): button = 1; break;
    case(Qt::MidButton): button = 2; break;
    case(Qt::RightButton): button = 3; break;
    case(Qt::NoButton): button = 0; break;
    default: button = 0; break;
  }
  _gw->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);
  update();
}

void AdapterWidget::mouseMoveEvent( QMouseEvent* event )
{
  _gw->getEventQueue()->mouseMotion(event->x(), event->y());
}
