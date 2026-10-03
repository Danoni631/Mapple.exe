#pragma once

#include "Mapple.h"

#define SAMPLE_RATE 8000
#define SECONDS 30
#define BUFFER_SIZE (SAMPLE_RATE * SECONDS)

namespace Bytebeats
{
	DWORD WINAPI Sound1(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE, SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
			return 1;

		std::vector<unsigned char> buffer(BUFFER_SIZE);

		for (int t = 0; t < BUFFER_SIZE; ++t)
		{
			buffer[t] =
			(unsigned char)
			(
				(t * (t << 2 | t >> 7)) + (t * ((t >> 6 | t >> 13) & 50))
			);
		}

		WAVEHDR header = { (LPSTR)buffer.data(), BUFFER_SIZE, 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);
		return 0;
	}

	DWORD WINAPI Sound2(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE, SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
			return 1;

		std::vector<unsigned char> buffer(BUFFER_SIZE);

		for (int t = 0; t < BUFFER_SIZE; ++t)
		{
			buffer[t] =
			(unsigned char)
			(
				((t * 1 & t >> 3) | (t * 7 & t >> 6)) +
				(t * ((t >> 12 | t >> 89) & 63 & t >> 7) + (17 & t >> 20))
			);
		}

		WAVEHDR header = { (LPSTR)buffer.data(), BUFFER_SIZE, 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);
		return 0;
	}

	DWORD WINAPI Sound3(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
			return 1;
		}

		DWORD bufferSize = 22050 * 30;
		char* buffer = new char[bufferSize];

		for (DWORD t = 0; t < bufferSize; ++t)
		{
			buffer[t] = static_cast<char>(((t >> t) + ((t | t % 257) + (t & t >> 8))) + (t >> t));
		}

		WAVEHDR header = { 0 };
		header.lpData = buffer;
		header.dwBufferLength = bufferSize;

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE)) {
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		delete[] buffer;

		return 0;
	}

	DWORD WINAPI Sound4(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE, SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
			return 1;

		std::vector<unsigned char> buffer(BUFFER_SIZE);

		for (int t = 0; t < BUFFER_SIZE; ++t)
		{
			buffer[t] =
			(unsigned char)
			(
				(t * (61 ^ t >> 5) + (t >> t))
			);
		}

		WAVEHDR header = { (LPSTR)buffer.data(), BUFFER_SIZE, 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);
		return 0;
	}

	DWORD WINAPI Sound5(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE, SAMPLE_RATE, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
			return 1;

		std::vector<unsigned char> buffer(BUFFER_SIZE);

		for (int t = 0; t < BUFFER_SIZE; ++t)
		{
			buffer[t] =
			(unsigned char)
			(
				(
					(((2 * t % 2556) /
					(1 + (t >> 10 & (t / (1 + (t / 16 & 8192 ? 2 : 4)) & 16 ? 31 : 120)))) * t) >> 5
				) + (t >> t)
			);
		}

		WAVEHDR header = { (LPSTR)buffer.data(), BUFFER_SIZE, 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);
		return 0;
	}

	DWORD WINAPI Sound6(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut = 0;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
			return 1;
		}

		DWORD bufferSize = 22050 * 30;
		char* buffer = new char[bufferSize];

		for (DWORD t = 0; t < bufferSize; ++t)
		{
			buffer[t] = static_cast<char>
			(
				((((t / 8 | 0) ^ (t / 8 | 0) - 1280) % 11 * t / 2 & 127) +
				(((t / 512 | 0) ^ (t / 500 | 0) - 2) % 13 * t / 2 & 127)) * 5
			);
		}

		WAVEHDR header = { 0 };
		header.lpData = buffer;
		header.dwBufferLength = bufferSize;

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE)) {
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		delete[] buffer;

		return 0;
	}
}