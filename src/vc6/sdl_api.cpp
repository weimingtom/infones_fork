#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdarg.h>
#include <crtdbg.h>
#include <stdlib.h>
#include "sdl_api.h"
#include "fixedfont_24.bin.h" 

#define WINDOW_STYLE WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU
#define TIMER_ELAPSE 1

static HWND s_hAppWnd;
static HDC s_hCanvas;

static LRESULT CALLBACK WndProc(HWND hWnd, 
	UINT message, 
	WPARAM wParam, 
	LPARAM lParam)
{
	HDC hdc;
	switch(message)
	{
	case WM_COMMAND:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_CREATE:
		s_hAppWnd = hWnd;
		SetWindowPos(hWnd, NULL, 0, 0, -1, -1, SWP_NOSIZE);
		s_hCanvas = CanvasInit(hWnd);
		MouseInit();
		KeyboardInit();
		SetTimer(hWnd, 1, TIMER_ELAPSE, 0);
		break;
	
	case WM_DESTROY:
		KeyboardRelease();
		MouseRelease();
		CanvasRelease();
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);
			BitBlt(hdc,
				ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right - ps.rcPaint.left, 
				ps.rcPaint.bottom - ps.rcPaint.top,
				s_hCanvas, 
				ps.rcPaint.left, ps.rcPaint.top, 
				SRCCOPY);
			EndPaint(hWnd, &ps);
		}
		break;

	case WM_TIMER:
		{
			UINT nIDEvent = (UINT)wParam;
			switch(nIDEvent)
			{
			case 1:
				break;
			}
		}
		break;

	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_CONTROL:
				break;
			
			case VK_ESCAPE:
				break;
			}
		}
		break;

	case WM_CHAR:
		{
			int Key = (UINT)wParam;
			MiscTrace("WM_CHAR: %d\n", Key);
			KeyboardChar(Key);
		}
		break;

	case WM_MOUSEMOVE:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			//MiscTrace("WM_MOUSEMOVE: %d, %d\n", point.x, point.y);
			MouseMove(point.x, point.y);
		}
		break;

	case WM_LBUTTONDOWN:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			MiscTrace("WM_LBUTTONDOWN: %d, %d\n", point.x, point.y);
			MouseLButtonDown(point.x, point.y);
		}
		break;

	case WM_LBUTTONUP:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			MiscTrace("WM_LBUTTONUP: %d, %d\n", point.x, point.y);
			MouseLButtonUp(point.x, point.y);
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

static BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	static RECT rectWindow = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	AdjustWindowRect(&rectWindow, WINDOW_STYLE, FALSE);
    hWnd = CreateWindowA(SSS_CLASS,
		SSS_TITLE, WINDOW_STYLE, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		rectWindow.right - rectWindow.left, 
		rectWindow.bottom - rectWindow.top, 
		NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

static ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, NULL);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = SSS_CLASS;
	wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);
	return RegisterClassExA(&wcex);
}

extern int main(int argc, char **argv);
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, 
        LPSTR lpCmdLine,
	int nCmdShow)
{
	MiscAppInit();
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	MyRegisterClass(hInstance);
	if(!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
#if 0
	int width = 640;
	int height = 480;
	MainFrameResize(width, height);
	while (true) 
	{
		CanvasSetColor(WINDOW_BGCOLOR);
		if (MainFrameGetMsg() != 0) 
		{
			break;
		}
		CanvasLock();
		//CanvasFillRect(100, 100, width-100, height-100, 0xff0000);
		CanvasFillRect(0, 0, width-0, height-0, 0xffffff);
		CanvasDrawLine(100, 100, width-100, height-100, 0xff0000, 0xff);
		CanvasBitblt(0, 0, 442, 13, 0, 0, 442 / 2, 13, fixedfont_bin, 442, 13, 1);

		CanvasUnlock();
		MainFrameRefresh();
	}
#else
	int width = 240;
	int height = 240;
	MainFrameResize(width, height);
	main(__argc, __argv);
#endif
	return 0; 
}

int MainFrameGetMsg(void) 
{
	MSG msg;
	if(!GetMessage(&msg, 0, 0, 0))
	{
		return 1;
	}
	if(!TranslateAccelerator(msg.hwnd, NULL, &msg)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

void MainFrameRefresh()
{
	InvalidateRect(s_hAppWnd, 0, FALSE);
}

void MainFrameResize(int w, int h)
{
	RECT rectWindow = {0};
        rectWindow.right = w;
        rectWindow.bottom = h;
	AdjustWindowRect(&rectWindow, WINDOW_STYLE, FALSE);
	SetWindowPos(s_hAppWnd, NULL, 
		0, 0, 
		rectWindow.right - rectWindow.left, 
		rectWindow.bottom - rectWindow.top, 
		SWP_NOMOVE);
	UpdateWindow(s_hAppWnd);
}

void MainFrameSetTitle(const char *str)
{
	SetWindowTextA(s_hAppWnd, str);
}

//------------------------------------------------------------------


static HDC s_hBackBufferDC;
static HBITMAP s_hBitmap;
static HBITMAP s_hOldBitmap;
static HPEN s_hPen;
static HPEN s_hOldPen;
static HBRUSH s_hBrush;
static HBRUSH s_hOldBrush;

HDC CanvasInit(HWND hWnd)
{
	RECT rect;
	HDC hDC;
	GetClientRect(hWnd, &rect);
	hDC = GetDC(hWnd);
	s_hBitmap = CreateCompatibleBitmap(hDC, 
		rect.right - rect.left, 
		rect.bottom - rect.left);
	s_hPen = CreatePen(PS_SOLID, 0, 0);
	s_hBackBufferDC = CreateCompatibleDC(hDC);
	s_hBrush = (HBRUSH)CreateSolidBrush(WINDOW_BGCOLOR);
	/*
	 * NOTE: bitmap object must be selected
	 */
	s_hOldBitmap = (HBITMAP)SelectObject(s_hBackBufferDC, s_hBitmap);
	s_hOldPen = (HPEN)SelectObject(s_hBackBufferDC, s_hPen);
	s_hOldBrush = (HBRUSH)SelectObject(s_hBackBufferDC, s_hBrush);
	ReleaseDC(hWnd, hDC);
	return s_hBackBufferDC;
}

void CanvasRelease(void)
{
	SelectObject(s_hBackBufferDC, s_hOldPen);
	SelectObject(s_hBackBufferDC, s_hOldBitmap);
	SelectObject(s_hBackBufferDC, s_hOldBrush);
	DeleteObject(s_hBackBufferDC);
	DeleteObject(s_hBitmap);
	DeleteObject(s_hPen);
	DeleteObject(s_hBrush);
}

/*
void CanvasSetPixel(int x, int y, int color)
{
	SetPixel(s_hBackBufferDC, x, y, (COLORREF)color);
}
*/

int CanvasGetPixel(int x, int y)
{
	return (int)GetPixel(s_hBackBufferDC, x, y);
}

void CanvasSetColor(int color)
{
	HPEN hNewPen = CreatePen(PS_SOLID, 0, color);
	SelectObject(s_hBackBufferDC, hNewPen);
	DeleteObject(s_hPen);
	s_hPen = hNewPen;
}

void CanvasMoveTo(int x, int y)
{
	MoveToEx(s_hBackBufferDC, x, y, NULL);
}

void CanvasLineTo(int x, int y)
{
	LineTo(s_hBackBufferDC, x, y);
}

//FIXME:
void CanvasDrawPixel(int x1, int y1, int color, int alpha)
{
	if (alpha != 255)
	{
		//FIXME:
		//__asm int 3;
	}
	else
	{
		CanvasFillRect(x1, y1, x1+1, y1+1, color);
	}
}

//FIXME:color参数很可能没传入正确的alpha
void CanvasDrawLine(int x1, int y1, int x2, int y2, int color, int alpha)
{
#if 0
	CanvasSetColor(color);
	CanvasMoveTo(x1, y1);
	CanvasLineTo(x2, y2);
#else

#ifndef ABS
#define ABS(x) ((x)<0?-(x):(x))
#endif
	
	int dx = ABS(x2 - x1);
    int dy = ABS(y2 - y1);

    if (dx > dy)
    {
        if (x1 > x2)
        {
            // swap x1, x2
            x1 ^= x2;
            x2 ^= x1;
            x1 ^= x2;

            // swap y1, y2
            y1 ^= y2;
            y2 ^= y1;
            y1 ^= y2;
        }

        if (y1 < y2)
        {
            int y = y1;
            int p = 0;

            for (int x = x1; x <= x2; x++)
            {
                CanvasDrawPixel(x, y, color, alpha);
                
                p += dy;

                if (p * 2 >= dx)
                {
                    y++;
                    p -= dx;
                }
            }
        }
        else
        {
            int y = y1;
            int p = 0;

            for (int x = x1; x <= x2; x++)
            {
                CanvasDrawPixel(x, y, color, alpha);
                p += dy;

                if (p * 2 >= dx)
                {
                    y--;
                    p -= dx;
                }
            }
        }
    }
    else
    {
        if (y1 > y2)
        {
            // swap y1, y2
            y1 ^= y2;
            y2 ^= y1;
            y1 ^= y2;

            // swap x1, x2
            x1 ^= x2;
            x2 ^= x1;
            x1 ^= x2;
        }

        if (x1 < x2)
        {
            int x = x1;
            int p = 0;

            for (int y = y1; y <= y2; y++)
            {
                CanvasDrawPixel(x, y, color, alpha);

                p += dx;

                if (p * 2 >= dy)
                {
                    x++;
                    p -= dy;
                }
            }
        }
        else
        {
            int x = x1;
            int p = 0;

            for (int y = y1; y <= y2; y++)
            {
                CanvasDrawPixel(x, y, color, alpha);

                p += dx;

                if (p * 2 >= dy)
                {
                    x--;
                    p -= dy;
                }
            }
        }
    }
#endif
}

void CanvasFillRect(int x1, int y1, int x2, int y2, int color)
{
#if 1
	CanvasSetColor(color);
	//https://docs.microsoft.com/zh-cn/windows/desktop/gdi/filled-shape-functions
	//Rectangle(s_hBackBufferDC, x1, y1, x2, y2);
	RECT rcBmp;
	rcBmp.left = x1;
	rcBmp.right = x2;
	rcBmp.top = y1;
	rcBmp.bottom = y2;
	int r = (color >> 0) & 0xff;
	int g = (color >> 8) & 0xff;
	int b = (color >> 16) & 0xff;
	HBRUSH hbrBkgnd = CreateSolidBrush(RGB(r, g, b));
	FillRect(s_hBackBufferDC, &rcBmp, hbrBkgnd); 
	DeleteObject(hbrBkgnd);
#endif
}

void CanvasLock()
{
	Rectangle(s_hBackBufferDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void CanvasUnlock()
{

}

void CanvasSetClipRect(int x1, int y1, int x2, int y2)
{
#if 0
	//SelectClipRgn(s_hBackBufferDC, NULL);
	HRGN s_hrgn = CreateRectRgn(x1, y1, x2, y2); 
    SelectClipRgn(s_hBackBufferDC, s_hrgn);
	DeleteObject(s_hrgn);
#endif
}

void CanvasBitblt(int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, const unsigned char *ptr, int w, int h, char hasPink)
{
	if (ptr != NULL)
	{
#if 1
#define TEST_IMAGE 0
#if TEST_IMAGE
		int j,k;
		unsigned char *image = (unsigned char *)calloc(w * h * 3, 1);
		//memcpy(image, ptr, w * h * 3);
		for (j = 0; j < h; ++j)
		{
			for (k = 0; k < w; ++k)
			{
				image[j * w * 3 + k * 3 + 0] = 0x00; // blue
				image[j * w * 3 + k * 3 + 1] = 0x00; // green
				image[j * w * 3 + k * 3 + 2] = 0xff; // red
			}
		}
#else
		const unsigned char *image = ptr;
#endif
		int x, y;
		for (y = sy; y >= 0 && y < h && y < sy + sh; ++y)
		{
			for (x = sx; x >= 0 && x < w && x < sx + sw; ++x)
			{
				unsigned char b = image[y * w * 3 + x * 3 + 0];
				unsigned char g = image[y * w * 3 + x * 3 + 1];
				unsigned char r = image[y * w * 3 + x * 3 + 2];
				if (hasPink && b == 0xff && g == 0x00 && r == 0xff)
				{
					//skip
				}
				else
				{
					CanvasDrawPixel(
						dx + (x - sx), dy + (y - sy), 
						r << 0 | g << 8 | b << 16, 0xff); 
				}
			}
		}



#if TEST_IMAGE
		free(image);
#endif
#endif
	}
	else
	{
		//__asm int 3;
	}
}

int CanvasRGB(int r, int g, int b)
{
	return RGB(r, g, b);
}

//------------------------------------------------------------------

#ifndef BOOL
#define BOOL int
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define PEN_DOWN 0xC0
#define PEN_MOVE 0x90
#define PEN_UP 0x20
#define PEN_LEAVE 0x8

struct mouse_buffer_struct {
	int status; //Is dragging
	int buffer[BUFSIZE];
	int head; //Reading position
	int tail; //Writing position
	BOOL reading; //Is reading
	BOOL writing; //Is writing
};
static struct mouse_buffer_struct s_MBuffer;

static int MouseGetBufNum(int head, int tail)
{
	if (tail > head)
	{
		return tail - head;
	}
	else if (tail < head)
	{
		return BUFSIZE - head + tail;
	} 
	else
	{
		return 0;
	}
}

void MouseInit(void)
{
    s_MBuffer.status = 0;
    s_MBuffer.writing = FALSE;
    s_MBuffer.reading = FALSE;
    s_MBuffer.head = 0;
    s_MBuffer.tail = 0;
	memset(s_MBuffer.buffer, 0, sizeof(s_MBuffer.buffer));
}

void MouseRelease(void)
{
    s_MBuffer.head = 0;
    s_MBuffer.tail = 1;
    s_MBuffer.buffer[0] = -1;
}

void MouseMove(int X, int Y)
{
	if (s_MBuffer.status == 1 && 
		MouseGetBufNum(s_MBuffer.head, s_MBuffer.tail) < BUFSIZE - 1)
	{
		s_MBuffer.writing = TRUE;
		s_MBuffer.buffer[s_MBuffer.tail] = 
			((X & 0xFFF) << 12) | 
			(Y & 0xFFF) | 
			(PEN_MOVE << 24);
		if (s_MBuffer.tail == BUFSIZE - 1)
		{
			s_MBuffer.tail = 0;
		}
		else
		{
			s_MBuffer.tail++;
		}
		s_MBuffer.writing = FALSE;
	}
}

void MouseLButtonDown(int X, int Y)
{
	if (MouseGetBufNum(s_MBuffer.head, s_MBuffer.tail) < BUFSIZE - 1)
	{
		s_MBuffer.status = 1;
		s_MBuffer.writing = TRUE;
		s_MBuffer.buffer[s_MBuffer.tail] = 
			((X & 0xFFF) << 12) | 
			(Y & 0xFFF) | 
			(PEN_DOWN << 24);
		if (s_MBuffer.tail == BUFSIZE - 1)
		{
			s_MBuffer.tail = 0;
		}
		else
		{
			s_MBuffer.tail++;
		}
		s_MBuffer.writing = FALSE;
	}
}

void MouseLButtonUp(int X, int Y)
{
	if (s_MBuffer.status == 1)
	{
		s_MBuffer.writing = TRUE;
		s_MBuffer.buffer[s_MBuffer.tail] = 
			((X & 0xFFF) << 12) | 
			(Y & 0xFFF) | 
			(PEN_UP << 24);
		if (s_MBuffer.tail == BUFSIZE - 1)
		{
			s_MBuffer.tail = 0;
		}
		else
		{
			s_MBuffer.tail++;
		}
		s_MBuffer.writing = FALSE;
		s_MBuffer.status = 0;
	}
}

int MouseGetMouseStatus(void)
{
    int status;
    if (MouseGetBufNum(s_MBuffer.head, s_MBuffer.tail) > 0)
    {
		/*
		MiscTrace("MouseGetBufNum: %d\n", 
			MouseGetBufNum(s_MBuffer.head, s_MBuffer.tail));
        */
		s_MBuffer.reading = TRUE;
        status = s_MBuffer.buffer[s_MBuffer.head];
		if (s_MBuffer.head == BUFSIZE - 1)
		{
			s_MBuffer.head = 0;
		}
		else
		{
			s_MBuffer.head++;
		}
		s_MBuffer.reading = FALSE;
        return status;
    }
    return 0;
}

//-------------------------------------------

struct keyboard_buffer_struct {
	int status;
	int buffer[BUFSIZE];
	int head;
	int tail;
	BOOL reading;
	BOOL writing;
};
static struct keyboard_buffer_struct s_KBuffer;

static int KeyboardGetBufNum(int head, int tail)
{
	if (tail > head)
	{
		return tail - head;
	}
	else if (tail < head)
	{
		return BUFSIZE - head + tail;
	} 
	else
	{
		return 0;
	}
}

void KeyboardInit(void)
{
    s_KBuffer.head = 0;
    s_KBuffer.tail = 0;
	memset(s_KBuffer.buffer, 0, sizeof(s_KBuffer.buffer));
}

void KeyboardRelease(void)
{
    s_KBuffer.head = 0;
    s_KBuffer.tail = 1;
    s_KBuffer.buffer[0] = -1;
}

void KeyboardChar(int Key)
{
	if (KeyboardGetBufNum(s_KBuffer.head, s_KBuffer.tail) < BUFSIZE - 1)
	{
		int s = 0;
		s_KBuffer.writing = TRUE;
		s_KBuffer.buffer[s_KBuffer.tail] = ((int)Key) | (s << 8);
		if (s_KBuffer.tail == BUFSIZE - 1)
		{
			s_KBuffer.tail = 0;
		}
		else
		{
			s_KBuffer.tail++;
		}
		s_KBuffer.writing = FALSE;
	}
}

int KeyboardGetKeyboardStatus(void)
{
    int status;
    if (KeyboardGetBufNum(s_KBuffer.head, s_KBuffer.tail) > 0)
    {
		/*
		MiscTrace("KeyboardGetBufNum: %d\n", 
		   KeyboardGetBufNum(s_KBuffer.head, s_KBuffer.tail));
		*/
        s_KBuffer.reading = TRUE;
        status = s_KBuffer.buffer[s_KBuffer.head];
		if (s_KBuffer.head == BUFSIZE - 1)
		{
			s_KBuffer.head = 0;
		}
		else
		{
			s_KBuffer.head++;
		}
		s_KBuffer.reading = FALSE;
        return status;
    }
    return 0;
}

//-------------------------------------------

void MiscTrace(const char *fmt, ...)
{
	char str[1000];
	va_list args;
	va_start(args, fmt);
	vsprintf(str, fmt, args);
#if USE_ANA
	__android_log_vprint(ANDROID_LOG_INFO, SSS_APPNAME, fmt, args);
#else
#ifdef WIN32
	OutputDebugStringA(str);
#else
	fprintf(stderr, "%s", str);
#endif
#endif
    va_end(args);
}

void MiscAppInit(void)
{
#if defined(WIN32) && defined(_DEBUG) && USE_WIN_LEAK
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#ifdef _CONSOLE
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
#else
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
#endif
#endif
	/* Test Memory Leak */
	/*
	malloc(10);
	*/
}

void MiscAppExit(void)
{
#if defined(WIN32) && defined(_DEBUG) && USE_WIN_LEAK
	_CrtDumpMemoryLeaks();
#endif
}
