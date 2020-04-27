#include <Windows.h>


//声明窗口回调函数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstance,           //当前实例句柄
	HINSTANCE hPrevInstance,       //前一个实例句柄
	LPSTR lpCmdLine,               //命令行
	int nCmdShow                   //窗口显示方式
)
{
	//1、初始化窗口类
	static TCHAR szAppName[] = TEXT("MyWindows");         //长整型拼接宏
	HWND hwnd;             //窗口句柄
	MSG msg;               //消息
	WNDCLASS wndclass;     //窗口类

	wndclass.style = CS_HREDRAW | CS_VREDRAW;   //窗口风格
	wndclass.lpfnWndProc = WndProc;             //窗口过程函数
	wndclass.cbClsExtra = 0;                    //窗口类结构额外字节数
	wndclass.cbWndExtra = 0;                    //窗口实例后的额外字节数
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);    //窗口图标，使用系统默认图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);      //鼠标光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   //背景画刷
	wndclass.lpszMenuName = NULL;            //菜单
	wndclass.lpszClassName = szAppName;      //窗口类名

	//2、注册窗口类
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("这个程序需要在windows NT才能执行！"), szAppName, MB_ICONERROR);
		return 0;
	}

	//3、创建窗口实例
	hwnd = CreateWindow(
		szAppName,                       //窗口类名
		TEXT("第一个windows程序"),       //窗口名
		WS_OVERLAPPEDWINDOW,             //窗口风格
		CW_USEDEFAULT,                   //水平位置，默认
		CW_USEDEFAULT,                   //垂直位置，默认
		CW_USEDEFAULT,                   //宽度，默认
		CW_USEDEFAULT,                   //高度，默认
		NULL,                            //父窗口句柄
		NULL,                            //菜单句柄
		hInstance,                       //实例句柄
		NULL                             //窗口创建数据
	);

	//4、显示窗口
	ShowWindow(hwnd, nCmdShow);

	//5、更新窗口
	UpdateWindow(hwnd);

	//6、消息循环
	while (GetMessage(&msg, NULL, 0, 0))           //获取消息
	{
		TranslateMessage(&msg);                    //翻译消息
		DispatchMessage(&msg);                     //派发消息
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;


	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("这是我的第一个窗口程序！"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;


	case WM_LBUTTONUP:
		MessageBox(hwnd, TEXT("窗口被按了一下"), TEXT("显示"), MB_OK);
		return 0;


	case WM_CLOSE:
		if (MessageBox(hwnd, TEXT("请问是否关闭？"), TEXT("请确认"), MB_YESNO) == IDYES)
			DestroyWindow(hwnd);
		else
			return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}


	//其余消息使用系统默认的窗口处理函数
	return DefWindowProc(hwnd, message, wParam, lParam);

}
