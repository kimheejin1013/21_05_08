﻿#include "stdafx.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Application* app = &Application::Get();
	GraphicRenderer* renderer = GraphicRenderer::Get();

	if (FAILED(app->OnCreate(hInstance, nCmdShow))) return FALSE;
	if (FAILED(renderer->OnCreateDeviceResource(app->GetHwnd()))) return FALSE;

	MainEntryClass* pMain = new MainEntryClass();
	if (FAILED(pMain->Start())) return E_FAIL;

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			renderer->BeginDraw();
			{
				pMain->Render();
			}
			renderer->EndDraw();
		}
	}

	SAFE_DELETE(pMain);

	return (int)msg.wParam;
}
