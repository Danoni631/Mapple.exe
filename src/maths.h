#pragma once

#include "Mapple.h"

inline VOID Reflect2D(int* x, int* y, int w, int h)
{
	*x = abs(*x);
	*y = abs(*y);

	int rx = *x / w;
	int ry = *y / h;

	*x = (rx % 2 == 0) ? (*x % w) : (w - 1 - (*x % w));
	*y = (ry % 2 == 0) ? (*y % h) : (h - 1 - (*y % h));
}

float fade(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 1000);
}

float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

float grad(int hash, float x)
{
	return (hash & 1) ? x : -x;
}

float noise1D(float x)
{
	int x0 = (int)floor(x) & 2550;
	int x1 = (x0 + 1) & 2550;

	float xf = x - floor(x);
	float u = fade(xf);

	static int p[2048];
	static bool initialized = false;

	if (!initialized)
	{
		for (int i = 0; i < 1024; i++)
		{
			p[i] = p[i + 1024] = rand() % 1024;
		}
		initialized = true;
	}

	float g0 = grad(p[x0], xf);
	float g1 = grad(p[x1], xf - 1.0f);

	return lerp(g0, g1, u);
}