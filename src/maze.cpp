#include "maze.h"
#include <vector>
#include <stack>
#include "room.h"

Maze::Maze(std::size_t rows, std::size_t colums, std::size_t roomWidth):kRows(rows), kColums(colums), kRoomWidth(roomWidth) {
		generateMazeGrid();
}

int Maze::checkNeighbours(std::vector <Room> maze, Room r) {
	int x = r.getX();
	int y = r.getY();
	std::vector < Room > neighbours;
	if(!maze[(x - 1) * kRows + y].isVisited() && x > 0) {
		neighbours.push_back(maze[(x - 1) * kRows + y]);
	}
	if(!maze[(x + 1) * kRows + y].isVisited() && x < kRows - 1) {
		neighbours.push_back(maze[(x + 1) * kRows + y]);
	}
	if(!maze[x * kRows + y + 1].isVisited() && y < kColums - 1) {
		neighbours.push_back(maze[x * kRows + y + 1]);
	}
	if(!maze[x * kRows + y - 1].isVisited() && y > 0) {
		neighbours.push_back(maze[x * kRows + y - 1]);
	}
	if (neighbours.size() < 1) {
		return -1;
	}

	int randomIdx = rand() % neighbours.size();
	int nxt = neighbours[randomIdx].getY() + neighbours[randomIdx].getX() * kRows;
	return nxt;
}

void Maze::printMaze(std::vector < Room > mazeGrid) {
	for(int i = 0; i < mazeGrid.size(); i++) {
		std::cout << "x:" << mazeGrid[i].getX() << " y:" << mazeGrid[i].getY() << " visited:" << mazeGrid[i].isVisited() << std::endl;
		mazeGrid[i].printWalls();
	}
}

void Maze::generateMazeGrid() {
	std::stack <Room*> roomStack;

	// initialize all rooms
	for (int i = 0; i < kRows; i++) {
		for (int j = 0; j < kColums; j++) {
			Room newRoom(i, j, kRoomWidth);
			mazeGrid.push_back(newRoom);
		}
	}

	// start at position (0,0)
	Room *current = &mazeGrid[0]; 
	current->visit(); 

	int next = 0;
	while(true){
		next = checkNeighbours(mazeGrid, *current);
		// If the current cell has any neighbours which have not been visited
		if (next != -1) {
			// Choose randomly one of the unvisited neighbours
			Room &nextRoom = mazeGrid[next];
			// Push the current cell to the stack
			roomStack.push(current);
			// Remove the wall between the current cell and the chosen cell
			current->removeWalls(nextRoom);
			// Make the chosen cell the current cell and mark it as visited
			current = &nextRoom; 
			current->visit();
		} else if (!roomStack.empty()) { // If stack is not empty
			// Pop a cell from the stack
			Room &previousRoom = *roomStack.top();
			roomStack.pop();
			// Make it the current cell
			current = &previousRoom;
		} else if (roomStack.empty()) { // If stack is empty
			break;
		}
	}
}

std::vector <Room> Maze::getMazeGrid() {
	return mazeGrid;
}

std::size_t Maze::getRows() const {
	return kRows;
}

std::size_t Maze::getColums() const {
	return kColums;
}

std::size_t Maze::getRoomWidth() const {
	return kRoomWidth;
}