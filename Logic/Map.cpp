#include <string>
#include <iostream>
#include <sstream>
#include <windows.h>
#include "../Cell.h"
#include "../Bacteria.h"
#include "../FoodCell.h"
#include "../Map.h"
#include "../Render_Util.h"




Cell* Map::find(int x, int y)
{
	for each (auto cel in cells)
	{
		if (cel->getX() == x&&cel->getY() == y)
			return cel;
	}
	return 0;
}

Map::Map(int width, int height)
{
	mapKey = MAP_KEY_;
	w = width;
	h = height;

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++){
			cells.push_back(new FoodCell(this, x, y, abs(rand() % (255))));
		}
}

Map::~Map()
{
	mapKey = (DWORD)-1;
	for each(auto cel in cells)
		delete cel;
}

Cell* Map::SettleBacteria(int x, int y, int addition_food)
{
	for each(auto cel in cells){
		if (cel->getCell(x, y)){

			auto b = new Bacteria(this, cel->getX(), cel->getY(), cel->getFood() + addition_food);

			cells.push_front(b);
			cells.remove(cel);
			//std::cout << "Welcome new bacteria " << b->getInfo() << std::endl;
			return b;
		}
	}
	return 0;
}

Cell* Map::SettleBacteria(Cell* old, int addition_food /*= 0*/)
{
	int _x = old->getX();
	int _y = old->getY();
	
	auto b = new Bacteria(this, _x, _y, old->getFood() + addition_food);

	cells.push_front(b);
	cells.remove(old);
	//std::cout << "Welcome new bacteria " << b->getInfo() << std::endl;
	return b;
}

void Map::Update()
{
	foodLeft = 0;
	bacterias = 0;
	energy = 0;

	RenderUtil::StartScene();
	for each(auto cel in cells){

		cel->Update();

		if (cel->isAlive())
			++bacterias;
		foodLeft += cel->getFood();
		energy += cel->getEnergy();

	}
	RenderUtil::EndScene();
}

int Map::FoodLeft()
{
	return foodLeft;
}

int Map::BacteriaAlive()
{
	return bacterias;
}

int Map::EnergyLeft()
{
	return energy;
}

Cell* Map::FindFood(int x, int y)
{
	x = x % w;
	y = y % h;
	auto r = find(x, y);
	if (r&&r->getFood() > 0)
		return r;
	return 0;
}
