#pragma once

class Map 
{
	Block cellBlock;
	int foodLeft;
	int bacterias;
	int energy;
	int cellsAlive;

	unsigned int w;
	unsigned int h;

	Cell* find(unsigned int x, unsigned int y);
public:
	Map(unsigned int width, unsigned int height);
	~Map();

	Cell* SettleBacteria(Cell* old, int addition_food = 0);
	Cell* SettleBacteria(unsigned int x, unsigned int y, int addition_food = 0);
	void Update();
	int FoodLeft();
	int BacteriaAlive();
	int EnergyLeft();
	int CellsAlive();
	Cell* FindFood(unsigned int x, unsigned int y);

	DWORD mapKey;
};

