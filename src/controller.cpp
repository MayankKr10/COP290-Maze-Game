#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "player.h"
#include "maze.h"

void Controller::ChangeDirection(Player &player, Player::Direction input, Maze &maze, bool &running) const {
	// calculate room number where player is currently located
	int roomNumber = (player.head_x * maze.getRows()) + player.head_y;
	if(roomNumber == (maze.getRows() * maze.getColums()) - 1) running = false;

	// check if there is no wall in the requested direction
	if((input == Player::Direction::kUp && !maze.getMazeGrid()[roomNumber].getWall(0)) ||
		(input == Player::Direction::kRight && !maze.getMazeGrid()[roomNumber].getWall(1)) ||
		(input == Player::Direction::kDown && !maze.getMazeGrid()[roomNumber].getWall(2)) ||
		(input == Player::Direction::kLeft && !maze.getMazeGrid()[roomNumber].getWall(3))) {
		player.direction = input;
		player.directionUpdated();
	}
}

void Controller::HandleInput(bool &running, Player &player, Maze &maze) const {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			running = false;
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					ChangeDirection(player, Player::Direction::kUp, maze, running);
					break;

				case SDLK_DOWN:
					ChangeDirection(player, Player::Direction::kDown, maze, running);
					break;

				case SDLK_LEFT:
					ChangeDirection(player, Player::Direction::kLeft, maze, running);
					break;

				case SDLK_RIGHT:
					ChangeDirection(player, Player::Direction::kRight, maze, running);
					break;
				case SDLK_ESCAPE:
					SDL_FlushEvent(SDLK_ESCAPE);
					running = false;
					break;
				case SDLK_RETURN:
					SDL_FlushEvent(SDLK_RETURN);
					running = false;
					break;
			}
		}
	}
}