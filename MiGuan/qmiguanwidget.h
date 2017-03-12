#ifndef QMIGUANWIDGET_H
#define QMIGUANWIDGET_H

#include <QtWidgets/QWidget>

class QMiGuanWidget : public QWidget
{
	Q_OBJECT

public:
	QMiGuanWidget(QWidget *parent = 0);
	~QMiGuanWidget();

protected:
	virtual void resizeEvent(QResizeEvent *) override;
	virtual void paintEvent(QPaintEvent *) override;
	virtual void timerEvent(QTimerEvent *) override;

	void drawMidCircle(QPainter &, QPoint &, int);
	void drawLitCircle(QPainter &, QPoint &, int);
	void drawPerson(QPainter &, QPoint &, int);

private:
	int m_nBigRadius;   // ��Բ�뾶

	int m_nMidRadius;   // �е�Բ�뾶
	int m_nMidSpace;    // �е�Բ���߾���

	int m_nLitRadius;   // СԲ�뾶
	int m_nLitSpace;    // СԲ���߾���

	int m_nPersonWid;   // �˿��
	int m_nPersonSpace;    // �˿��߾���

	float m_fBigAngle;
	float m_fMidAngle;
	float m_fLitAngle;

	int m_nTimerId;
};

#endif // QMIGUANWIDGET_H
