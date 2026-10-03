#pragma once

#include "Mapple.h"

#define NOTSRCINVERT 0x999999

int w = GetSystemMetrics(0);
int h = GetSystemMetrics(1);

#define SquareWave(t, freq, sampleCount) (((BYTE)(2.f * (FLOAT)(freq) * ((t) / (FLOAT)(sampleCount))) % 2) == 0 ? 1.f : -1.f)

#define PI 3.141592653589793238462643383279

enum
{
	MEM_ALLOC_TYPES = MEM_COMMIT | MEM_RESERVE
};
/*
VOID WINAPI ci(HDC hdc, int x, int y, int w, int h)
{
	POINT hex[8];

	int inc = 0;

	double cx = x + w / 2.0;
	double cy = y + h / 2.0;
	double r = min(w, h) / 2.0;

	for (int i = 0; i < 3; i++)
	{
		double a = (120.0f * i - inc) * PI / 180.0;

		hex[i].x = (cx + r * sin(a));
		hex[i].y = (cy + r * cos(a));

	}
	inc++;

	HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	SelectObject(hdc, brush);

	for (int z = 0; z < x; z += 10) {
		StretchBlt(hdc, z, -10 + (rand() % 21), 10, h, hdc, z, 0, 10, h, PATINVERT);
	}
	for (int z = 0; z < y; z += 10) {
		StretchBlt(hdc, -10 + (rand() % 21), z, w, 10, hdc, 0, z, w, 10, PATINVERT);
	}

	HRGN hrgn = CreatePolygonRgn(hex, 3, WINDING);

	SelectClipRgn(hdc, hrgn);

	BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);

	DeleteObject(brush);
	DeleteObject(hrgn);
	ReleaseDC(NULL, hdc);
}
*/

VOID Shaking(HDC hdc, DWORD rop)
{
	BitBlt(hdc, 2, 0, w, h, hdc, 0, 0, rop);
	Sleep(1);
	BitBlt(hdc, 0, 2, w, h, hdc, 0, 0, rop);
	Sleep(1);
	BitBlt(hdc, 0, 0, w, h, hdc, 2, 0, rop);
	Sleep(1);
	BitBlt(hdc, 0, 0, w, h, hdc, 0, 2, rop);
	Sleep(1);
}

namespace GDIPayloads
{
	DWORD WINAPI TrashBlur(LPVOID lpParam)
	{
		HDC hdc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(hdc);

		HBITMAP bmp = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(dcCopy, bmp);

		BLENDFUNCTION blur = { 0 };

		blur.BlendOp = AC_SRC_OVER;
		blur.BlendFlags = 0;
		blur.AlphaFormat = 0;
		blur.SourceConstantAlpha = 10;

		while (1)
		{
			StretchBlt(dcCopy, 25, 25, w, h, hdc, 0, 0, w, h, SRCERASE);
			AlphaBlend(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);
			Sleep(1);
		}

		return 0;
	}

	DWORD WINAPI DarkandBright(LPVOID lpParam)
	{
		while (1)
		{
			HDC hdc = GetDC(0);
			Shaking(hdc, SRCAND);
			Sleep(1);
			Shaking(hdc, SRCCOPY);
			Sleep(1);
			Shaking(hdc, SRCPAINT);
			Sleep(1);
			ReleaseDC(0, hdc);
		}
	}

	DWORD WINAPI Texts(LPVOID lpParam)
	{
		HDC hdc = GetDC(0);

		LOGFONTW lFont = { 0 };

		lFont.lfWidth = 20;
		lFont.lfHeight = 60;
		lFont.lfOrientation = 400;
		lFont.lfWeight = 600;
		lFont.lfUnderline = true;
		lFont.lfQuality = DRAFT_QUALITY;
		lFont.lfPitchAndFamily = DEFAULT_PITCH | FF_ROMAN;

		lstrcpy(lFont.lfFaceName, L"Arial Black");

		int state = 0;
		int r = 0;
		int g = 0;
		int b = 0;

		while (true)
		{
			if (state == 0)
			{
				g += 5; if (g >= 255) state = 1;
			}

			else if (state == 1)
			{
				r -= 5; if (r <= 0) state = 2;
			}

			else if (state == 2)
			{
				b += 5; if (b >= 255) state = 3;
			}

			else if (state == 3)
			{
				g -= 5; if (g <= 0) state = 4;
			}

			else if (state == 4)
			{
				r += 5; if (r >= 255) state = 5;
			}

			else if (state == 5)
			{
				b -= 5; if (b <= 0) state = 0;
			}

			lFont.lfEscapement = rand() % 60;

			HFONT hFont = CreateFontIndirectW(&lFont);
			SelectObject(hdc, hFont);

			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			SetBkColor(hdc, RGB(r, g, b));

			int index = rand() % 40;

			TextOutA(hdc, rand() % w, rand() % h, "Mapple.exe", lstrlenA("Mapple.exe"));

			Sleep(rand() % 5);

			if (rand() % 25 == 24)
			{
				Redraw();
			}
		}

		return 0;
	}

	DWORD WINAPI MovingRGB(LPVOID lpParam)
	{
		HDC hdc = GetDC(0);
		HDC dcCopy = CreateCompatibleDC(hdc);

		BITMAPINFO bmpi = { 0 };
		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = -h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;

		PRGBQUAD_t prgbDst = nullptr;
		HBITMAP hbmDst = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&prgbDst, NULL, 0);
		SelectObject(dcCopy, hbmDst);

		PRGBQUAD_t prgbSrc =
		(PRGBQUAD_t)VirtualAlloc(NULL, w * h * sizeof(RGBQUAD_t), MEM_ALLOC_TYPES, PAGE_READWRITE);

		int t = 0;

		FLOAT div = (float)t / 30.f;
		
		int a = 0;
		int b = 0;
		int c = 0;

		while (true)
		{
			BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
			memcpy(prgbSrc, prgbDst, w * h * sizeof(RGBQUAD));
			RGBQUAD_t rgbDst;

			for (INT y = 0; y < h; y++)
			{
				for (INT x = 0; x < w; x++)
				{
					a += 1;
					b = sin(a + 1) * 2;
					c = cos(1) * 2;

					UINT u = x + (INT)b;
					UINT v = y + (INT)c;

					u %= w;
					v %= h;

					rgbDst = prgbSrc[v * w + u];
					rgbDst.r += ~prgbSrc[y * w + x].r / 54;
					rgbDst.g += ~prgbSrc[y * w + x].g / 54;
					rgbDst.b += ~prgbSrc[y * w + x].b / 54;
					prgbDst[y * w + x] = rgbDst;
				}
			}

			BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);
			Sleep(10);
		}

		VirtualFree(prgbSrc, 0, MEM_RELEASE);
		DeleteObject(hbmDst);
		DeleteDC(dcCopy);
		ReleaseDC(NULL, hdc);

		return 0;
	}

	DWORD WINAPI Icons(LPVOID lpParam)
	{
		HDC hdc = GetWindowDC(GetDesktopWindow());

		while (true)
		{
			int x = 0;
			int y = 0;

			int sel = rand() % 2 + 1;
			double wave = 0;
			int i = 0;

			if (sel == 1)
			{
				x = 0;
				y = rand() % h;

				for (; x < w; x += 3)
				{
					DrawIcon(hdc, x, y + wave * cos(i), LoadIcon(0, IDI_ERROR));
					i += 0.05;
					wave += 0.32;
					Sleep(1);
				}
			}

			else if (sel == 2)
			{
				x = w;
				y = rand() % h;

				for (; x > 0; x -= 3)
				{
					DrawIcon(hdc, x, y + wave * sin(i), LoadIcon(0, IDI_WARNING));
					i += 0.05;
					wave += 0.32;
					Sleep(1);
				}
			}
		}
	}

	DWORD WINAPI SierspinskiHSL(LPVOID lpParam)
	{

		HDC hdc = GetDC(0);
		HDC dcCopy = CreateCompatibleDC(hdc);

		BITMAPINFO bmi = { 0 };
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biWidth = w;
		bmi.bmiHeader.biHeight = -h;

		PRGBQUAD_t prgbDst = nullptr;
		HBITMAP hbmTemp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&prgbDst, NULL, 0);
		SelectObject(dcCopy, hbmTemp);

		PRGBQUAD_t prgbSrc =
		(PRGBQUAD_t)VirtualAlloc(NULL, w * h * sizeof(RGBQUAD_t), MEM_ALLOC_TYPES, PAGE_READWRITE);

		float angle = 0.0f;

		HSL hsl;

		while (1)
		{
			BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
			memcpy(prgbSrc, prgbDst, w * h * sizeof(RGBQUAD_t));

			float frequency = 0.05f;
			float amplitude = 20.0f;

			int t = 0;
			const float f = 1.0f / 4.0f;

			for (int y = 0; y < h; y++)
			{
				int offsetX = (int)(sinf(y * frequency + angle) * amplitude);

				for (int x = 0; x < w; x++)
				{
					int srcX = (x + offsetX) % w;
					if (srcX < 0) srcX += w;

					int dstIdx = y * w + x;
					int srcIdx = y * w + srcX;

					int rawU = ~((x + t) & y);
					int rawV = ~((y + t) & x);

					UINT u = (UINT)(abs(rawU) % w);
					UINT v = (UINT)(abs(rawV) % h);

					Reflect2D((PINT)&u, (PINT)&v, w, h);

					RGBQUAD_t rgbDst = prgbSrc[v * w + u];
					RGBQUAD_t rgbSrc = prgbSrc[y * w + x];

					if (!rgbSrc.rgb)
					{
						rgbSrc.rgb = 1;
					}

					rgbDst.rgb &= rgbDst.rgb % ((rgbSrc.rgb << 8) + 1);
					FLOAT r = (FLOAT)rgbDst.r * f + (FLOAT)rgbSrc.r * (1.f - f);
					FLOAT g = (FLOAT)rgbDst.g * f + (FLOAT)rgbSrc.g * (1.f - f);
					FLOAT b = (FLOAT)rgbDst.b * f + (FLOAT)rgbSrc.b * (1.f - f);
					rgbDst.rgb = ((BYTE)b | ((BYTE)g << 8) | ((BYTE)r << 16));

					hsl = RGBtoHSL(rgbDst);
					hsl.h /= 1.0125f;
					hsl.s /= 1.0125f;
					hsl.l /= 1.0125f;

					if (hsl.l < .2f)
					{
						hsl.l += .2f;
					}

					rgbDst = HSLtoRGB(hsl);
					prgbDst[y * w + x] = rgbDst;
				}
			}

			BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);
			angle += 0.15f;
			Sleep(10);
		}

		VirtualFree(prgbSrc, 0, MEM_RELEASE);
		DeleteObject(hbmTemp);
		DeleteDC(dcCopy);
		ReleaseDC(NULL, hdc);

		return 0;
	}

	DWORD WINAPI SquareWaveHSL(LPVOID lpParam)
	{
		HDC hdc = GetDC(0);
		HDC dcCopy = CreateCompatibleDC(hdc);

		BITMAPINFO bmpi = { 0 };
		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = -h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;

		PRGBQUAD_t prgbSrc =
		(PRGBQUAD_t)VirtualAlloc(NULL, w * h * sizeof(RGBQUAD_t), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		PRGBQUAD_t prgbDst = nullptr;

		HBITMAP hbmDst = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&prgbDst, NULL, 0);
		SelectObject(dcCopy, hbmDst);

		FLOAT f = 0.f;

		while (true)
		{
			BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
			memcpy(prgbSrc, prgbDst, w * h * sizeof(RGBQUAD_t));

			RGBQUAD_t rgbDst;
			RGBQUAD_t rgbSrc;

			int t = 0;

			for (INT y = 0; y < h; y++)
			{
				FLOAT a = SquareWave(t + y, 10, h) * 10.f;

				for (INT x = 0; x < w; x++)
				{
					UINT u = x + (INT)a;
					UINT v = y;

					u %= w;
					v %= h;


					Reflect2D((PINT)&u, (PINT)&v, w, h);

					COLORREF rgbSrcRgb = 0;
					COLORREF rgbDstRgb = 0;

					rgbDst = prgbSrc[v * w + u];
					rgbSrc = prgbSrc[y * w + x];

					if (!rgbSrcRgb)
					{
						rgbSrcRgb = 1;
					}

					rgbDstRgb &= rgbDstRgb % ((rgbSrcRgb << 8) + 1);
					FLOAT _r = (FLOAT)rgbDst.r * f + (FLOAT)rgbSrc.r * (1.f - f);
					FLOAT _g = (FLOAT)rgbDst.g * f + (FLOAT)rgbSrc.g * (1.f - f);
					FLOAT _b = (FLOAT)rgbDst.b * f + (FLOAT)rgbSrc.b * (1.f - f);
					rgbDstRgb = ((BYTE)_b | ((BYTE)_g << 8) | ((BYTE)_r << 16));

					HSL hsl = RGBtoHSL(rgbDst);
					hsl.h = (FLOAT)fmod((DOUBLE)hsl.h + (DOUBLE)(x + y) / 100000.0 + 0.05, 1.0);
					hsl.s = 1.f;

					if (hsl.l < .2f)
					{
						hsl.l += .2f;
					}

					rgbDst = HSLtoRGB(hsl);
					prgbDst[y * w + x] = rgbDst;
				}
			}

			BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);
			Sleep(10);
		}

		VirtualFree(prgbSrc, 0, MEM_RELEASE);
		DeleteObject(hbmDst);
		DeleteDC(dcCopy);
		ReleaseDC(NULL, hdc);

		return 0;
	}

	/*
	DWORD WINAPI TrianglePayload(LPVOID lpParam)
	{
		HDC hdc = GetDC(0);

		RECT rect;
		GetWindowRect(GetDesktopWindow(), &rect);
		
		int tw = rect.right - rect.left;
		int th = rect.bottom - rect.top;

		for (int t = 0;; t++)
		{
			const int size = max(tw * 3, th * 3);
			int x = tw - tw / 2, y = th - th / 2;

			for (int repeat = 0; repeat < 100; ++repeat)
			{
				for (int i = 0; i < size; i += 25)
				{
					ci(hdc, x - i * 2, y - i * 2, i, i);
				}
			}
		}
	}
	*/

	DWORD WINAPI Blur(LPVOID lpParam)
	{
		HDC hdc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(hdc);
		HBITMAP bmp = CreateCompatibleBitmap(hdc, w, h);
		
		SelectObject(dcCopy, bmp);

		BLENDFUNCTION blur = { 0 };

		blur.BlendOp = AC_SRC_OVER;
		blur.BlendFlags = 0;
		blur.AlphaFormat = 0;
		blur.SourceConstantAlpha = 50;

		int a = 0;
		int b = 0;
		int c = 0;
		
		while (1)
		{
			hdc = GetDC(NULL);
			BitBlt(dcCopy, 0, 0, w, h, hdc, b, c, SRCCOPY);
			AlphaBlend(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);
			a += 1;
			b = sin(a / 21.f) * 10;
			c = cos(a / 20.f) * 10;
			ReleaseDC(0, hdc);
		}
	}

	DWORD WINAPI Ors(LPVOID lpParam)
	{
		HDC hdc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(hdc);

		int ws = w / 4;
		int hs = h / 4;

		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = ws;
		bmpi.bmiHeader.biHeight = hs;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		PRGBQUAD_t rgbquad = NULL;

		bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		int i = 0;
		double angle = 0.f;


		SetStretchBltMode(hdc, COLORONCOLOR);
		SetStretchBltMode(dcCopy, COLORONCOLOR);


		while (1)
		{
			StretchBlt(dcCopy, 0, 0, ws, hs, hdc, 0, 0, w, h, SRCCOPY);
			RGBQUAD_t rgbquadCopy;

			for (int x = 0; x < ws; x++)
			{
				for (int y = 0; y < hs; y++)
				{
					int index = y * ws + x;

					int cx = (x - (ws / 2));
					int cy = (y - (hs / 2));

					int zx = cos(angle) * cx - tan(angle) * cy;
					int zy = sin(angle) * cx + log(angle) * cy;

					int fx = (zx + i) & (zy + i);

					rgbquad[index].r += fx;
					rgbquad[index].g += fx;
					rgbquad[index].b += fx;
				}
			}

			i++; angle += 0.01f;

			StretchBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);
			Sleep(500);
		}

		return 0;
	}

	DWORD WINAPI PatBltEff(LPVOID lpParam)
	{
		while (true)
		{
			HDC hdc = GetDC(0);
			HDC dcCopy = CreateCompatibleDC(hdc);
			HBITMAP bm = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(dcCopy, bm);
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(hdc, brush);
			PatBlt(hdc, 0, 0, w, h, PATINVERT);
			DeleteObject(brush);
			DeleteObject(dcCopy);
			DeleteObject(bm);
			ReleaseDC(0, hdc);
			Sleep(1);
		}
	}

	DWORD WINAPI BitBlts(LPVOID lpParam)
	{
		HDC dc = GetDC(0);

		while (true)
		{
			if (rand() % 2 == 0)
			{
				BitBlt(dc, 1, 0, w, h, dc, 0, 1, NOTSRCINVERT);
			}
			else
			{
				BitBlt(dc, 1, 0, w, h, dc, 0, 1, SRCINVERT);
			}

			Sleep(rand() % 5);
		}
	}
}