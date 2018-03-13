#include "CDecode.h"
#include "CInput.h"

extern "C"
{

#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
#include <libavutil/time.h>
#include <libswscale/swscale.h>
}

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")

CDecode::CDecode(CInFile *pIn)
{
	m_pInFile = pIn;
	if (pIn->getVCodecPara())
	{
		auto pInCodec = avcodec_find_decoder(pIn->getVCodecID());
		m_pVCodecCtx = avcodec_alloc_context3(pInCodec);
		if (!m_pVCodecCtx)
		{
			m_bOpened = false;
			return;
		}
		int  ret =avcodec_parameters_to_context(m_pVCodecCtx, pIn->getVCodecPara());
		if (ret < 0)
		{
			m_bOpened = false;
			return;
		}
		//m_pVCodecCtx->framerate = av_guess_frame_rate(pInFmtCtx, pInFmtCtx->streams[vStreamIndex], nullptr);
		ret = avcodec_open2(m_pVCodecCtx, pInCodec, nullptr);
		if (ret)
		{
			m_bOpened = false;
			return;
		}
		m_bOpened = true;
		m_nWidth = m_pVCodecCtx->width;
		m_nHeight = m_pVCodecCtx->height;
	}	
	if (pIn->getACodecPara())
	{
		auto pInCodec = avcodec_find_decoder(pIn->getACodecPara()->codec_id);
		m_pACodecCtx = avcodec_alloc_context3(pInCodec);
		if (!m_pVCodecCtx)
		{
			m_bOpened = false;
			return;
		}
		int  ret = avcodec_parameters_to_context(m_pACodecCtx, pIn->getACodecPara());
		if (ret < 0)
		{
			m_bOpened = false;
			return;
		}		
		//m_pVCodecCtx->framerate = av_guess_frame_rate(pInFmtCtx, pInFmtCtx->streams[vStreamIndex], nullptr);
		ret = avcodec_open2(m_pACodecCtx, pInCodec, nullptr);
		if (ret)
		{
			m_bOpened = false;
			return;
		}
		m_bOpened = true;
	}

	m_pVSwsCtx = sws_getContext(m_pVCodecCtx->width, m_pVCodecCtx->height, m_pVCodecCtx->pix_fmt,
									m_nWidth , m_nHeight, AV_PIX_FMT_RGB24, SWS_BICUBIC, nullptr, nullptr, nullptr);

	
}


CDecode::~CDecode()
{
	free();
}

void CDecode::free()
{
	if (m_pVCodecCtx)
	{
		avcodec_free_context(&m_pVCodecCtx);
		m_pVCodecCtx = nullptr;
	}
	if (m_pACodecCtx)
	{
		avcodec_free_context(&m_pACodecCtx);
		m_pACodecCtx = nullptr;
	}
	if (m_pVSwsCtx)
	{
		sws_freeContext(m_pVSwsCtx);
		m_pVSwsCtx = nullptr;
	}
}

int CDecode::decode(AVFrame*pOutFrame, AVPacket *pInPacket)
{
	
	auto ret = avcodec_send_packet(m_pVCodecCtx, pInPacket);
	if (ret < 0)  return ret;
	AVFrame *frame= av_frame_alloc();
	ret = avcodec_receive_frame(m_pVCodecCtx, frame);
	if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
	{
		av_frame_free(&frame);
		return ret;
	}		
	if (pInPacket->stream_index == m_pInFile->getVIndex())
	{
		int h = sws_scale(m_pVSwsCtx, frame->data, frame->linesize, 0, m_pVCodecCtx->height, pOutFrame->data, pOutFrame->linesize);
		if (h <= 0)
		{
			av_frame_free(&frame);
			return -1;
		}
		av_frame_free(&frame);
		return 1;
	}
	
	av_frame_free(&frame);
	return 2;
}

