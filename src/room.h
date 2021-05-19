#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "SDL2/SDL.h"

class Room {
	public: 
		// receives the position x and y and the romm width
		Room(int i, int j, int rw);
		// remove all walls
		void removeWalls(Room &r);
		// remove the given wall
		void removeWall(int wall);
		void printWalls();
		// mark room as visited
		void visit();

		int getX();
		int getY();
		bool isVisited();
		int getRoomWidth();
		bool getWall(int i);
	private: 
		int x, y, roomWidth;
		// indicates the walls in the room
		// 0 - top, 1 - right, 2 - bottom, 3 - left
		bool walls[4];
		bool visited;  
};

#endif