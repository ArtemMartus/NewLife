#include "../Header.h"
#include "../Bacteria.h"

const float energy_per_food = 1.0f;


Bacteria::Bacteria(Map*_map, unsigned int x, unsigned int y, float food) :Cell(_map, x, y)
{
	energy = 0.0f;
	zero = BACTERIA_CODE;
	Feed(food);
}

void Bacteria::Feed(float food_count)
{
	//std::cout << getInfo() << "\tEating " << food_count <<" +"<<energy<< std::endl;
	energy += food_count*energy_per_food/RenderUtil::GetTax();
}

float Bacteria::steal(float amount)
{
	//std::cout << getInfo() << "\tSomeone's eating " << amount << "/" << food_amount << std::endl;
	auto ne = energy - amount*RenderUtil::GetTax();
	if (ne > 0.0f)
	{
		energy = ne;
		return amount;
	}
	else
	{
		ne = energy;
		energy = 0.0f;
		return ne;
	}
}

bool Bacteria::Update()
{
	if (!map || map->mapKey != MAP_KEY_){
		energy = -1;
		return false;
	}

	if (!isAlive())
		return false;

	color.b = abs((int)(((float)energy / 100.0f)*(0xff / 2))) & (0xff / 2) & 125;

	color.r = 0;
	color.g = 0;

	RenderUtil::Render(color.rgba, quad);
	float food = energy / 5.0f;

	if (rand() % 2)
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
			if (energy >= 50 && cell->ratio() <= RenderUtil::GetRatio() && rand() % 2){
				Bacteria* nc = (Bacteria*)(map->SettleBacteria(c, food));
				energy -= food;
			}
		}

		}
	//energy--;
	energy -= energy_per_food + energy / 50;
	return true;
}

bool Bacteria::isAlive()
{
	bool ret = energy > 0;
// 	if (!ret)
// 		zero = (DWORD)-1;
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
