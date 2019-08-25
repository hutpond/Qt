#include "QOpenExeWidget.h"
#include<Windows.h>
#include <atlstr.h>
#include <QWindow>
#include <QDebug>

QOpenExeWidget::QOpenExeWidget(QWidget *parent)
	: QWidget(parent)
{
	//QString cmd = QString("notepad.exe");
	//this->startExe("D:/project/hook/notepad/x64/Debug/notepad.exe", "notepad");
	this->startExe("notepad.exe", "notepad");
}

void QOpenExeWidget::startExe(const char *cmd, const char *name)
{
	m_process.start(cmd);
	//if (!m_process.waitForStarted(300))
	//{
	//	return;
	//}
	Sleep(100);

	CString str = CString(name);
	USES_CONVERSION;
	LPCWSTR wszClassName = A2CW(W2A(str));
	str.ReleaseBuffer();

	childHwnd = FindWindow(str, NULL);
	HWND parentHwnd = (HWND)this->winId();
	SetParent(childHwnd, parentHwnd);
	SetWindowPos(childHwnd, HWND_TOP, 0, 0, 500, 500, SWP_FRAMECHANGED);
	SetWindowLong(childHwnd, GWL_STYLE, GetWindowLong(childHwnd, GWL_STYLE) & ~WS_CAPTION);
	//SetWindowLong(
	//	childHwnd, GWL_EXSTYLE, 
	//	GetWindowLong(childHwnd, GWL_EXSTYLE) & ~(WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME)
	//);
}

void QOpenExeWidget::resizeEvent(QResizeEvent *)
{
	SetWindowPos(childHwnd, HWND_TOP, 0, 0, this->width(), this->height(), SWP_FRAMECHANGED);
}