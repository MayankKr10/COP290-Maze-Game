#include "room.h"

using namespace std;

Room::Room(int i, int j, int rw) {
	this->x = i;
	this->y = j;
	this->roomWidth = rw;
	walls[0] = true;
	walls[1] = true;
	walls[2] = true;
	walls[3] = true;
	visited = false;
}

void Room::removeWalls(Room &r) {
	if (this->x - r.x == -1) {
		this->removeWall(1);
		r.removeWall(3);
	} 
	if (this->x - r.x == 1) {
		this->removeWall(3);
		r.removeWall(1);
	} 
	if (this->y - r.y == -1) {
		this->removeWall(2);
		r.removeWall(0);
	} 
	if (this->y - r.y == 1) {
			this->removeWall(0);
			r.removeWall(2);
	} 
}

void Room::printWalls() {
	for (int i = 0; i < 4; i++) {
		std::cout << "     wall:" << i << " - " << walls[i] << " ";
	}
	std::cout << "\n";
}

void Room::removeWall(int w) {
	this->walls[w] = false;
}

void Room::visit() {
	this->visited = true;
}

int Room::getX() {
	return this->x;
}

int Room::getY() {
	return this->y;
}

bool Room::isVisited() {
	return this->visited;
}

int Room::getRoomWidth() {
	return this->roomWidth;
}

bool Room::getWall(int i) {
	if(i < 0 || i > 3)
		throw ("Unexpected Value Exception: Room wall out of range");
	return this->walls[i];
}