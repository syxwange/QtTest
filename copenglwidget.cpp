#include "copenglwidget.h"
#include <QPainter>

extern "C"
{
#include "libavformat/avformat.h"	
}

COpenGLWidget::COpenGLWidget(QWidget *parent): QOpenGLWidget(parent)
{
}

COpenGLWidget::~COpenGLWidget()
{
}

void COpenGLWidget::paintEvent(QPaintEvent * event)
{
	QPainter p;
	p.begin(this);
	p.drawImage(QPoint(0, 0), m_img);
	p.end();
}

void COpenGLWidget::onShowPic(const AVFrame *pic)
{	
	int pixSize = 3;
	delete m_img.bits();
	if (m_bReSize)
	{
		resize(pic->width, pic->height);
		m_bReSize = false;
	}
	uchar *buf = new uchar[pic->height*pic->width* pixSize];
	m_img = QImage(buf, pic->width, pic->height, QImage::Format_RGB888);
	memcpy(m_img.bits(), (uchar *)pic->data[0],pic->height*pic->width*pixSize);
	m_img.save("111.bmp");
	update();
	
}
