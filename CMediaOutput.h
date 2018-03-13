#pragma once

#include <QObject>
#include "CMediaData.h"
#include <qvector.h>
#include <qmutex.h>
class SwsContext;

class CMediaOutput : public QObject
{
	Q_OBJECT

public:
	CMediaOutput(QList<CMediaData*>& data, QObject *parent=nullptr);
	~CMediaOutput();
	virtual int open() = 0;
	virtual int write() = 0;	
	virtual void free();
	void setWidth(int width) { m_nWidth = width; }
	void setHeight(int height) { m_nHeight = height; }
	void setReWidth(int width) { m_nResizeWidth = width; }
	void setReHeight(int height) { m_nResizeHeight = height; }
	void setExit() { m_bWrite = false; }
protected:
	void filter();

protected:
	QList<CMediaData*>& m_dataList;
	QVector<FilterType> m_vecFilterType;
	bool m_bWrite = true;
	int m_nWidth = 0;
	int m_nHeight = 0;
	int m_nResizeWidth = 0;
	int m_nResizeHeight = 0;
	QMutex m_mutex;	
};

class COutScreen:public CMediaOutput
{
	Q_OBJECT
public:
	COutScreen(QList<CMediaData*>& data, QObject *parent = nullptr);
	~COutScreen();

	virtual int open() ;
	virtual int write() ;
	void free();
signals:
	void sendPic(AVFrame * pic);
private:
	SwsContext * m_pVSwsCtx = nullptr;
	long long m_starTime = 0;
};

