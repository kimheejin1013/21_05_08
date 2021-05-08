#include "stdafx.h"
#include "MainEntryClass.h"

MainEntryClass::MainEntryClass()
{
}

MainEntryClass::~MainEntryClass()
{
}

HRESULT MainEntryClass::Start()
{
	m_Rect = D2D1::RectF(

		_Application.Width / 2.0f - 50.0f,
		_Application.Height / 2.0f - 50.0f,
		100.0f,
		100.0f);


	return S_OK;
}

void MainEntryClass::Update()
{
}

void MainEntryClass::Render()
{
	_RenderTarget->DrawRectangle(m_Rect, _Renderer->GetBrush());
	

}
