#include "QShowWidget.h"

#include <cmath>

//#define GLEW_STATIC
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <opencv2/opencv.hpp>
//#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <QMouseEvent>

QShowWidget::QShowWidget(QWidget *parent)
  : QOpenGLWidget(parent)
{
  capture_ = cv::VideoCapture(0);
  tiemr_id = startTimer(100);
}

QShowWidget::~QShowWidget()
{
  killTimer(tiemr_id);
}

void QShowWidget::initializeGL()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  for (int i = 0; i < 6; ++i) {
    std::string fileName = "image/" +
        std::to_string(i + 1) + ".jpg";
    texture_[i] = loadTexture(fileName);
  }
}

void QShowWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void QShowWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glReadBuffer(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glDepthFunc(GL_LESS);
  glShadeModel(GL_SMOOTH);
//  glEnable(GL_LIGHTING);
//  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);   //开启法向量规范化

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  double vehicle_x = 5;
  double vehicle_y = 5;
//  double vehicle_z = 5;

  double radius = 20;
  float width = 10;
  float ratio = (float)this->height() / this->width();
//  float height = width * ratio;

  // project
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  double rangle = 80;
  bool ortho = false;
  if (ortho) {
    glOrtho(vehicle_x - rangle,
            vehicle_x + rangle,
            vehicle_y - rangle * ratio,
            vehicle_y + rangle * ratio,
            -5 * radius, 20 * radius);
  }
  else {
    gluPerspective(45, 1.0 / ratio, 1, 100);
    gluLookAt(
          7.5, 7.5 * ratio, 100.0,
          7.5, 7.5 * ratio, 0.0,
          0.0, 1.0, 0.0
          );
  }

  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };        //设置全局环境光
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
  GLfloat Kc = 1.0;
  GLfloat Kl = 0.0;
  GLfloat Kq = 0.0;
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);

  GLfloat light_pos[] = {0.0f,0.0f,1.0f,0.0f};     //采用方向光源
  GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
  GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
  GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

  glPushMatrix();
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glPopMatrix();
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

  GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};      //材质特性
  GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
  GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
  GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
  GLfloat material_Se = 20.0f;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);

  drawCubeTexture2();
}

void QShowWidget::drawCube()
{
  double cx = 18;
  double cy = 18;
  double cz = 18;

  glTranslatef(cx / 2, cy / 2, cz / 2);

  glRotatef( x_rot_, 1.0, 0.0, 0.0 );
  glRotatef( y_rot_, 0.0, 1.0, 0.0 );
  glRotatef( z_rot_, 0.0, 0.0, 1.0 );


  glBegin(GL_QUADS);
  // 左面
  glColor3f(1.0, 0.0, 0);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f(-cx,  cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(-cx,  cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, -cy,  cz);
  // 右面
  glColor3f(0.0, 1.0, 0);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f(cx,  cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(cx,  cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(cx, -cy,  cz);

  // 前面
  glColor3f(0.0, 0.0, 1.0);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx, cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, cy,  cz);
  // 后面
  glColor3f(1.0, 1.0, 0.0);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, -cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx, -cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, -cy,  cz);

  // 下面
  glColor3f(1.0, 0.0, 1.0);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, -cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx,  cy, -cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx,  cy, -cz);
  // 上面
  glColor3f(0.0, 1.0, 1.0);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, -cy, cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx,  cy, cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx,  cy, cz);
  glEnd();

  glTranslatef(-cx / 2, -cy / 2, -cz / 2);
}

void QShowWidget::mousePressEvent(QMouseEvent *e)
{
  last_pos_ = e->localPos();
  mpressed_ = true;
}

void QShowWidget::mouseMoveEvent(QMouseEvent *e)
{
  if (!mpressed_) {
    e->ignore();
    return;
  }

  QPointF diff = e->localPos() - last_pos_;
  double w = qMax<double>(1,width());
  double h = qMax<double>(1,height());

  double accel = 1.5;
  double relx = accel*360 * diff.x() / w;
  double relyz = accel*360 * diff.y() / h;

  x_rot_ = std::fmod(round(x_rot_ + relyz), 360);
  y_rot_ = std::fmod(round(y_rot_ + relx), 360);
  z_rot_ = std::fmod(round(z_rot_ + relx), 360);

  this->update();

  last_pos_ = e->pos();
}

/**
 * @brief 绘制纹理
 */
void QShowWidget::drawCubeTexture()
{
  double cx = 18;
  double cy = 18;
  double cz = 18;

  glTranslatef(cx / 2, cy / 2, cz / 2);

  glRotatef( x_rot_, 1.0, 0.0, 0.0 );
  glRotatef( y_rot_, 0.0, 1.0, 0.0 );
  glRotatef( z_rot_, 0.0, 0.0, 1.0 );

  // 左面
  glBindTexture(GL_TEXTURE_2D, texture_[0]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f(-cx,  cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(-cx,  cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, -cy,  cz);
  glEnd();
  // 右面
  glBindTexture(GL_TEXTURE_2D, texture_[1]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f(cx,  cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(cx,  cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(cx, -cy,  cz);
  glEnd();

  // 前面
  glBindTexture(GL_TEXTURE_2D, texture_[2]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx, cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, cy,  cz);
  glEnd();
  // 后面
  glBindTexture(GL_TEXTURE_2D, texture_[3]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, -cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx, -cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, -cy,  cz);
  glEnd();

  // 下面
  glBindTexture(GL_TEXTURE_2D, texture_[4]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, -cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx,  cy, -cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx,  cy, -cz);
  glEnd();
  // 上面
  glBindTexture(GL_TEXTURE_2D, texture_[5]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, -cy, cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx,  cy, cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx,  cy, cz);
  glEnd();

//  glutSwapBuffers();

  glTranslatef(-cx / 2, -cy / 2, -cz / 2);
}

/**
 * @brief 绘制纹理
 */
void QShowWidget::drawCubeTexture2()
{
  double cx = 18;
  double cy = 18;
  double cz = 18;

  glTranslatef(cx / 2, cy / 2, cz / 2);

  glRotatef( x_rot_, 1.0, 0.0, 0.0 );
  glRotatef( y_rot_, 0.0, 1.0, 0.0 );
  glRotatef( z_rot_, 0.0, 0.0, 1.0 );

  cv::Mat frame;
  capture_ >> frame;
  cv::imwrite("/tmp/1.jpg", frame);

  GLuint texture = loadTexture("/tmp/1.jpg");

  // 左面
  glBindTexture(GL_TEXTURE_2D, texture);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f(-cx,  cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(-cx,  cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, -cy,  cz);
  glEnd();
  // 右面
  glBindTexture(GL_TEXTURE_2D, texture);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f(cx,  cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(cx,  cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(cx, -cy,  cz);
  glEnd();

  // 前面
  glBindTexture(GL_TEXTURE_2D, texture);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx, cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, cy,  cz);
  glEnd();
  // 后面
  glBindTexture(GL_TEXTURE_2D, texture);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, -cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx, -cy,  cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx, -cy,  cz);
  glEnd();

  // 下面
  glBindTexture(GL_TEXTURE_2D, texture);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, -cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, -cy, -cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx,  cy, -cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx,  cy, -cz);
  glEnd();
  // 上面
  glBindTexture(GL_TEXTURE_2D, texture);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-cx, -cy, cz);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f( cx, -cy, cz);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f( cx,  cy, cz);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-cx,  cy, cz);
  glEnd();

//  glutSwapBuffers();

  glTranslatef(-cx / 2, -cy / 2, -cz / 2);
}

void QShowWidget::timerEvent(QTimerEvent *)
{
  this->update();
}

/**
 * @brief 判断数字是否2的幂函数
 * @param n
 * @return
 */
bool QShowWidget::powerOfTwo(int n)
{
  if( n <= 0 )
    return false;
  return (n & (n-1)) == 0;
}

/**
 * @brief 读取图片文件并创建纹理
 * @param file_name
 * @return
 */
GLuint QShowWidget::loadTexture(const std::string &file_name)
{
  GLint width, height, total_bytes;
  std::shared_ptr<GLubyte> pixels;
  GLuint last_texture_ID=0, texture_ID = 0;

  cv::Mat image = cv::imread(file_name);

  width = image.cols;
  height = image.rows;
  while( width % 4 != 0 )
    ++width;

  {
    GLint line_bytes = width * 3;
    while( line_bytes % 4 != 0 )
      ++line_bytes;
    total_bytes = line_bytes * height;
  }
  pixels.reset(new GLubyte[total_bytes]);
  int index = 0;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      pixels.operator ->()[index ++] = image.at<cv::Vec3b>(i, j)[0];
      pixels.operator ->()[index ++] = image.at<cv::Vec3b>(i, j)[1];
      pixels.operator ->()[index ++] = image.at<cv::Vec3b>(i, j)[2];
    }
  }

  // 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
  // 若图像宽高超过了OpenGL规定的最大值，也缩放
  {
    GLint max;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
    if( !powerOfTwo(width)
        || !powerOfTwo(height)
        || width > max
        || height > max )
    {
      const GLint new_width = 256;
      const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
      GLint new_line_bytes, new_total_bytes;
      std::shared_ptr<GLubyte> new_pixels;

      // 计算每行需要的字节数和总字节数
      new_line_bytes = new_width * 3;
      while( new_line_bytes % 4 != 0 )
        ++new_line_bytes;
      new_total_bytes = new_line_bytes * new_height;

      // 分配内存
      new_pixels.reset(new GLubyte[new_total_bytes]);
      if( new_pixels == 0 )
      {
        return 0;
      }

      // 进行像素缩放
      gluScaleImage(
            GL_RGB,
            width, height, GL_UNSIGNED_BYTE,
            pixels.get(), new_width, new_height,
            GL_UNSIGNED_BYTE, new_pixels.get());

      // 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
      pixels = new_pixels;
      width = new_width;
      height = new_height;
    }
  }

  // 分配一个新的纹理编号
  glGenTextures(1, &texture_ID);
  if( texture_ID == 0 )
  {
    return 0;
  }

  // 绑定新的纹理，载入纹理并设置纹理参数
  // 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
  GLint lastTextureID=last_texture_ID;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
  glBindTexture(GL_TEXTURE_2D, texture_ID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
               GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels.get());
  glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
  return texture_ID;
}
