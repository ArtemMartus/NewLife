#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <GL/freeglut.h>
#include "Cell.h"
#include "Render_Util.h"
#include "Block.h"
#include "Cell.h"
#include "Bacteria.h"
#include "FoodCell.h"
#include "Map.h"
#include <list>
#include <memory>
#include <chrono>

#ifndef MAP_KEY_
#define MAP_KEY_ 0xfe2aefbc
#endif

#ifndef BACTERIA_CODE
#define BACTERIA_CODE 0x1f3e5c7a
#endif

#ifndef CELL_VALID
#define CELL_VALID 0xf2f4f6f8
#endif

#ifndef MAPSIZE
#define MAPSIZE 0xffff
#endif
