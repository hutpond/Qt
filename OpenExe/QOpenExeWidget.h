#pragma once

#include <QtWidgets/QWidget>
#include <QProcess>

class QOpenExeWidget : public QWidget
{
	Q_OBJECT

public:
	QOpenExeWidget(QWidget *parent = Q_NULLPTR);

protected:
	void resizeEvent(QResizeEvent *);

protected:
	void startExe(const char *, const char *);

private:
	QProcess m_process;

	HWND childHwnd;
};
