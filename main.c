#include <Windows.h>
#include <time.h>

HWND window, text, edit, but;

#pragma comment(lib, "winmm.lib")

BOOLEAN Enable = FALSE;



LRESULT CALLBACK wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if (msg == WM_COMMAND)
	{
		if (LOWORD(wParam) == 1000)
		{
			if (Enable == FALSE)
			{
				Enable = TRUE;
				PlaySoundW(MAKEINTRESOURCEW(102), 0, SND_RESOURCE | SND_LOOP | SND_ASYNC);
			}
			else
			{
				MessageBoxW(0, L"Вы уже включили сектор газа", L"Предупреждение", MB_ICONWARNING);
			}
		}
		if (LOWORD(wParam) == 1001)
		{
			if (Enable == TRUE)
			{
				Enable = FALSE;
				PlaySoundW(NULL, 0, SND_ASYNC);
			}
			else
			{
				MessageBoxW(0, L"Сектор газа выключен", L"Предупреждение", MB_ICONWARNING);
			}
		}

		if (LOWORD(wParam) == 123)
		{
			WCHAR txt[8192] = { 0 };
			GetWindowTextW(edit, txt, 8192);

			SetWindowTextW(text, txt);
		}
		
	}


	


	if (msg == WM_CLOSE)
	{
		if (MessageBoxW(0, L"Вы действительно хотите покинуть приложение?", L"Предупреждение", MB_YESNO | MB_ICONWARNING) == IDYES)
		{
			PostQuitMessage(0);
			return 0;
		}
		else
		{
			return 0;
		}
	}

	return DefWindowProcW(hWnd, msg, wParam, lParam);
}


void GenerateRandomClass(WCHAR classname[200], int len)
{
	WCHAR symbols[] = L"1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";

	for (int i = 0; i < len; i++)
	{
		classname[i] = symbols[rand() % 62];
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	srand(time(0));
	WCHAR Class[200];
	GenerateRandomClass(Class, rand() % 19);

	HMENU hMenu = CreateMenu();
	HMENU status = CreateMenu();

	WNDCLASSEXW wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.hInstance = hInstance;
	wc.lpszClassName = Class;
	wc.lpfnWndProc = wndproc;

	RegisterClassExW(&wc);

	window = CreateWindowExW(0, Class, Class, WS_VISIBLE | WS_SYSMENU, 400, 400, 500, 400, 0, 0, hInstance, 0);
	text = CreateWindowExW(0, L"STATIC", L"Mytext", WS_CHILD | WS_VISIBLE, 10, 10, 200, 30, window, 0, 0, 0);
	edit = CreateWindowExW(0, L"EDIT", L"I am edit", WS_CHILD | WS_VISIBLE, 10, 50, 200, 50, window, 0, 0, 0);
	but = CreateWindowExW(0, L"BUTTON", L"Click me", WS_CHILD | WS_VISIBLE, 10, 200, 150, 30, window, (HMENU)123, 0, 0);

	

	AppendMenuW(status, MF_STRING, 1000, L"Включить сектор газа");
	AppendMenuW(status, MF_STRING, 1001, L"Выключить сектор газа");
	AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)status, L"Сектор газа");


	SetMenu(window, hMenu);

	MSG msg;
	while (GetMessageW(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}





}