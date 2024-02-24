#pragma once

#include <iostream>
#include "Cell.hpp"

using namespace std;

	Cell::Cell(){
	traversed = false;
	onDeadPath = false;
	type = ' ';
	X = 0;
	Y = 0;
	p_north = 0;
	p_south = 0;
	p_east = 0;
	p_west = 0;
}
	Cell::~Cell() {
		
	}