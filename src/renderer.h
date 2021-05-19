#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "player.h"
#include "room.h"

class Renderer {
	public:
		Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t grid_width, const std::size_t grid_height);
		~Renderer();

		// draw all components of the game
		void Render(Player const player, SDL_Point const &food, std::vector <Room> mazeGrid);
		void UpdateWindowTitle(int score, Uint32 timeDuration);
		// if the player reached the goal stop the time
		void setFinished();
		bool isFinished();

	private:
		SDL_Window *sdl_window;
		SDL_Renderer *sdl_renderer;
		bool finished;

		const std::size_t screen_width;
		const std::size_t screen_height;
		const std::size_t grid_width;
		const std::size_t grid_height;
		// draw the maze
		void renderMaze(SDL_Renderer* renderer, std::vector <Room> mazeGrid);
};

#endif