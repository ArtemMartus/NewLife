#pragma once
#include <list>
#ifndef MAP_KEY_
#define MAP_KEY_ 0xfe2aefbc
#endif
class Map 
{
	std::list<Cell*> cells;
	int foodLeft;
	int bacterias;
	int energy;

	int w;
	int h;

	Cell* find(int x, int y);
public:
	Map(int width, int height);
	~Map();

	Cell* SettleBacteria(Cell* old, int addition_food = 0);
	Cell* SettleBacteria(int x, int y, int addition_food = 0);
	void Update();
	int FoodLeft();
	int BacteriaAlive();
	int EnergyLeft();
	Cell* FindFood(int x, int y);

	DWORD mapKey;
};

