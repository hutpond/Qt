#include "qmywindow.h"

#include <QPainter>
#include <QVector3D>
#include <QDebug>

QMyWindow::QMyWindow()
    :QRasterWindow(), _timerid(0)
{
    m_view.lookAt(QVector3D(1, 1, 5), QVector3D(1,1,0), QVector3D(0,1,0));

    m_projection.setToIdentity();
    m_projection.perspective(45.f, 1.f, 1.f, 200.f);
    //m_projection.frustum(-2, 2, -2, 2, 5, 200);
    //m_projection.ortho(-1, 1, -1, 1, 1, 200);

    m_model.setToIdentity();
    m_model2.setToIdentity();
    m_model2.rotate(-90, 0, 1, 0);
    m_model3.setToIdentity();
    m_model3.rotate(90, 1, 0, 0);

    path.moveTo(0, 0);
    path.lineTo(0, 2);
    path.lineTo(2, 2);
    path.lineTo(2, 0);
    path.closeSubpath();

    int pos = 2;
    pt11 = QVector3D(0, 0, 0);
    pt12 = QVector3D(0, pos, 0);
    pt13 = QVector3D(pos, pos, 0);
    pt14 = QVector3D(pos, 0, 0);

    pt21 = QVector3D(0, 0, 0);
    pt22 = QVector3D(0, 0, pos);
    pt23 = QVector3D(pos, 0, pos);
    pt24 = QVector3D(pos, 0, 0);

    pt31 = QVector3D(0, 0, 0);
    pt32 = QVector3D(0, pos, 0);
    pt33 = QVector3D(0, pos, pos);
    pt34 = QVector3D(0, 0, pos);

    _timerid = startTimer(300);
}

QMyWindow::~QMyWindow()
{
    if (_timerid != 0)
    {
        killTimer(_timerid);
        _timerid = 0;
    }
}

void QMyWindow::resizeEvent(QResizeEvent *)
{
    m_tr.setToIdentity();
    m_tr.translate(200, 200);
    m_tr.scale(100, 100);
}

void QMyWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(0, 0, this->width(), this->height(), Qt::gray);

    QLinearGradient gradient(QPointF(-1,-1), QPointF(1,1));
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1, Qt::green);

    painter.setWorldTransform(m_tr.toTransform());
    QMatrix4x4 mt = m_projection * m_view * m_model;

    QVector3D _pt11 = mt.map(pt11);
    QVector3D _pt12 = mt.map(pt12);
    QVector3D _pt13 = mt.map(pt13);
    QVector3D _pt14 = mt.map(pt14);
    float min1 = qMin(qMin(_pt11.z(), _pt12.z()), qMin(_pt13.z(), _pt14.z()));

    QVector3D _pt21 = mt.map(pt21);
    QVector3D _pt22 = mt.map(pt22);
    QVector3D _pt23 = mt.map(pt23);
    QVector3D _pt24 = mt.map(pt24);
    float min2 = qMin(qMin(_pt21.z(), _pt22.z()), qMin(_pt23.z(), _pt24.z()));

    QVector3D _pt31 = mt.map(pt31);
    QVector3D _pt32 = mt.map(pt32);
    QVector3D _pt33 = mt.map(pt33);
    QVector3D _pt34 = mt.map(pt34);
    float min3 = qMin(qMin(_pt31.z(), _pt32.z()), qMin(_pt33.z(), _pt34.z()));

    QPainterPath _path;
    _path.moveTo(_pt11.x(), _pt11.y());
    _path.lineTo(_pt12.x(), _pt12.y());
    _path.lineTo(_pt13.x(), _pt13.y());
    _path.lineTo(_pt14.x(), _pt14.y());
    _path.closeSubpath();

    QPainterPath _path2;
    _path2.moveTo(_pt21.x(), _pt21.y());
    _path2.lineTo(_pt22.x(), _pt22.y());
    _path2.lineTo(_pt23.x(), _pt23.y());
    _path2.lineTo(_pt24.x(), _pt24.y());
    _path2.closeSubpath();

    QPainterPath _path3;
    _path3.moveTo(_pt31.x(), _pt31.y());
    _path3.lineTo(_pt32.x(), _pt32.y());
    _path3.lineTo(_pt33.x(), _pt33.y());
    _path3.lineTo(_pt34.x(), _pt34.y());
    _path3.closeSubpath();

    //qDebug() << _pt11.z() << _pt12.z() << _pt13.z() << _pt14.z();
    //qDebug() << _pt21.z() << _pt22.z() << _pt23.z() << _pt24.z();
    //qDebug() << _pt31.z() << _pt32.z() << _pt33.z() << _pt34.z();

    qDebug() << min1 << min2 << min3;

    if (min1 > min2)
    {
        if(min2 > min3)
        {
            painter.fillPath(_path, Qt::red);
            painter.fillPath(_path2, Qt::blue);
            painter.fillPath(_path3, Qt::green);
        }
        else
        {
            painter.fillPath(_path, Qt::red);
            painter.fillPath(_path3, Qt::green);
            painter.fillPath(_path2, Qt::blue);
        }
    }
    else if (min2 > min3)
    {
        if(min1 > min3)
        {
            painter.fillPath(_path2, Qt::blue);
            painter.fillPath(_path, Qt::red);
            painter.fillPath(_path3, Qt::green);
        }
        else
        {
            painter.fillPath(_path2, Qt::blue);
            painter.fillPath(_path3, Qt::green);
            painter.fillPath(_path, Qt::red);
        }
    }
    else
    {
        if(min1 > min2)
        {
            painter.fillPath(_path3, Qt::green);
            painter.fillPath(_path, Qt::red);
            painter.fillPath(_path2, Qt::blue);
        }
        else
        {
            painter.fillPath(_path3, Qt::green);
            painter.fillPath(_path2, Qt::blue);
            painter.fillPath(_path, Qt::red);
        }
    }

    /*painter.setWorldTransform(m_tr.toTransform());
    QMatrix4x4 mvp =  m_projection * m_view * m_model;
    painter.setTransform(mvp.toTransform(), true);
    painter.fillPath(path, Qt::red);

    painter.setWorldTransform(m_tr.toTransform());
    mvp =  m_projection * m_view * m_model2;
    painter.setTransform(mvp.toTransform(), true);
    painter.fillPath(path, Qt::blue);

    painter.setWorldTransform(m_tr.toTransform());
    mvp =  m_projection * m_view * m_model3;
    painter.setTransform(mvp.toTransform(), true);
    painter.fillPath(path, Qt::green);*/
}

void QMyWindow::timerEvent(QTimerEvent *)
{
    m_view.rotate(10, 1, 0, 0);
    update();
}
