#pragma once


struct AVCodecParameters;
struct AVCodecContext;
struct AVPacket;
struct AVFrame;
struct SwsContext;
class CInFile;
class CDecode
{
public:
	CDecode(CInFile *pIn);
	~CDecode();
	void free();
	bool isOpen() { return m_bOpened; }
	AVCodecContext* getVCodecCtx() { return m_pVCodecCtx; }
	AVCodecContext* getACodecCtx() { return m_pACodecCtx; }
	int decode(AVFrame*pOutFrame,AVPacket *pPacket);
	int getWidth() { return m_nWidth; }
	int getHeight() { return m_nHeight; }

private:
	AVCodecContext * m_pVCodecCtx = nullptr;
	AVCodecContext * m_pACodecCtx = nullptr;
	bool m_bOpened=false;
	SwsContext *m_pVSwsCtx = nullptr;
	int m_nWidth = 0;
	int m_nHeight = 0;
	CInFile *m_pInFile = nullptr;
};

