#include "Header.h"

Map *map;
typedef std::chrono::high_resolution_clock Clock;

static unsigned int delay = 100;

static int last_bac = 0;
static int last_fod = 0;
static int last_erg = 0;
static int last_cls = 0;

static int stat_frames = 0;

static int curr_bac = 0;
static int curr_fod = 0;
static int curr_erg = 0;
static int curr_cls = 0;

static bool over = false;
static bool start = false;

void mouse(float x_, float y_)
{
	float x = x_ ;
	float y = y_;
	std::cout << "Mouse clicked on " << x << " " << y << std::endl;
	map->SettleBacteria(x, y);
}

auto t1 = Clock::now();
bool firstDraw = true;

bool eq(float a, float b)
{
	float c = fabs(a - b);
	return c <= 0.0001f;
}

void renderFunc()
{
	if (firstDraw || std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count() >= delay)
	{
		t1 = Clock::now();
		map->Update();
		firstDraw = false;

		curr_bac += map->BacteriaAlive();
		curr_fod += map->FoodLeft();
		curr_erg += map->EnergyLeft();
		curr_cls += map->CellsAlive();
		stat_frames++;

		if (curr_bac > 0)
			start = true;
	}

	if (stat_frames >= 100)
	{
		float a = ((float)(curr_bac - last_bac)) / stat_frames;
		float b = ((float)(curr_fod - last_fod)) / stat_frames;
		float c = ((float)(curr_erg - last_erg)) / stat_frames;
		float d = ((float)(curr_cls - last_cls)) / stat_frames;

		if (start)
			std::cout << "Bacteria " << a <<
			"\tFood " << b <<
			"\tEnergy " << c <<
			"\tAlive cells " << d << "\n";

		if (start && eq(a,b) && eq(b,c)&&eq(c,d)&&eq(d,0.0f))
			over = true;

		last_bac = curr_bac;
		last_fod = curr_fod;
		last_erg = curr_erg;
		last_cls = curr_cls;

		stat_frames = 0;

		curr_bac = 0;
		curr_fod = 0;
		curr_erg = 0;
		curr_cls = 0;
	}

	if (over){
		std::cout << "It's over for now. Seems no food left...\n";
		system("pause");
		delete map;
		glutLeaveMainLoop();
	}
}

int main(int argc,char**argv)
{// 0xff 8bit 0xffff 16bit 0xffffff 32bit 0xffffffff 64bit
	std::cout << "Frame delay ms, higher value = slower growing(100 is good):";
	std::cin >> delay;
	if (delay < 0)
		delay = 0;
	int rate = 30;
	std::cout << "Current_food/food ratio (0-100), higher value = more aggressive conquering(50 is good):";
	std::cin >> rate;
	float tax = 0.2f;
	std::cout << "Energy transfer tax(0.1 is good):";
	std::cin >> tax;

	t1 = Clock::now();
	RenderUtil::Init(argc, argv, renderFunc, mouse, 1200, 900, 0xff, 0xff, rate,tax);
	map = new Map(0xff, 0xff);
	
	RenderUtil::Loop();

	return 0;
}