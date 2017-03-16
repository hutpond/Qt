#ifndef QMYWINDOW_H
#define QMYWINDOW_H

#include <QRasterWindow>
#include <QMatrix4x4>

class QMyWindow : public QRasterWindow
{
public:
    QMyWindow();
    ~QMyWindow();

protected:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void timerEvent(QTimerEvent *) override;
    virtual void resizeEvent(QResizeEvent *) override;

private:
    QPainterPath path;

    QVector3D pt11, pt12, pt13, pt14;
    QVector3D pt21, pt22, pt23, pt24;
    QVector3D pt31, pt32, pt33, pt34;

    QMatrix4x4 m_tr;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QMatrix4x4 m_model;
    QMatrix4x4 m_model2;
    QMatrix4x4 m_model3;

    int _timerid;
};

#endif // QMYWINDOW_H
