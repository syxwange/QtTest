#include "CMediaOutput.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/time.h>
#include <libswscale/swscale.h>
}
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")


CMediaOutput::CMediaOutput(QList<CMediaData*>& data, QObject *parent )	: QObject(parent),m_dataList(data)
{

}

CMediaOutput::~CMediaOutput()
{
}

void CMediaOutput::free()
{
	
}

void CMediaOutput::filter()
{
	for (auto t : m_vecFilterType)
	{
		switch (t)
		{
		case Yuv2Rgb:
			break;
		case ReSize:
			break;
		case Brightness:
			break;
		case Contrast:
			break;
		default:
			break;
		}
	}
}

COutScreen::COutScreen(QList<CMediaData*>& data, QObject *parent):CMediaOutput(data,parent)
{
	
}

COutScreen::~COutScreen()
{
}

int COutScreen::open()
{
	m_pVSwsCtx = sws_getContext(m_nWidth, m_nHeight, AV_PIX_FMT_YUV420P,
		m_nWidth, m_nHeight, AV_PIX_FMT_RGB24, SWS_BICUBIC, nullptr, nullptr, nullptr);
	return 0;
}

int COutScreen::write()
{
	auto pFrame = av_frame_alloc();
	pFrame->width =m_nWidth;
	pFrame->height = m_nHeight;
	pFrame->format = AV_PIX_FMT_RGB24;
	pFrame->pts = 0;
	auto ret = av_frame_get_buffer(pFrame, 32);
	m_starTime = av_gettime();
	while (m_bWrite)
	{
		m_mutex.lock();
		if(m_dataList.count()<1)
		{
			m_mutex.unlock();
			continue;
		}
		CMediaData * tempData = m_dataList.first();
		m_dataList.removeFirst();
		m_mutex.unlock();
		if (tempData->m_nStreamId == 0)
		{			
			int h = sws_scale(m_pVSwsCtx, tempData->p.m_pFrame->data, tempData->p.m_pFrame->linesize, 0,
				m_nHeight, pFrame->data, pFrame->linesize);			
			filter();
			AVRational tb = tempData->m_timeBase;
			//已经过去的时间
			long long now = av_gettime() - m_starTime;
			long long pts = static_cast<long long>(tempData->p.m_pFrame->pts * (1000 * 1000 * av_q2d(tb)));
			if (pts > now)
			{				
				av_usleep(static_cast<unsigned int>(pts - now));
			}
			emit sendPic(pFrame);
			delete tempData;
		}
		
	}
	return 0;
}

void COutScreen::free()
{
	
	if (m_pVSwsCtx)
	{
		sws_freeContext(m_pVSwsCtx);
		m_pVSwsCtx = nullptr;
	}
}
