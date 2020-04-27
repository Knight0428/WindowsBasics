#include <Windows.h>


//�������ڻص�����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstance,           //��ǰʵ�����
	HINSTANCE hPrevInstance,       //ǰһ��ʵ�����
	LPSTR lpCmdLine,               //������
	int nCmdShow                   //������ʾ��ʽ
)
{
	//1����ʼ��������
	static TCHAR szAppName[] = TEXT("MyWindows");         //������ƴ�Ӻ�
	HWND hwnd;             //���ھ��
	MSG msg;               //��Ϣ
	WNDCLASS wndclass;     //������

	wndclass.style = CS_HREDRAW | CS_VREDRAW;   //���ڷ��
	wndclass.lpfnWndProc = WndProc;             //���ڹ��̺���
	wndclass.cbClsExtra = 0;                    //������ṹ�����ֽ���
	wndclass.cbWndExtra = 0;                    //����ʵ����Ķ����ֽ���
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);    //����ͼ�꣬ʹ��ϵͳĬ��ͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);      //�����
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   //������ˢ
	wndclass.lpszMenuName = NULL;            //�˵�
	wndclass.lpszClassName = szAppName;      //��������

	//2��ע�ᴰ����
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("���������Ҫ��windows NT����ִ�У�"), szAppName, MB_ICONERROR);
		return 0;
	}

	//3����������ʵ��
	hwnd = CreateWindow(
		szAppName,                       //��������
		TEXT("��һ��windows����"),       //������
		WS_OVERLAPPEDWINDOW,             //���ڷ��
		CW_USEDEFAULT,                   //ˮƽλ�ã�Ĭ��
		CW_USEDEFAULT,                   //��ֱλ�ã�Ĭ��
		CW_USEDEFAULT,                   //��ȣ�Ĭ��
		CW_USEDEFAULT,                   //�߶ȣ�Ĭ��
		NULL,                            //�����ھ��
		NULL,                            //�˵����
		hInstance,                       //ʵ�����
		NULL                             //���ڴ�������
	);

	//4����ʾ����
	ShowWindow(hwnd, nCmdShow);

	//5�����´���
	UpdateWindow(hwnd);

	//6����Ϣѭ��
	while (GetMessage(&msg, NULL, 0, 0))           //��ȡ��Ϣ
	{
		TranslateMessage(&msg);                    //������Ϣ
		DispatchMessage(&msg);                     //�ɷ���Ϣ
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
		DrawText(hdc, TEXT("�����ҵĵ�һ�����ڳ���"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;


	case WM_LBUTTONUP:
		MessageBox(hwnd, TEXT("���ڱ�����һ��"), TEXT("��ʾ"), MB_OK);
		return 0;


	case WM_CLOSE:
		if (MessageBox(hwnd, TEXT("�����Ƿ�رգ�"), TEXT("��ȷ��"), MB_YESNO) == IDYES)
			DestroyWindow(hwnd);
		else
			return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}


	//������Ϣʹ��ϵͳĬ�ϵĴ��ڴ�����
	return DefWindowProc(hwnd, message, wParam, lParam);

}
