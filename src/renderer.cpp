#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
					const std::size_t screen_height,
					const std::size_t grid_width, 
					const std::size_t grid_height)
		: 	screen_width(screen_width),
			screen_height(screen_height),
			grid_width(grid_width),
			grid_height(grid_height),
			finished(false) {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize.\n";
		std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
	}

	// Create Window
	sdl_window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);

	if (nullptr == sdl_window) {
		std::cerr << "Window could not be created.\n";
		std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
	}

	// Create renderer
	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
	if (nullptr == sdl_renderer) {
		std::cerr << "Renderer could not be created.\n";
		std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
	}
}

Renderer::~Renderer() {
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}

void Renderer::Render(Player const player, SDL_Point const &food, std::vector <Room> mazeGrid) {
	SDL_Rect block;
	block.w = (screen_width / grid_width);
	block.h = (screen_height / grid_height);

	// Clear screen
	SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
	SDL_RenderClear(sdl_renderer);

	// Render Maze
	renderMaze(sdl_renderer, mazeGrid);

	// Render food
	SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
	block.x = food.x * block.w;
	block.y = food.y * block.h;
	SDL_RenderFillRect(sdl_renderer, &block);

	// Render player
	SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
	block.x = (player.head_x * block.w);
	block.y = (player.head_y * block.h);
	SDL_RenderFillRect(sdl_renderer, &block);

	// Render the goal
	SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
	block.x = screen_width - block.w;
	block.y = screen_height - block.h;
	SDL_RenderFillRect(sdl_renderer, &block);

	// Update Screen
	SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, Uint32 timeDuration) {
	if(!finished) {
		std::string title{"Maze Score: " + std::to_string(score) + " Time: " + std::to_string(timeDuration)};
		SDL_SetWindowTitle(sdl_window, title.c_str());
	}
}

void Renderer::renderMaze(SDL_Renderer* renderer, std::vector <Room> mazeGrid) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	for (Uint32 i = 0; i < mazeGrid.size(); i++) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_Rect rect{mazeGrid[i].getX() * mazeGrid[i].getRoomWidth(), mazeGrid[i].getY() * mazeGrid[i].getRoomWidth(), mazeGrid[i].getRoomWidth(), mazeGrid[i].getRoomWidth()};
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			
		int xCoord = mazeGrid[i].getX() * mazeGrid[i].getRoomWidth();
		int yCoord = mazeGrid[i].getY() * mazeGrid[i].getRoomWidth();
		if (mazeGrid[i].getWall(0)) {
			SDL_RenderDrawLine(renderer, xCoord, yCoord, xCoord + mazeGrid[i].getRoomWidth(), yCoord);
		}
		if (mazeGrid[i].getWall(1)) {
			SDL_RenderDrawLine(renderer, xCoord + mazeGrid[i].getRoomWidth(), yCoord, xCoord + mazeGrid[i].getRoomWidth(), yCoord + mazeGrid[i].getRoomWidth());
		}
		if (mazeGrid[i].getWall(2)) {
			SDL_RenderDrawLine(renderer, xCoord, yCoord + mazeGrid[i].getRoomWidth(), xCoord + mazeGrid[i].getRoomWidth(), yCoord + mazeGrid[i].getRoomWidth());
		}
		if (mazeGrid[i].getWall(3)) {
			SDL_RenderDrawLine(renderer, xCoord, yCoord, xCoord, yCoord + mazeGrid[i].getRoomWidth());
		}
	}
}

void Renderer::setFinished() {
	finished = true;
}

bool Renderer::isFinished() {
	return finished;
}