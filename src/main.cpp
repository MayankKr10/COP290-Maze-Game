#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"  
#include "constants.h"
	
int main() {
	// read the size of the maze
	int size;
	std::cout << "Please enter maze size from the range " << kMinMazeSize << " to " << kMaxMazeSize << "." << std::endl;
	std::cin >> size;
	while(size < kMinMazeSize || size > kMaxMazeSize) {
		std::cout << "Maze size not in range. Please enter a value between " << kMinMazeSize << " and " << kMaxMazeSize << "." << std::endl;
		std::cin >> size;
	}
	// calculate box size
	int roomSize = kScreenWidth / size;
	int score1, score2, gametime1, gametime2;

	// Player 1
	Renderer renderer(size * roomSize, size * roomSize, size, size);
	Controller controller;
	Game game(size, size, roomSize);
	game.Run(controller, renderer, kMsPerFrame);  
	score1 = game.GetScore() - (game.GetTime()/size);
	std::cout << "Player 1 Score: " << score1 << "\n";

	// Player 2
	Renderer renderer1(size * roomSize, size * roomSize, size, size);
	Controller controller1;
	Game game1(size, size, roomSize);
	game1.Run(controller1, renderer1, kMsPerFrame);  
	score2 = game1.GetScore() - (game1.GetTime()/size);
	std::cout << "Player 2 Score: " << score2 << "\n";

	if(score1 > score2) std::cout << "Player 1 Wins!\n";
	else if(score2 > score1) std::cout << "Player 2 Wins!\n";
	else std::cout<< "Draw!\n";

	return 0;
}