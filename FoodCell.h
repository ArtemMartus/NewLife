#pragma once
class FoodCell :
	public Cell
{
	int food_amount;
	int old_food;
public:
	FoodCell(Map*_map, int x, int y, int food = 1);
	bool Update();
	int getFood();
	int steal(int amount);
	std::string getInfo();
	~FoodCell();
};

