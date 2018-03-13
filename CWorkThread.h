#pragma once

#include <QThread>

#include "CMediaData.h"
#include "CInput.h"
#include "CMediaOutput.h"

class CWorkThread : public QObject
{
	Q_OBJECT

public:
	CWorkThread(QObject *parent=nullptr);
	~CWorkThread();
	int init();	
	void free();
public:
	QList<CMediaData*> m_dataList;
signals:
	void sendPic(const AVFrame *pic);
private:
	CInFile* m_pIn=nullptr;
	COutScreen* m_pOut = nullptr;
	QThread* m_pInThread = nullptr;
	QThread* m_pOutThread = nullptr;
	
};
