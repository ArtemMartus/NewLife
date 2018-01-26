#pragma once

union block_id
{
	struct  
	{
		unsigned __int8 x;
		unsigned __int8 y;
	};
	unsigned __int16 id = 0;
	block_id() :id(0){}
	block_id(unsigned __int16 d) :id(d){}
	block_id(unsigned __int8 _x, unsigned __int8 _y) :x(_x), y(_y){}
};

class Block
{
	DWORD* block;

public:

	Cell* getCell(block_id id);
	Cell* setCell(block_id id, Cell* c);
	Cell* find(int x, int y);
	Block();
	~Block();
};

