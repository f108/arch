// PanelImage.cpp: implementation of the CPanelImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LEDServer.h"
#include "PanelImage.h"


//////////////////////////////////////////////////////////////////////

CPanelFont::CPanelFont()
{
	HS=0; VS=0; data=NULL;
}

CPanelFont::~CPanelFont()
{
	delete data;
}

#define FONTFILEID "\x0PanelFontV00"

void CPanelFont::LoadFont(const char *fontname)
{
HANDLE hFile;
DWORD cbw;
char FileName[256];
char buf[20];

	strcpy(FileName, Path);
	strcat(FileName, fontname);
	strcat(FileName, ".pfn");

	hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, NULL);
	if (hFile==INVALID_HANDLE_VALUE) return;
	delete[] data;
	ReadFile(hFile, buf, sizeof(FONTFILEID), &cbw, NULL);
	ReadFile(hFile, &HS, sizeof(HS), &cbw, NULL);
	ReadFile(hFile, &VS, sizeof(VS), &cbw, NULL);
	data = new char[256*HS*VS];
	ReadFile(hFile, data, 256*HS*VS, &cbw, NULL);
	CloseHandle(hFile);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPanelImage::CPanelImage()
{

}

CPanelImage::~CPanelImage()
{

}

void CPanelImage::Clear(void)
{
	memset(buf, 0, 256*16*64);
	memset(AttrBuf, 0x10, 64);
	SetFont("6x8");
	SetBkColor(0);
	AppendNullFrame = true;
	RepeatCount = 1;
};

void CPanelImage::SetFont(const char *fontname)
{
	Font.LoadFont(fontname);
	Font.GetSymbSize(&HS, &VS);
}

void CPanelImage::SetColor(int k)
{
	Color = k;
}

void CPanelImage::SetXY(int x, int y)
{	X = x;	Y = y; }

void CPanelImage::SetTextAttr(DWORD Attr)
{ TextAttr = Attr;}

void CPanelImage::SetBkColor(int BC)
{
	BkColor = BC;
}

void CPanelImage::Line(int Pane, int x0, int y0, int x1, int y1, int color)
{
}

void CPanelImage::TextOut(int Pane, int x, int y, int _color, const char *str)
{
int HS, VS;
int curx=x, cury=y;
int color;

	Font.GetSymbSize(&HS, &VS);
	for(int p=0; p<strlen(str); p++)
	{

		for (int i=0; i<HS; i++)
			for (int j=0; j<VS; j++)
			{
				if (Font.GetPixel(str[p], i, j)==0) 
					color = BkColor;
				else
					color=_color;
				SetPixel(Pane, curx+i, cury+j, color);
			};
		curx+=HS;
	};

};

void CPanelImage::PutChar(unsigned char ch, int x, int y, int _color)
{
	if (x==-1) x=X;
	if (y==-1) y=Y;
	if (_color==-1) _color=Color;
int color;
	for (int i=0; i<HS; i++)
		for (int j=0; j<VS; j++)
		{
			if (x+i>255 && ((TextAttr&TX_VWRAPORIENT)!=0) ||
				y+j>15 && ((TextAttr&TX_VWRAPORIENT)==0)) continue;
			if (Font.GetPixel(ch, i, j)==0) 
				color = BkColor;
			else
				color=_color;
			if ((TextAttr&TX_TRANSPARENT) && Font.GetPixel(ch, i, j)==0) ; else
				SetPixel(x+i, y+j, color);
		};
}

int CPanelImage::GetLenWrapText(const char *str, int width, int *reallen)
{
int *len = new int[strlen(str)];
int ret=0, i, curlen=0;
int maxchar = width/HS;

	for (i=0; i<strlen(str); i++)
	{
		if (str[i]=='\\' && (str[i+1]=='c' || str[i+1]=='b' || str[i+1]=='y')) 
		{
			len[i]=len[i+1]=len[i+2]=curlen;
			i+=2;
			continue;
		};
		curlen++;
		len[i]=curlen;
	};

	if (len[strlen(str)-1]<=maxchar) 
	{
		*reallen = len[strlen(str)-1];
		delete[] len;
		return strlen(str);
	};
	for (i=strlen(str)-1; i>=0; i--)
	{
		if ((str[i]==' ') && (len[i-1]<=maxchar))
		{
			*reallen = len[i];
			delete[] len;
			return i;	
		};
	};
	*reallen = len[maxchar];
	delete[] len;
	return maxchar;
}

int CPanelImage::GetNotNullFrameCount(void)
{
int i, j;
	for (i=0; i<64; i++)
	{
		for (j=0; j<1024*4; j++)
			if (buf[i*1024*4+j]!=0) break;
		if (j>=1024*4) return i==0?1:i;
	};
	return 64;
}

char *_SUBST[] = {"$DATE", "$TIME", "\\x", "$XDATEYYYY", NULL};

int hsmbtoint(const char ch)
{
	if (ch>='0' && ch <='9') return ch-0x30;
	else if (ch>='a' && ch <='f') return ch-0x60+9;
	else if (ch>='A' && ch <='F') return ch-0x40+9;
	else return 0;
};

void CPanelImage::ReplaceSubst(char *str)
{
SYSTEMTIME ST;
char *ptr;
char buf[200];
unsigned char ch;
	GetLocalTime(&ST);
	sprintf(buf, "%02d/%02d%02d:%02d%02d/%02d/%04d", ST.wDay, ST.wMonth, ST.wHour, ST.wMinute, ST.wDay, ST.wMonth, ST.wYear);
	for (int k=0;_SUBST[k];k++)
	{
		for (;;)
		{
			ptr = strstr(str, _SUBST[k]);
			if (ptr==NULL) break;
			switch (k)
			{
				case 0:	strncpy(ptr, &buf[0], 5); break;
				case 1:	strncpy(ptr, &buf[5], 5); break;
				case 2:	
					strncpy(ptr, ptr+2, 2); 
					memset(ptr+2, 'y', 2);
					ch = hsmbtoint(*ptr)*16+hsmbtoint(*(ptr+1));
					*ptr = unsigned char(ch);
					*(ptr+1) = '\\';
					break;
				case 3:	strncpy(ptr, &buf[10], 10); break;
			};
		};
	};
}

void CPanelImage::DrawText(const char *str, int color, int x0, int y0, int x1, int y1)
{
int x=x0, y=y0;
int k, chcount=0, reallen;
char buf[500];

	SetColor(color);

	if (!(TextAttr&TX_VWRAPORIENT))
	{
		for (k=0; k<strlen(str); k++)
		{
			if (str[k]=='\\')
			{
				switch(str[k+1])
				{
					case 'c': SetColor(str[k+2]-0x30); k+=2; break;
					case 'b': SetBkColor(str[k+2]-0x30); k+=2; break;
					case 'y': k+=2; break;
				};
				continue;
			};
			PutChar(str[k], x+HS*chcount, y);
			chcount++;

//			PutChar(str[k], x0+HS*k, y0);

		};
		return;
	};


	for (char *p=(char*)str; *p; )
	{
		if (*p==' ') {p++; continue; };
		k = GetLenWrapText(p, x1-x0, &reallen);
		strncpy(buf, p, k);	buf[k]=0;
		switch (TextAttr&3)
		{
			case TX_RALIGN:	x = x1-reallen*HS; break;
			case TX_LALIGN:	x = x0; break;
			case TX_CENTER:	x = x0+(x1-x0-reallen*HS)/2; break;
		};
		chcount=0;

		for (int i=0; i<k; i++)
		{
			if (p[i]=='\\')
			{
				switch(p[i+1])
				{
					case 'c': SetColor(str[i+2]-0x30); i+=2; break;
					case 'b': SetBkColor(str[i+2]-0x30); i+=2; break;
					case 'y': i+=2; break;
				};
				continue;
			};
			PutChar(p[i], x+HS*chcount, y);
			chcount++;
		};

		cout << buf << endl;

		p+=k;
		y+= VS;
	};
}

char *_Command[] = {"SETTEXT", "SETATTR", "SETFONT", "SETFRAMEATTR", "SETTEXTATTR", 
					"NOTNULLFRAME", "REPEATCOUNT", NULL };

void CleanText(char *str)
{
char *ptr, *ptr1, *ptr2;
int len;
	ptr = str;

	len=0;
	for (;;)
	{
		ptr1 = strchr(ptr, '"');
		if (ptr1==NULL) break;
		ptr2 = strchr(ptr1+1, '"');
		strncpy(str+len, ptr1+1, ptr2-ptr1);
		len+=ptr2-ptr1-1;
		str[len]=0;
		ptr = ptr2+1;
	};
};

char *CPanelImage::ExecProg(char *Prog)
{
char *ptr, *ptr1, *ptr2, *buf, *ret=NULL;
int c,x0,y0,x1,y1;
int len, i;

	for (len=0, i=0;Prog[len];len++)
	{
		if (Prog[len]==';' && i%2==0) 
		{
			ret = &Prog[len]+1;
			break;
		};
		if (Prog[len]=='"') i++;
	};

	buf = new char[len+1];
	strncpy(buf, Prog, len);
	buf[len]=0;

	ReplaceSubst(buf);

	ptr1 = strchr(buf, '"');
	if (ptr1 == NULL) ptr1=buf+strlen(buf);

	for (i=0; _Command[i]!=NULL; i++)
	{
		ptr = strstr(buf, _Command[i]);
		if (ptr==NULL || ptr >=ptr1 || *(ptr+strlen(_Command[i]))!=' ') continue;
		break;
	};

	switch (i)
	{
		case 0:
			ptr1 = ptr+strlen(_Command[i]); //settext
			sscanf(ptr1, "%d,%d,%d,%d", &x0, &y0, &x1, &y1);
			CleanText(buf);
			DrawText(buf, c, x0, y0, x1, y1);
			break;
		case 2:
			ptr1 = ptr+strlen(_Command[i]);
			sscanf(ptr1, "%d,%d,%d,%d", &x0, &y0, &x1, &y1);
			CleanText(buf);
			SetFont(buf);
			break;
		case 3:
			unsigned char Attr;
			ptr1 = ptr+strlen(_Command[i]);
			sscanf(ptr1, "%d,%d,%d,%d", &x0, &y0, &x1, &y1);
			Attr = (y0&15)|((y1&3)<<4)|((x1&3)<<6);
			if (unsigned(x0)>=64) for (i=0; i<64; i++) AttrBuf[i] = Attr;
			else AttrBuf[x0]=Attr;
			break;
		case 4:
			ptr1 = ptr+strlen(_Command[i]);
			sscanf(ptr1, "%d", &c);
			SetTextAttr(c);
			cout << int(c) << endl;
			break;
		case 5:
			AppendNullFrame = false;
			break;
		case 6:
			ptr1 = ptr+strlen(_Command[i]);
			sscanf(ptr1, "%d", &x0);
			RepeatCount = x0;
			break;
	};

	delete[] buf;
	return ret;
}




