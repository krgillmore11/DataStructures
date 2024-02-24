#include <iostream>
#include "Tracker.hpp"
#include "Map.hpp"
#include "Stack.hpp"
#include <vector>
#include <string>

using namespace std;

Tracker::Tracker() {
	p_current = 0;
	size = 0;
	vector <Cell*> cells;
}
void Tracker::printRoute() {
	for (int i = 0; i < cells.size(); i++) {
		if (i % size == 0) {
			cout << endl;
		}
		if (cells[i]->traversed && !(cells[i]->onDeadPath))
			cout << "O ";
		else {
			cout << "X ";
		}
	}
	cout << endl;

}
void Tracker::findPath(Map& map) {
	size = map.getSize();
	cells = map.getCells();
	bool foundStart = false;
	for (int i = 0; i < map.getCells().size(); i++) {
		if (map.getCells()[i]->type == 'S') {
			p_current = map.getCells()[i];
			foundStart = true;
			cout << "Starting at: X : " + to_string(p_current->X) + " Y : " + to_string(p_current->Y) << endl;
			break;
		}
	}
	if (!foundStart) {
		cout << "Unable to find start" << endl;
	}


	route.push(p_current);

	while (p_current->type != 'E') {
		if (!checkForRoute()) {
			cout << "Backtracking from: X: " + to_string(p_current->X) + " Y : " + to_string(p_current->Y) + " Type : " + p_current->type;
			p_current->onDeadPath = true;
			cout << " to : X: " + to_string(route.top()->X) + " Y : " + to_string(route.top()->Y) + " Type : " + route.top()->type << endl;
			p_current = route.top();
			route.pop();
		}
	}
		
	p_current->traversed = true;
}
bool Tracker::checkForRoute() {
	bool retVal = false;
		if (p_current->Y != 0) {
			if ((p_current->p_north->type == 'F' || p_current->p_north->type == 'E') && p_current->p_north->traversed != true && p_current->p_north != 0 && !(p_current->p_north->onDeadPath)) {
				route.push(p_current);
				p_current->traversed = true;
				p_current = p_current->p_north;
				cout << "Going North X : " + to_string(p_current->X) + " Y : " + to_string(p_current->Y) + " Type : " + p_current->type << endl;
				retVal = true;
			}
		}
		if (p_current->Y != size - 1) {
			if ((p_current->p_south->type == 'F' || p_current->p_south->type == 'E') && p_current->p_south->traversed != true && p_current->p_south != 0 && !(p_current->p_south->onDeadPath)) {
				route.push(p_current);
				p_current->traversed = true;
				p_current = p_current->p_south;
				cout << "Going South X : " + to_string(p_current->X) + " Y : " + to_string(p_current->Y) + " Type : " + p_current->type << endl;
				retVal = true;
			}
		}
		if (p_current->X != 0) {
			if ((p_current->p_west->type == 'F' || p_current->p_west->type == 'E') && p_current->p_west->traversed != true && p_current->p_west != 0 && !(p_current->p_west->onDeadPath)) {
				route.push(p_current);
				p_current->traversed = true;
				p_current = p_current->p_west;
				cout << "Going West X : " + to_string(p_current->X) + " Y : " + to_string(p_current->Y) + " Type : " + p_current->type << endl;
				retVal = true;
			}
		}
		if (p_current->X != size - 1) {
			if ((p_current->p_east->type == 'F' || p_current->p_east->type == 'E') && p_current->p_east->traversed != true && p_current->p_east != 0 && !(p_current->p_east->onDeadPath)) {
				route.push(p_current);
				p_current->traversed = true;
				p_current = p_current->p_east;
				cout << "Going East X : " + to_string(p_current->X) + " Y : " + to_string(p_current->Y) + " Type : " + p_current->type << endl;
				retVal = true;
			}
		}
		return retVal;
}