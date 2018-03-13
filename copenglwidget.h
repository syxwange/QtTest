#pragma once

#include <QOpenGLWidget>
struct AVFrame;

class COpenGLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	COpenGLWidget(QWidget *parent);
	~COpenGLWidget();
	void	paintEvent(QPaintEvent *event);
	void onShowPic(const AVFrame *pic);

private:
	QImage m_img;
	bool m_bReSize = true;
};
