#include "game.h"
#include <iostream>
#include "SDL.h"
#include "maze.h"

Game::Game(std::size_t rows, std::size_t colums, std::size_t roomWidth)
		: player(rows, colums),
			maze(rows, colums, roomWidth),
			engine(dev()),
			random_w(0, static_cast<int>(colums)),
			random_h(0, static_cast<int>(rows)),
			score(0){
	PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) {
	Uint32 title_timestamp = SDL_GetTicks();
	Uint32 frame_start;
	Uint32 frame_end;
	Uint32 frame_duration;
	int frame_count = 0;
	bool running = true;
	Uint32 time_taken;

	// generate maze
	std::vector <Room> mazeGrid = maze.getMazeGrid();
	// initialize start time of game
	startTimestamp = SDL_GetTicks();

	while (running) {
		frame_start = SDL_GetTicks();

		// Input, Update, Render - the main game loop.
		controller.HandleInput(running, player, maze);
		Update(renderer);
		renderer.Render(player, food, mazeGrid);

		int roomNumber = (player.head_x * maze.getRows()) + player.head_y;
		if((roomNumber != (maze.getRows() * maze.getColums()) - 1) && !running) score = 0;

		frame_end = SDL_GetTicks();

		// Keep track of how long each loop through the input/update/render cycle takes.
		frame_count++;
		frame_duration = frame_end - frame_start;

		// After every second, update the window title.
		if (frame_end - title_timestamp >= 1000) {
			renderer.UpdateWindowTitle(score, (SDL_GetTicks() - startTimestamp) / 1000);
			frame_count = 0;
			title_timestamp = frame_end;
			game_time = (SDL_GetTicks() - startTimestamp)/1000;
		}

		// If the time for this frame is too small delay the loop to reach the correct frame rate
		if (frame_duration < target_frame_duration) {
			SDL_Delay(target_frame_duration - frame_duration);
		}
	}
}

void Game::PlaceFood() {
	int x, y;
	while (true) {
		x = random_w(engine);
		y = random_h(engine);
		// Check that the location is not occupied by the player before placing food.
		if (!player.PlayerCell(x, y)) {
			food.x = x;
			food.y = y;
			return;
		}
	}
}

void Game::Update(Renderer &renderer) {
	if (renderer.isFinished()) return;

	player.Update();

	int new_x = static_cast<int>(player.head_x);
	int new_y = static_cast<int>(player.head_y);

	// Check if there's food over here
	if (food.x == new_x && food.y == new_y) {
		score++;
		PlaceFood();
	}

	// check if goal was reached -  the goal is always in the right down corner
	if(new_x == maze.getRows() - 1 && new_y == maze.getColums() - 1) {
		renderer.setFinished();
	}
}

int Game::GetScore() const { return score; }

int Game::GetTime() const { return game_time; }
