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
	int m_nBigRadius;   // ¥Û‘≤∞Îæ∂

	int m_nMidRadius;   // ÷–µ»‘≤∞Îæ∂
	int m_nMidSpace;    // ÷–µ»‘≤øø±ﬂæ‡¿Î

	int m_nLitRadius;   // –°‘≤∞Îæ∂
	int m_nLitSpace;    // –°‘≤øø±ﬂæ‡¿Î

	int m_nPersonWid;   // »ÀøÌ∂»
	int m_nPersonSpace;    // »Àøø±ﬂæ‡¿Î

	float m_fBigAngle;
	float m_fMidAngle;
	float m_fLitAngle;

	int m_nTimerId;
};

#endif // QMIGUANWIDGET_H
