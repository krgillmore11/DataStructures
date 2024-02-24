#pragma once

#include <iostream>

using namespace std;

class Cell {
public:
	Cell();
	~Cell();
	bool traversed;
	bool onDeadPath;
	char type;
	int X;
	int Y;
	Cell* p_north;
	Cell* p_south;
	Cell* p_east;
	Cell* p_west;
private:

};
