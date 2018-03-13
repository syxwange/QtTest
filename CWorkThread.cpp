#include "CWorkThread.h"
#include "CInput.h"
#include "CDecode.h"
#include <qmessagebox.h>


CWorkThread::CWorkThread(QObject *parent)	: QObject(parent)
{	
	
	
}

CWorkThread::~CWorkThread()
{
	
	m_pIn->setExit();
	m_pOut->setExit();
	m_pInThread->exit();
	m_pOutThread->exit();
	m_pInThread->wait();	
	m_pOutThread->wait();
	free();
}

int CWorkThread::init()
{	
	free();
	m_pIn = new CInFile(m_dataList);
	m_pOut = new COutScreen(m_dataList);
	m_pInThread = new QThread;
	m_pOutThread = new QThread;
	connect(m_pInThread, &QThread::started, m_pIn, &CInFile::decode);
	connect(m_pOutThread, &QThread::started, m_pOut, &COutScreen::write);
	connect(m_pOut, &COutScreen::sendPic, this, &CWorkThread::sendPic);
	m_pIn->setUrl("aaa.flv");
	auto ret = m_pIn->open();	
	if (ret < 0)
	{
		QMessageBox::warning(nullptr, "error", "find decodec error");
		return ret;
	}
	auto i = QThread::currentThreadId();
	m_pIn->moveToThread(m_pInThread);
	m_pInThread->start();
	m_pOut->setWidth(m_pIn->getVCodecPara()->width);
	m_pOut->setHeight(m_pIn->getVCodecPara()->height);
	m_pOut->open();
	m_pOut->moveToThread(m_pOutThread);
	m_pOutThread->start();
	return ret;
}

void CWorkThread::free()
{
	if (m_pInThread)
	{
		m_pIn->setExit();
		m_pInThread->exit();
		m_pInThread->wait();
		m_pInThread->deleteLater();
		m_pInThread = nullptr;
	}
	if (m_pOutThread)
	{
		m_pOut->setExit();
		m_pOutThread->exit();
		m_pOutThread->deleteLater();
		m_pOutThread->wait();
		m_pOutThread = nullptr;
	}	
	if (m_pIn)
	{
		m_pIn->free();
		m_pIn = nullptr;
	}
	if (m_pOut)
	{
		m_pOut->free();
		m_pOut = nullptr;
	}
	for (auto i : m_dataList)
	{
		delete i;
	}	
	m_dataList.clear();
}
