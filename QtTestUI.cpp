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
	//connect(ui.pushButton, &QPushButton::clicked, this, &QtTestUI::init);
	//connect(this, &QtTestUI::sendPic, ui.openGLWidget, &COpenGLWidget::onShowPic);
}

int QtTestUI::init()
{
	//auto m_pInFile = new CInFile();
	//auto ret = m_pInFile->open("aaa.flv");
	//auto m_pDecpde = new CDecode(m_pInFile->getVCodecPara(), m_pInFile->getACodecPara());
	//if (!m_pDecpde->isOpen())
	//{
	//	QMessageBox::warning(nullptr, "error", "find decode error");
	//	return -1;
	//}
	//auto m_pRgbFrame = av_frame_alloc();
	//m_pRgbFrame->width = m_pDecpde->getWidth();
	//m_pRgbFrame->height = m_pDecpde->getHeight();
	//m_pRgbFrame->format = AV_PIX_FMT_RGB24;
	//m_pRgbFrame->pts = 0;
	//ret = av_frame_get_buffer(m_pRgbFrame, 32);


	//while (true)
	//{
	//	Sleep(1);
	//	AVPacket pkt = {};
	//	auto ret = m_pInFile->read(&pkt);
	//	ret = m_pDecpde->decode(m_pRgbFrame, &pkt);
	//	if (ret == -11)
	//		continue;
	//	if (ret == 3)
	//	{

	//		QImage img((uchar*)m_pRgbFrame->data[0], m_pRgbFrame->width, m_pRgbFrame->height, QImage::Format_RGB888);
	//		img.save("111.jpg");
	//		img.save("111.bmp");
	//		img.save("111.png");
	//		//emit sendPic(m_pRgbFrame);
	//	}
	//}
	return 0;
}
