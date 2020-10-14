#ifndef QANIMATEWIDGET_H
#define QANIMATEWIDGET_H

#include <QOpenGLWidget>
#include <osgViewer/Viewer>
#include <osgSim/OverlayNode>
#include <osg/AnimationPath>

#include <thread>

class QAnimateWidget : public QOpenGLWidget, public osgViewer::Viewer
{
  Q_OBJECT
public:
  explicit QAnimateWidget(QWidget *);

protected:
  virtual void initializeGL() final;
  virtual void resizeGL(int, int) final;
  virtual void paintGL() final;

  virtual void keyPressEvent(QKeyEvent *);
  virtual void keyReleaseEvent(QKeyEvent *);
  virtual void mousePressEvent(QMouseEvent *);
  virtual void mouseReleaseEvent(QMouseEvent *);
  virtual void mouseMoveEvent(QMouseEvent *);

  osg::ref_ptr<osg::Group> createModel(bool, osgSim::OverlayNode::OverlayTechnique);
  osg::Node* createBase(const osg::Vec3 &, float);
  osg::AnimationPath* createAnimationPath(const osg::Vec3 &, float, double);
  osg::Node* createMovingModel(const osg::Vec3 &, float);

  osgViewer::GraphicsWindow* getGraphicsWindow() { return _gw.get(); }
  const osgViewer::GraphicsWindow* getGraphicsWindow() const { return _gw.get(); }

private:
  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _gw;
};

#endif // QANIMATEWIDGET_H
