// FrameSet.h: interface for the CFrameSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMESET_H__8793F2E8_DC62_4800_BAC6_741B38BFE9F2__INCLUDED_)
#define AFX_FRAMESET_H__8793F2E8_DC62_4800_BAC6_741B38BFE9F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PanelImage.h"

class CFrameSet  
{
public:
	CFrameSet();
	virtual ~CFrameSet();

	DWORD SendToPort(const char *PortName, bool &ServiceInProgress);

	void LoadFrom(CPanelImage *CPI, int _FrameCount);

	DWORD GetExpositionTime(void);
	DWORD GetTrasmissionTime(void);

private:
	unsigned char FrameAttr[64];
	int FrameCount;
	char databuf[64*1024];
	int RepeatCount;
};

#endif // !defined(AFX_FRAMESET_H__8793F2E8_DC62_4800_BAC6_741B38BFE9F2__INCLUDED_)
