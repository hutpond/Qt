#ifndef QSHOWWIDGET_H
#define QSHOWWIDGET_H

#include <GL/glew.h>
#include <QOpenGLWidget>

class QShowWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  QShowWidget(QWidget *parent = nullptr);
  ~QShowWidget();

protected:
  virtual void initializeGL() final;
  virtual void resizeGL(int w, int h) final;
  virtual void paintGL() final;

  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);

  void drawCube();
  void drawCubeTexture();

  bool powerOfTwo(int);
  GLuint loadTexture(const std::string &);

private:
  QPointF last_pos_;
  bool mpressed_{false};

  double x_rot_{0.0};
  double y_rot_{0.0};
  double z_rot_{0.0};

  GLuint texture_[6];
};
#endif // QSHOWWIDGET_H
