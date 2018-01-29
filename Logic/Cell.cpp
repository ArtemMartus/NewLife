#include "../Header.h"
#include "../Cell.h"


bool Cell::Update()
{
	return false;
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


Cell::Cell(Map*_map, unsigned int x, unsigned int y)
{

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

}
