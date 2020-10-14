#define WindowWidth  400
#define WindowHeight 400
#define WindowTitle  "Texture"

#include <GL/glut.h>
#include <memory>

#include <opencv2/opencv.hpp>

//定义两个纹理对象编号
GLuint texGround;
GLuint texWall;

#define BMP_Header_Length 54  //图像数据在内存块中的偏移量
static GLfloat angle = 0.0f;   //旋转角度

// 函数power_of_two用于判断一个整数是不是2的整数次幂
int power_of_two(int n)
{
  if( n <= 0 )
    return 0;
  return (n & (n-1)) == 0;
}

/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(const char* file_name)
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
    if( !power_of_two(width)
        || !power_of_two(height)
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

void display(void)
{
  // 清除屏幕
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // 设置视角
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(75, 1, 1, 21);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-4, 7,7, 0, 0, 0, 0, 0, 1);

  glRotatef(angle, 0.0f, 0.0f, 1.0f); //旋转

  // 绘制底面以及纹理
  glBindTexture(GL_TEXTURE_2D, texGround);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);
  glTexCoord2f(0.0f, 3.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
  glTexCoord2f(3.0f, 3.0f); glVertex3f(8.0f, 8.0f, 0.0f);
  glTexCoord2f(3.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
  glEnd();
  // 绘制立面
  glBindTexture(GL_TEXTURE_2D, texWall);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 5.0f);
  glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);
  glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
  glEnd();

  //绘制另外一个立面
  glBegin(GL_QUADS);
  glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(6.0f, 9.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(6.0f, 9.0f, 5.0f);
  glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);
  glEnd();

  glutSwapBuffers();
}

void myIdle(void)
{
  angle += 0.1f;
  if( angle >= 360.0f )
    angle = 0.0f;
  display();
}

int main(int argc, char* argv[])
{
  // GLUT初始化
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(WindowWidth, WindowHeight);
  glutCreateWindow(WindowTitle);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);    // 启用纹理
  texGround = load_texture("image/1.jpg");  //加载纹理
  texWall = load_texture("image/2.jpg");
  glutDisplayFunc(&display);   //注册函数
  glutIdleFunc(&myIdle);
  glutMainLoop(); //循环调用
  return 0;
}
