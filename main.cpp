#include <windows.h>
#include <string>
#include <iostream>
#include <list>
#include <memory>
#include <chrono>
#include "Cell.h"
#include "Render_Util.h"
#include "Map.h"

Map *map;
typedef std::chrono::high_resolution_clock Clock;


void mouse(float x_, float y_)
{
	float x = x_ ;
	float y = y_;
	std::cout << "Mouse clicked on " << x << " " << y << std::endl;
	map->SettleBacteria(x, y);
}

auto t1 = Clock::now();
bool firstDraw = true;

void renderFunc()
{
	if (firstDraw||std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count() >= 200)
	{
		t1 = Clock::now();
		map->Update();
		firstDraw = false;
		std::cout << "Bacteria count " << map->BacteriaAlive() << "\tFood count " << map->FoodLeft() <<"\tEnergy left "<<map->EnergyLeft()<< std::endl;
	}
}

int main(int argc,char**argv)
{
	t1 = Clock::now();
	RenderUtil::Init(argc,argv,renderFunc,mouse,1200,900,100,100);
	map = new Map(100, 100);
	
	RenderUtil::Loop();
	system("pause");
	delete map;
	return 0;
}