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
	unsigned int x, y;
	RECT quad;
	Map* map;
	_col color;
	DWORD vali;
public:

	virtual bool Update();
	virtual std::string getInfo();
	virtual int getFood();
	virtual bool isAlive();
	virtual int  getEnergy();

	bool getCell(unsigned int x, unsigned int y);
	unsigned int getX();
	unsigned int getY();

	bool isValid();

	Cell(Map*map, unsigned int x, unsigned int y);
	virtual ~Cell();
};

