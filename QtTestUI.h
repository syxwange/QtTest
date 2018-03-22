#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtTestUI.h"
class CWorkThread;
struct AVFrame;

class QtTestUI : public QWidget
{
	Q_OBJECT

public:
	QtTestUI(QWidget *parent = Q_NULLPTR);
signals:
	void sendPic(const AVFrame *pic);
private:
	Ui::QtTestUIClass ui;
	CWorkThread *m_pWork;
};
