#pragma once
namespace RenderUtil
{

	void StartScene();
	void Render(DWORD color,RECT size);
	void EndScene();
	void Init(int argc, char**argv, void(*displayFunc)(), void(*OnMouseClick)(float posX, float posY), int width, int height, int wcount, int hcount);
	void Loop();
	int  GetCellSize();

};

