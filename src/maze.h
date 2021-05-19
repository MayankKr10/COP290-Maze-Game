#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include "SDL2/SDL.h"
#include "room.h"
#include <vector>

class Maze {    
	public: 
		Maze(std::size_t rows, std::size_t colums, std::size_t roomWidth);
		// return the generated maze
		std::vector <Room> getMazeGrid();
		std::size_t getRows() const;
		std::size_t getColums() const;
		std::size_t getRoomWidth() const;
	private: 
		std::size_t kRows;
		std::size_t kColums;
		std::size_t kRoomWidth;
		// contains the generated maze grid
		std::vector <Room> mazeGrid;
		// generates the maze grid with breadth first search
		void generateMazeGrid();
		// analyzes all neighbors of the current room and randomly choses one which is next
		int checkNeighbours(std::vector <Room> maze, Room r);
		void printMaze(std::vector <Room> mazeGrid);
};

#endif