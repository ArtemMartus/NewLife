#pragma once
#include <memory>

class Bacteria:
	public Cell
{
	long energy;
	DWORD zero;
	int steal(int amount);
public:
	Bacteria(Map*_map, int x, int y, int food);
	void Feed(int food_count);
	bool Update();
	bool isAlive();
	int  getEnergy();
	std::string getInfo();
	~Bacteria();
};

