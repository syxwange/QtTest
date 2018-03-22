#include "QtTestUI.h"
#include <QCameraInfo>
#include <qdebug.h>

#include "CWorkThread.h"

extern "C"
{
#include "libavformat/avformat.h"
}
#pragma comment(lib, "avutil.lib")


QtTestUI::QtTestUI(QWidget *parent)	: QWidget(parent),m_pWork(new CWorkThread(this))
{
	ui.setupUi(this);	
	connect(m_pWork, &CWorkThread::sendPic, ui.openGLWidget, &COpenGLWidget::onShowPic);
	connect(ui.pushButton, &QPushButton::clicked, m_pWork, &CWorkThread::init);
}
