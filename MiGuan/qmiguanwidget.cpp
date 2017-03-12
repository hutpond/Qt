#include "qmiguanwidget.h"

#include <QPainter>

#define PI 3.1415926

QMiGuanWidget::QMiGuanWidget(QWidget *parent)
: QWidget(parent), m_fBigAngle(0), m_fMidAngle(0), m_fLitAngle(0), m_nTimerId(0)
{
	m_nTimerId = startTimer(50);
}

QMiGuanWidget::~QMiGuanWidget()
{
	if (m_nTimerId != 0)
	{
		killTimer(m_nTimerId);
		m_nTimerId = 0;
	}
}

void QMiGuanWidget::resizeEvent(QResizeEvent *)
{

	m_nBigRadius = qMin(this->width(), this->height()) * 0.9 / 2;

	m_nMidRadius = m_nBigRadius * 0.38;
	m_nMidSpace = m_nBigRadius * 0.03;

	m_nLitRadius = m_nMidRadius * 0.27;
	m_nLitSpace = m_nMidRadius * 0.03;

	m_nPersonWid = m_nLitRadius * 0.4;
	m_nPersonSpace = m_nLitRadius * 0.03;
}

void QMiGuanWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	painter.save();
	painter.setPen(Qt::lightGray);
	painter.setBrush(Qt::lightGray);
	painter.drawEllipse(this->rect().center(), m_nBigRadius, m_nBigRadius);
	painter.restore();

	drawMidCircle(painter, this->rect().center(), m_fBigAngle);
	drawMidCircle(painter, this->rect().center(), m_fBigAngle + 90);
	drawMidCircle(painter, this->rect().center(), m_fBigAngle + 180);
	drawMidCircle(painter, this->rect().center(), m_fBigAngle + 270);
}

void QMiGuanWidget::drawMidCircle(QPainter & painter, QPoint & pt, int rotation)
{
	painter.save();
	QTransform tr;
	tr.translate(pt.x(), pt.y());
	tr.rotate(rotation);
	tr.translate(-m_nBigRadius, 0);
	painter.setTransform(tr);
	painter.setPen(Qt::yellow);
	painter.setBrush(Qt::yellow);
	painter.drawEllipse(QPoint(m_nMidRadius + m_nMidSpace, 0), m_nMidRadius, m_nMidRadius);

	drawLitCircle(painter, QPoint(m_nMidRadius + m_nMidSpace, 0), m_fMidAngle);
	drawLitCircle(painter, QPoint(m_nMidRadius + m_nMidSpace, 0), m_fMidAngle + 60);
	drawLitCircle(painter, QPoint(m_nMidRadius + m_nMidSpace, 0), m_fMidAngle + 120);
	drawLitCircle(painter, QPoint(m_nMidRadius + m_nMidSpace, 0), m_fMidAngle + 180);
	drawLitCircle(painter, QPoint(m_nMidRadius + m_nMidSpace, 0), m_fMidAngle + 240);
	drawLitCircle(painter, QPoint(m_nMidRadius + m_nMidSpace, 0), m_fMidAngle + 300);

	painter.restore();
}

void QMiGuanWidget::drawLitCircle(QPainter & painter, QPoint & pt, int rotation)
{
	painter.save();
	QTransform tr;
	tr.translate(pt.x(), pt.y());
	tr.rotate(rotation);
	tr.translate(-m_nMidRadius, 0);
	painter.setTransform(tr, true);
	painter.setPen(Qt::blue);
	painter.setBrush(Qt::blue);
	painter.drawEllipse(QPoint(m_nLitRadius + m_nLitSpace, 0), m_nLitRadius, m_nLitRadius);

	drawPerson(painter, QPoint(m_nLitRadius + m_nLitSpace, 0), m_fLitAngle);
	drawPerson(painter, QPoint(m_nLitRadius + m_nLitSpace, 0), m_fLitAngle + 120);
	drawPerson(painter, QPoint(m_nLitRadius + m_nLitSpace, 0), m_fLitAngle + 240);

	painter.restore();
}

void QMiGuanWidget::drawPerson(QPainter & painter, QPoint & pt, int rotation)
{
	painter.save();
	QTransform tr;
	tr.translate(pt.x(), pt.y());
	tr.rotate(rotation);
	tr.translate(-m_nLitRadius, 0);
	painter.setTransform(tr, true);
	painter.setPen(Qt::green);
	painter.setBrush(Qt::green);
	QRect rect(0, 0, m_nPersonWid, m_nPersonWid);
	rect.moveCenter(QPoint(m_nPersonWid / 2.0 + m_nPersonSpace, 0));
	painter.drawRect(rect);
	painter.restore();
}

void QMiGuanWidget::timerEvent(QTimerEvent *)
{
	m_fBigAngle += 1.8;
	m_fMidAngle += 1.0;
	m_fLitAngle += 0.7;

	update();
}