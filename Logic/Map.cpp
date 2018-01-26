#include "../Header.h"
#include "../Map.h"



Cell* Map::find(unsigned int x, unsigned int y)
{
	Cell * c = 0;
	if (x >= 0 && x < 0xff && y >= 0 && y < 0xff)
	{
		c = cellBlock.getCell(block_id(x, y)); 
		try{
			if (c&&c->isValid())
				return c;
		}
		catch (...){
			return 0;
		}
	}
	return 0;
}

Map::Map(unsigned int width, unsigned int height)
{
	mapKey = MAP_KEY_;
 	w = width;
 	h = height;

	block_id id;
	for (id.id = 0; id.id < MAPSIZE; id.id++){
		unsigned __int16 food = 0;
	food_sp:
		food = abs(rand() % (0xff));
		if (food < 40)
			goto food_sp;

		cellBlock.setCell(id, new FoodCell(this, id.x, id.y, food));
	}
}

Map::~Map()
{
	mapKey = (DWORD)-1;
}

Cell* Map::SettleBacteria(unsigned int x, unsigned int y, int addition_food)
{
	Cell* b = 0;

	Cell* cel = cellBlock.find(x, y);
	if (cel){

		auto b = new Bacteria(this, cel->getX(), cel->getY(), cel->getFood() + addition_food);
		cellBlock.setCell(block_id(b->getX(), b->getY()), b);
		delete cel;
		//std::cout << "Welcome new bacteria " << b->getInfo() << std::endl;
		return b;
	}
	return 0;
}

Cell* Map::SettleBacteria(Cell* old, int addition_food /*= 0*/)
{
	auto _x = old->getX();
	auto _y = old->getY();

	
	auto b = new Bacteria(this, _x, _y, old->getFood() + addition_food);
	if (!b || !b->isValid())
		return 0;

	delete cellBlock.getCell(block_id(_x, _y));
	cellBlock.setCell(block_id(_x, _y), b);
	//std::cout << "Welcome new bacteria " << b->getInfo() << std::endl;
	return b;
}

void Map::Update()
{
	foodLeft = 0;
	bacterias = 0;
	energy = 0;
	cellsAlive = 0;

	RenderUtil::StartScene();
	for (int i = 0; i < MAPSIZE; ++i){

		Cell* cel = cellBlock.getCell(block_id(i));
		if (!cel->Update())
		{
			continue;
		}
		cellsAlive++;

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

int Map::CellsAlive()
{
	return cellsAlive;
}

Cell* Map::FindFood(unsigned int x, unsigned int y)
{
 	x = x % w;
 	y = y % h;
	auto r = find(x, y);
	if (r&&r->getFood() > 0)
		return r;
	return 0;
}
