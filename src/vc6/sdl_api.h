#pragma once

#ifndef DUMMY_SDL
#define DUMMY_SDL
#endif

#include <stdlib.h>

extern void CanvasLock(void);
extern void CanvasUnlock(void);
extern void MainFrameRefresh(void);
extern void CanvasSetClipRect(int x1, int y1, int x2, int y2);
extern void CanvasBitblt(int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, const unsigned char *ptr, int w, int h, char hasPink);

struct SDL_Surface {
	int w, h;
	char type;
	const unsigned char *ptr;
	const char *name;
	char hasPink;
};

struct SDL_PixelFormat {
	void *p;
};

struct SDL_Rect {
	int x, y, w, h;
};

struct SDL_Event {
	void *p;
};

struct TTF_Font
{

};

inline void SDL_SetClipRect(SDL_Surface *s, SDL_Rect *rect)
{
	if (s->type == 1)
	{
		CanvasSetClipRect(rect->x, rect->y, rect->x + rect->w, rect->y + rect->h);
	}
	else
	{
		while(1);
	}
}

inline void SDL_BlitSurface(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect)
{
	if (dst->type == 1 && src->type == 2)
	{
		CanvasBitblt(
			dstrect->x, dstrect->y, dstrect->w, dstrect->h, 
			srcrect->x, srcrect->y, srcrect->w, srcrect->h,
			src->ptr, src->w, src->h, src->hasPink);
	}
	else
	{
		while(1);
	}
}

inline void SDL_FreeSurface(SDL_Surface *src)
{
	//free(src);
}

inline SDL_Surface *SDLinit()
{
	static SDL_Surface s1;
	SDL_Surface *screen;
	screen = &s1;
	screen->w = 640;
	screen->h = 480;
	screen->ptr = 0;
	screen->type = 1;
	screen->name = "[screen]";
	screen->hasPink = 0;
	return screen;
}

inline void SDL_Quit()
{

}

inline void SDL_Flip(SDL_Surface *screen)
{
	CanvasUnlock();
	MainFrameRefresh();
}


//------------------------------------

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#endif

#if defined(_MSC_VER) && defined(_DEBUG)

#include <crtdbg.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#define _CRTDBG_MAP_ALLOC
/*
#define new  ::new(_NORMAL_BLOCK, __file__, __line__)
*/

#ifdef malloc
#undef malloc
#endif
#define malloc(s) (_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__))

#ifdef free
#undef free
#endif
#define free(s) (_free_dbg(s, _NORMAL_BLOCK))

#ifdef calloc
#undef calloc
#endif
#define calloc(m, s) (_calloc_dbg(m, s, _NORMAL_BLOCK, __FILE__, __LINE__))

#ifdef realloc
#undef realloc
#endif
#define realloc(m, s) (_realloc_dbg(m, s, _NORMAL_BLOCK, __FILE__, __LINE__))

#ifdef new
#undef new
#endif
#define new DEBUG_NEW

#endif

#define BUFSIZE 256

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_BGCOLOR 0x000000 
//#define WINDOW_BGCOLOR 0xCCCCCC 

#define SSS_APPNAME "SimpleScriptSystem"
#define SSS_VERSION "0.0.1"

#define SSS_CLASS "SimpleScriptSystem_GDI"
#define SSS_TITLE SSS_APPNAME " GDI " SSS_VERSION

//------------------------------------

extern int MainFrameGetMsg(void);
extern void MainFrameRefresh(void);
extern void MainFrameResize(int w, int h);
extern void MainFrameSetTitle(const char *str);

//------------------------------------

extern void MiscTrace(const char *fmt, ... );
extern void MiscAppInit(void);
extern void MiscAppExit(void);

//------------------------------------

extern void KeyboardInit(void);
extern void KeyboardRelease(void);
extern void KeyboardChar(int Key);
extern int KeyboardGetKeyboardStatus(void);


//------------------------------------

extern void MouseInit(void);
extern void MouseRelease(void);
extern void MouseMove(int X, int Y);
extern void MouseLButtonDown(int X, int Y);
extern void MouseLButtonUp(int X, int Y);
extern int MouseGetMouseStatus(void);

//------------------------------------
extern HDC CanvasInit(HWND hWnd);
extern void CanvasRelease(void);

//lock canvas
extern void CanvasLock(void);
extern void CanvasUnlock(void);

//color 
extern void CanvasSetColor(int color);
extern int CanvasRGB(int r, int g, int b);

//draw pixel
//extern void CanvasSetPixel(int x, int y, int color);
extern int CanvasGetPixel(int x, int y);

//draw line
extern void CanvasMoveTo(int x, int y);
extern void CanvasLineTo(int x, int y);
extern void CanvasDrawLine(int x1, int y1, int x2, int y2, int color, int alpha);
extern void CanvasFillRect(int x1, int y1, int x2, int y2, int color);

extern void CanvasBitblt(int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, const unsigned char *ptr, int w, int h, char hasPink);
extern void CanvasDrawPixel(int x1, int y1, int color, int alpha);

//-------------------------------------

