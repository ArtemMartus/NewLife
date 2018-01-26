#include "../Header.h"
#include "../Cell.h"

#define CELL_VALID 0xf2f4f6f8

bool Cell::Update()
{
	return false;
}

std::string Cell::getInfo()
{
	std::stringstream str;
	str << "[" << x << ":" << y << "]" << quad.left << "..." << quad.right << " | " << quad.top << "..." << quad.bottom;
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

bool Cell::getCell(unsigned int x_, unsigned int y_)
{
	auto cell = RenderUtil::GetCellSize();

	int _x = x_ / cell;
	int _y = y_ / cell;
	return x == _x && y == _y;
}

unsigned int Cell::getX()
{
	return x;
}

unsigned int Cell::getY()
{
	return y;
}

bool Cell::isValid()
{
	return vali == CELL_VALID;
}

Cell::Cell(Map*_map, unsigned int x, unsigned int y)
{
	vali = CELL_VALID;

	map = _map;
	this->x = x;
	this->y = y;

	quad.left = x;
	quad.right = x;
	quad.top = y;
	quad.bottom = y;

	color.r = -(0xff / 2);
	color.g = -(0xff / 2);
	color.b = 0xff / 2;
	color.a = 0xff / 2;
}

Cell::~Cell()
{
	vali = (DWORD)-1;
}
