#include <iostream>
#include "Map.hpp"
#include "Cell.hpp"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Map::Map(string filePath) {
    size = 0;
    originalMapString = "";
    newMap = "";

    readFile(filePath);
    cleanseMap();
    //cout << originalMapString;
    
    createCellMap();
}

Map::~Map() {
    for (int i = 0; i < (size*size); i++)
    {
        delete cells[i];
        cells[i] = 0;
    }
    cells.clear();
}

void Map::printCells() {
    for (int i = 0; i < originalMapString.length(); i++) {
        if (i % size == 0) {
            cout << endl;
        }
        cout << originalMapString[i] << ' ';
    }
    cout << endl;
}

void Map::readFile(string filePath){
    string str;
    ifstream file;
    file.open(filePath);

    while (!file.eof()) {
        getline(file, str);
        originalMapString += str;
        size++;
    }
    file.close();
    }

void Map::cleanseMap() {
    for (int i = 0; i < originalMapString.length(); i++) {
        if (originalMapString.at(i) == ' ') {
            originalMapString.erase(originalMapString.begin() + i);
            i--;
        }
    }
}

void Map::createCellMap() {
    int x = 0;
    int y = 0;
    for (int i = 0; i < originalMapString.length(); i++) {
        Cell* p_newCell = new Cell;
        p_newCell->type = originalMapString[i];;
        p_newCell->X = x;
        x++;
        if (x == size) {
            x = 0;
        }
        
        if (i % size == 0 && i != 0) {
            y++;
        }
        p_newCell->Y = y;
        if (i < size) {
            p_newCell->p_north = 0;
        }
        if (i % size == 0) {
            p_newCell->p_west = 0;
        }
        if (i >= (size * size) - size) {
            p_newCell->p_south = 0;
        }
        if (i % size == size - 1) {
            p_newCell->p_east = 0;
        }
        if (i > 0 && i % size != 0) {
            p_newCell->p_west = cells[i - 1];
        }
        if (i >= size) {
            p_newCell->p_north = cells[i - size];
        }
        cells.push_back(p_newCell);
    }
    for (int i = size*size - 1; i >= 0; i--) {
        if (i < (size * size) - size) {
            cells[i]->p_south = cells[i+size];
        }
        if (i % size != size - 1) {
            cells[i]->p_east = cells[i + 1];
        }
    }

}

vector<Cell*> Map::getCells() {
    return cells;
}

int Map::getSize() {
    return size;
}