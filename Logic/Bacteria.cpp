#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <windows.h>
#include "../Cell.h"
#include "../FoodCell.h"
#include "../Bacteria.h"
#include "../Render_Util.h"
#include "../Map.h"

const int energy_per_food = 3;

#define BACTERIA_CODE 0x1f3e5c7a

Bacteria::Bacteria(Map*_map, int x, int y, int food) :Cell(_map, x, y)
{
	energy = -1;
	zero = BACTERIA_CODE;
	Feed(food);
}

void Bacteria::Feed(int food_count)
{
	//std::cout << getInfo() << "\tEating " << food_count <<" +"<<energy<< std::endl;
	energy += food_count*energy_per_food;
}

int Bacteria::steal(int amount)
{
	//std::cout << getInfo() << "\tSomeone's eating " << amount << "/" << food_amount << std::endl;
	auto ne = energy - amount;
	if (ne > 0)
	{
		energy = ne;
		return amount;
	}
	else
	{
		ne = energy;
		energy = 0;
		return ne;
	}
}

bool Bacteria::Update()
{
	if (!map|| map->mapKey!=MAP_KEY_){
		energy = -1;
		return false;
	}

	if (!isAlive())
		return false;

	color.b = abs((int)(((float)energy / 50.0f)*(0xff / 2))) & (0xff / 2) & 125;

	color.r = 0;
	color.g = 0;

	RenderUtil::Render(color.rgba, quad);
	int food = energy / 5;

	for (int i = 0; i < 4; ++i){
		int _x, _y;
		switch (i)
		{
		case 0:
			_x = x; _y = y - 1;
			break;
		case 1:
			_x = x + 1; _y = y;
			break;
		case 2:
			_x = x; _y = y + 1;
			break;
		case 3:
			_x = x - 1; _y = y;
			break;
		}
		auto c = map->FindFood(_x, _y);
		FoodCell* cell = (FoodCell*)(c);
		if (cell){
			Feed(cell->steal(rand() % 10));
			if (energy >= 50&& rand()%2){
				Bacteria* nc = (Bacteria*)(map->SettleBacteria(c, food));
				energy -= food;
			}
		}

	}

	energy -= energy_per_food + energy/50;
	return true;
}

bool Bacteria::isAlive()
{
	bool ret = energy > 0;
	if (!ret)
		zero = (DWORD)-1;
	return ret;
}

int Bacteria::getEnergy()
{
	return energy;
}

std::string Bacteria::getInfo()
{
	std::stringstream str;
	str << "Bacteria " << x << ":" << y << " (energy left " << energy << ")";// \tOn a{ "<< Cell::getInfo()<<" }";
	return str.str();
}

Bacteria::~Bacteria()
{
	zero = (DWORD)-1;
}
