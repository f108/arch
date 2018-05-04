// Panel.h: interface for the CPanel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PANEL_H__EED28CBD_B4DB_465D_9325_DE8D6895F970__INCLUDED_)
#define AFX_PANEL_H__EED28CBD_B4DB_465D_9325_DE8D6895F970__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPanel  
{
public:
	CPanel();
	virtual ~CPanel();

	void PanelOut(char *buf, int BufLen);
	void Run(void);

private:
	char *MainBuf;
	int MainBufLen;

};

#endif // !defined(AFX_PANEL_H__EED28CBD_B4DB_465D_9325_DE8D6895F970__INCLUDED_)
