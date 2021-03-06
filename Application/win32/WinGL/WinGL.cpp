// WinGL.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WinGL.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "GLRenderer.h"
#include "freeImage/FreeImage.h"
#include "GLBitmap.h"



#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名


int m_width = 800;
int m_height = 600;
EGLConfig m_config;
EGLSurface m_surface;
EGLContext m_context;
EGLDisplay m_display;

HWND m_hWnd;

GLRenderer* m_render;



// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	


	// TODO: 在此处放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINGL, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINGL));


	// 主消息循环:
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (msg.message == WM_DESTROY || msg.message == WM_CLOSE)
		{
			break;
		}
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (m_render)
			{
				m_render->onDrawFrame();
			}
			eglSwapBuffers(m_display, m_surface);
		}
	}



	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINGL));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINGL);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

bool initOpenGLES()
{
	const EGLint attrbs[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_DEPTH_SIZE, 24,
		EGL_NONE
	};
	EGLint format(0);
	EGLint numConfigs(0);
	EGLint major;
	EGLint minor;

	m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(m_display, &major, &minor);
	eglChooseConfig(m_display, attrbs, &m_config, 1, &numConfigs);
	eglGetConfigAttrib(m_display, m_config, EGL_NATIVE_VISUAL_ID, &format);
	m_surface = eglCreateWindowSurface(m_display, m_config, m_hWnd, nullptr);

	EGLint attr[] = { EGL_CONTEXT_CLIENT_VERSION, 3 , EGL_NONE, EGL_NONE };
	m_context = eglCreateContext(m_display, m_config, 0, attr);

	if (eglMakeCurrent(m_display, m_surface, m_surface, m_context))
	{
		return false;
	}

	return true;

}

void destoryOpenGLES()
{
	if (m_display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (m_context != EGL_NO_CONTEXT)
		{
			eglDestroyContext(m_display, m_context);
		}
		if (m_surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(m_display, m_surface);
		}
		eglTerminate(m_display);

		m_display = EGL_NO_DISPLAY;
		m_context = EGL_NO_CONTEXT;
		m_surface = EGL_NO_SURFACE;
	}

	if (m_render != nullptr)
	{
		delete m_render;
		m_render = nullptr;
	}

}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量ff 
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, m_width, m_height, nullptr, nullptr, hInstance, nullptr);
	m_hWnd = hWnd;
	if (!hWnd)
	{
		return FALSE;
	}
	initOpenGLES();
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	/*
	m_render = new GLRenderer();
	m_render->enter(ID_EFFECT_BASIC_DRAW);
	m_render->onSurfaceCreate();
	m_render->onSurfaceChanged(m_width, m_height);
	*/

	m_render = new GLRenderer();
	m_render->enter(ID_EFFECT_TEXTURE_DRAW);
	m_render->onSurfaceCreate();

	const char* imagPath = "C:\\Users\Administrator\Documents\Code\MediaCode\OpenGLESLearn-build\Debug\data\image\main.jpg";
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(imagPath, 0);

	//2 ¼ÓÔØÍ¼Æ¬
	FIBITMAP* dib = FreeImage_Load(fifmt, imagPath, 0);

	//3 ×ª»¯Îªrgb 24É«
	dib = FreeImage_ConvertTo24Bits(dib);

	//4 »ñÈ¡Êý¾ÝÖ¸Õë
	BYTE* pixels = (BYTE*)FreeImage_GetBits(dib);

	int     width = FreeImage_GetWidth(dib);
	int     height = FreeImage_GetHeight(dib);

	m_render->onSurfaceChanged(m_width, m_height);
	

	return TRUE;
}



//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		destoryOpenGLES();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
