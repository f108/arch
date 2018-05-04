// PanelImage.h: interface for the CPanelImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PANELIMAGE_H__665E8D6C_6E91_4241_9AFF_C0F75AB3C118__INCLUDED_)
#define AFX_PANELIMAGE_H__665E8D6C_6E91_4241_9AFF_C0F75AB3C118__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TX_RALIGN		0x0001
#define TX_LALIGN		0x0002
#define TX_CENTER		0x0003
#define TX_VCENTER		0x0004

#define TX_SINGLELINE	0x0008
#define TX_WORDBREAK	0x0010
#define TX_TRANSPARENT	0x0020

#define TX_VWRAPORIENT	0x0100
#define TX_HWRAPORIENT	0x0000


#define BUFSIZE 256*64*16

class CPanelFont
{
	friend class CFrameSet;
public:
	CPanelFont();
	~CPanelFont();

	void LoadFont(const char *);

	int HS, VS;
	char *data;

	void GetSymbSize(int *_HS, int *_VS) { *_HS=HS; *_VS=VS;};
	inline char GetPixel(unsigned char ch, int x, int y) 
	{ 
		return data[ch*HS*VS+y*HS+x];
	};
};

class CPanelImage  
{
	friend class CFrameSet;
public:
	CPanelImage();
	virtual ~CPanelImage();

	void Clear(void);
	void SetColor(int);
	void SetBkColor(int);

	inline void SetPixel(int Pane, int x, int y, int color) 
		{ unsigned k=256*(16*Pane+y)+x; if (k<BUFSIZE) buf[k]=color%4; };
	inline void SetPixel(int x, int y, int color) 
	{ unsigned k=256*(y+(x/256)*16)+x%256; if (k<BUFSIZE) buf[k]=color%4; };
	void Line(int Pane, int x0, int y0, int x1, int y1, int color);

	void TextOut(int Pane, int x, int y, int color, const char *str);
	void SetFont(const char *);

	void PutChar(unsigned char ch, int x=-1, int y=-1, int color=-1);
	void DrawText(int Pane, int x0, int y0, int x1, int y1, int color, const char *str, DWORD Attr);

	void DrawText(const char *str, int color=-1, int x0=-1, int y0=-1, int x1=-1, int y1=-1);

	void SetXY(int x, int y);
	void SetTextAttr(DWORD Attr);

	char *ExecProg(char *Prog);
	int GetNotNullFrameCount(void);


private:
	int GetLenWrapText(const char *str, int width, int *reallen);
	void ReplaceSubst(char *str);

	unsigned char buf[256*64*16];
	unsigned char AttrBuf[64];
	bool AppendNullFrame;
	int RepeatCount;
	CPanelFont Font;
	int BkColor;
	int Color;
	int X, Y;
	int HS, VS;
	DWORD TextAttr;
};

#endif // !defined(AFX_PANELIMAGE_H__665E8D6C_6E91_4241_9AFF_C0F75AB3C118__INCLUDED_)
