#include "stdafx.h"

GraphicRenderer::GraphicRenderer()
	: m_D2DFactory(nullptr), m_DWriteFactory(nullptr), m_WICFactory(nullptr), m_RenderTarget(nullptr)
{
}

GraphicRenderer::~GraphicRenderer()
{
	SAFE_RELEASE(m_SolidBrush);

	SAFE_RELEASE(m_D2DFactory);
	SAFE_RELEASE(m_DWriteFactory);
	SAFE_RELEASE(m_WICFactory);
	SAFE_RELEASE(m_RenderTarget);

	//	COM ��ü (Component Object Model)
	CoUninitialize();
}

HRESULT GraphicRenderer::OnCreateDeviceResource(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	//	Ŭ���̾�Ʈ ��Ʈ ����Ѵ�
	D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);
	HResult(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_D2DFactory));

	//	�׷��� ī�带 ����ϱ� ���� D2D ���丮�� �ҷ��´� (���丮 �޼��� ����)
	HResult(
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_DWriteFactory),
			reinterpret_cast<IUnknown**>(&m_DWriteFactory))
	);

	//	COM ��ü ����
	//	���丮 ��� �� �� COM ��ü�� �ʿ���!
	CoInitialize(nullptr);
	HResult(
		CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC,
			IID_PPV_ARGS(&m_WICFactory)));

	//	���� Ŭ���̾�Ʈ ��ġ�� ����� ����
	//	���� ���� ������ �ִ� hWnd(�ڵ�) ���ٰ� �׷��޶� �����ش�
	HResult(
		m_D2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&m_RenderTarget));

	if (FAILED(m_RenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black), &m_SolidBrush
	))) return E_FAIL;

	return S_OK;
}

void GraphicRenderer::OnResize(UINT width, UINT height)
{
	if (m_RenderTarget) m_RenderTarget->Resize(D2D1::SizeU(width, height));
}

void GraphicRenderer::BeginDraw()
{
	m_RenderTarget->BeginDraw();
	m_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Gold));
}

void GraphicRenderer::EndDraw()
{
	m_RenderTarget->EndDraw();
}

HRESULT GraphicRenderer::CreateBitmap(ID2D1Bitmap ** ppBitmap, std::wstring filePath, float width, float height, float alphaThresholdPercent, WICBitmapDitherType diter, WICBitmapPaletteType palette)
{

	return E_NOTIMPL;
}
