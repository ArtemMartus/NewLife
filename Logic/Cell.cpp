#include <string>
#include <windows.h>
#include <sstream>
#include "../Cell.h"
#include "../Render_Util.h"
#include "../Map.h"

bool Cell::Update()
{
	return false;
}

std::string Cell::getInfo()
{
	std::stringstream str;
	str << "[" << x << ":" << y << "]" << quad.left << "..." << quad.right <<" | " << quad.top << "..." << quad.bottom;
	return str.str();
}

int Cell::getFood()
{
	return 0;
}

bool Cell::isAlive()
{
	return false;
}

int Cell::getEnergy()
{
	return 0;
}

bool Cell::getCell(int x_, int y_)
{
	return x_ >= quad.left && x_ <= quad.right && y_ >= quad.top && y_ <= quad.bottom;
}

int Cell::getX()
{
	return x;
}

int Cell::getY()
{
	return y;
}

Cell::Cell(Map*_map,int x, int y)
{
	map = _map;
	this->x = x;
	this->y = y;
	auto cell = RenderUtil::GetCellSize();

	quad.left = x*cell + cell / 10;
	quad.right = x*cell + cell - cell / 10;
	quad.top = y*cell + cell / 10;
	quad.bottom = y*cell + cell - cell / 10;

	color.r = -(0xff/2);
	color.g = -(0xff / 2);
	color.b = 0xff / 2;
	color.a = 0xff / 2;
}

Cell::~Cell()
{
}
