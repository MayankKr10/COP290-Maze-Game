#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "maze.h"

class Controller {
	public:
		// evaluate the up, down, left, right, and quit
		void HandleInput(bool &running, Player &player, Maze &maze) const;

	private:
		// check if the move is allowed according to the walls and update the direction
		void ChangeDirection(Player &player, Player::Direction input, Maze &maze, bool &running) const;
};

#endif