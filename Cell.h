#pragma once
class Map;
union _col
{
	struct{
		char r;
		char g;
		char b;
		char a;
	};
	DWORD rgba;
};

class Cell
{
protected:
	int x, y;
	RECT quad;
	Map* map;
	_col color;
public:
	virtual bool Update();
	virtual std::string getInfo();
	virtual int getFood();
	virtual bool isAlive();
	virtual int  getEnergy();

	bool getCell(int x, int y);
	int getX();
	int getY();

	Cell(Map*map,int x,int y);
	virtual ~Cell();
};

