#pragma once


class Bacteria:
	public Cell
{
	float energy;
	DWORD zero;
	float steal(float amount);
public:
	Bacteria(Map*_map, unsigned int x, unsigned int y, float food);
	void Feed(float food_count);
	bool Update();
	bool isAlive();
	int  getEnergy();
	std::string getInfo();
	~Bacteria();
};

