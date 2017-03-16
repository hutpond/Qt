#include <QGuiApplication>
#include <QMatrix4x4>

#include "qmywindow.h"

void calcFrustum();

void calcLookat();

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QMyWindow w;
    w.setGeometry(300, 200, 600, 400);
    w.show();

    return a.exec();
}

void calcFrustum()
{
    float l = 0, r = 6;
    float b = 0, t = 6;
    float n = 6, f = 12;

    QMatrix4x4 mt(n, 0,      0,    0,
                  0, n,      0,    0,
                  0, 0, -(n+f), -n*f,
                  0, 0,    -1.,    0);

    QMatrix4x4 mt2(1, 0, 0, -(l+r)/2.,
                   0, 1, 0, -(b+t)/2.,
                   0, 0, 1, -(n+f)/2.,
                   0, 0, 0, 1);

    QMatrix4x4 mt3(2./(r-l), 0, 0, 0,
                   0, 2./(t-b), 0, 0,
                   0, 0, 2./(f-n), 0,
                   0, 0, 0, 1);

    QMatrix4x4 mt4 = mt3 * mt2 * mt;

    QMatrix4x4 mt6;
    mt6.scale(2./(r-l), 2./(t-b), 2./(f-n));
    mt6.translate(-(l+r)/2., -(b+t)/2., -(n+f)/2.);
    mt6 = mt6*mt;
    qDebug() << mt6;

    QMatrix4x4 mt5;
    mt5.frustum(l, r, b, t, n, f);

    qDebug() << "mt4" << mt4;
    qDebug() << "mt5" << mt5;
}

void showFrustum()
{
    QMatrix4x4 mt;
    mt.frustum(0, 6, 0, 10, 8, 16);
    QMatrix4x4 mt2;
    mt2.translate(2, 2, -6);
    mt = mt2 * mt;
    //qDebug() << mt;

    QVector3D vct(0, 0, 8);
    qDebug() << vct << mt.map(vct);
    vct = QVector3D(0, 5, 8);
    qDebug() << vct << mt.map(vct);
    vct = QVector3D(4, 0, 8);
    qDebug() << vct << mt.map(vct);
    vct = QVector3D(4, 5, 8);
    qDebug() << vct << mt.map(vct);

    vct = QVector3D(0, 0, 16);
    qDebug() << vct << mt.map(vct);
    vct = QVector3D(0, 20, 16);
    qDebug() << vct << mt.map(vct);
    vct = QVector3D(12, 0, 16);
    qDebug() << vct << mt.map(vct);
    vct = QVector3D(12, 20, 16);
    qDebug() << vct << mt.map(vct);
}

void calcLookat()
{
}
