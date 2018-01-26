#include "../Header.h"
#include "../FoodCell.h"



FoodCell::FoodCell(Map*_map, unsigned int x, unsigned int y, float food) : Cell(_map, x, y)
{
	food_amount = food;
	old_food = food_amount;
}

bool FoodCell::Update()
{
	if (food_amount <= 0)
		return false;

	int red = (int)(((float)food_amount /(float) old_food)*(255.0f/2.0f));
	color.r = abs(red&(255/2));
	color.g = 0;
	color.b = 0;

	RenderUtil::Render(color.rgba, quad);

	return true;
}

int FoodCell::getFood()
{
	return food_amount;
}

float FoodCell::steal(float amount)
{
	//std::cout << getInfo() << "\tSomeone's eating " << amount << "/" << food_amount << std::endl;
	auto ne = food_amount - amount*RenderUtil::GetTax();
	if (ne > 0.0f)
	{
		food_amount = ne;
		return amount;
	}
	else
	{
		ne = food_amount;
		food_amount = 0.0f;
		return ne;
	}
}

int FoodCell::ratio()
{
	auto rate = (float)food_amount / old_food;
	return (int)(rate * 100.0f);
}

std::string FoodCell::getInfo()
{
	std::stringstream str;
	str << "Food " << x << ":" << y << " (food left " << food_amount << ")";// {" << Cell::getInfo()<<"}";
	return str.str();
}

FoodCell::~FoodCell()
{
}
