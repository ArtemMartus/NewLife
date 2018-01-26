#pragma once
namespace RenderUtil
{

	void StartScene();
	void Render(DWORD color,RECT size);
	void EndScene();
	void Init(int argc, char**argv, void(*displayFunc)(), void(*OnMouseClick)(float posX, float posY), unsigned int width, unsigned int height, unsigned int wcount, unsigned int hcount,int ratio,float tax);
	void Loop();
	int  GetCellSize();
	int  GetRatio();
	float GetTax();
};

