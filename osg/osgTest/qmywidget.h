#ifndef QMYWIDGET_H
#define QMYWIDGET_H

#include <QOpenGLWidget>
#include <osgViewer/Viewer>

class AdapterWidget : public osgViewer::Viewer, public QOpenGLWidget
{
public:

  AdapterWidget(QWidget *parent = nullptr);
  virtual ~AdapterWidget();

  osgViewer::GraphicsWindow* getGraphicsWindow() { return _gw.get(); }
  const osgViewer::GraphicsWindow* getGraphicsWindow() const { return _gw.get(); }

protected:

  void init();

  virtual void resizeGL( int width, int height );
  virtual void paintGL();

  virtual void keyPressEvent( QKeyEvent* event );
  virtual void keyReleaseEvent( QKeyEvent* event );
  virtual void mousePressEvent( QMouseEvent* event );
  virtual void mouseReleaseEvent( QMouseEvent* event );
  virtual void mouseMoveEvent( QMouseEvent* event );

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _gw;
};


#endif // QMYWIDGET_H
