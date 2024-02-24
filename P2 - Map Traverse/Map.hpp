#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "Cell.hpp"

using namespace std;

class Map {
public:
	Map(string filePath);
	~Map();
	void printCells();
	vector<Cell*> getCells();
	int getSize();
private:
	int size;
	string originalMapString;
	string newMap;
	vector <Cell*> cells;
	void readFile(string filePath);
	void cleanseMap();
	void createCellMap();
	
};