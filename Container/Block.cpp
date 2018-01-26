#include "../Header.h"
#include "../Block.h"


Cell* Block::getCell(block_id id)
{
	DWORD a = block[id.id];
	if (a <= MAPSIZE)
		return 0;
	return (Cell*)a;
}

Cell* Block::setCell(block_id id, Cell* c)
{
	block[id.id] = (DWORD)c;
	return (Cell*)block[id.id];
}


Cell* Block::find(int x, int y)
{
	Cell* c = 0;
	for (int i = 0; i < MAPSIZE; ++i){
		c =(Cell*)block[i];
		if (c->isValid() && c->getCell(x, y))
			return c;
	}
	return 0;
}

Block::Block() : block(new DWORD[MAPSIZE])
{
	for (int a = 0; a < MAPSIZE; ++a)
		block[a] = 0;
}


Block::~Block()
{
	for (int a = 0; a < MAPSIZE; ++a)
		delete (Cell*)(block[a]);
	delete[]block;
}
