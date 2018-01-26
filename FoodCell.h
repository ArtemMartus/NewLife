#pragma once
class FoodCell :
	public Cell
{
	float food_amount;
	float old_food;
public:
	FoodCell(Map*_map, unsigned int x, unsigned int y, float food = 1);
	bool Update();
	int getFood();
	float steal(float amount);
	int ratio();
	std::string getInfo();
	~FoodCell();
};

