#pragma once

class MainEntryClass
{

public:
	MainEntryClass();
	~MainEntryClass();

private:
	D2D_RECT_F m_Rect;

public:
	HRESULT Start();
	void Update();
	void Render();
};

