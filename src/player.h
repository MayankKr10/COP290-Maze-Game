#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "SDL.h"

class Player {
	public:
		enum class Direction { kUp, kDown, kLeft, kRight };

		Player(int grid_width, int grid_height);
		// update the position of the player
		void Update();
		// indicates if the player changed it's position
		void directionUpdated();
		// check if cell is occupied by player
		bool PlayerCell(int x, int y);

		Direction direction;

		// the amount of change for the position
		float speed;
		// coordinates of the player
		float head_x;
		float head_y;

	private:
		int grid_width;
		int grid_height;
		bool directionUpdate;
};

#endif