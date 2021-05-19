#include "player.h"
#include <cmath>
#include <iostream>

Player::Player(int grid_width, int grid_height) : grid_width(grid_width), grid_height(grid_height), head_x(0.0), head_y(0.0), direction(Direction::kUp), speed(1.0f), directionUpdate(false) {}

void Player::directionUpdated(){
	directionUpdate = true;
}

void Player::Update() {
	if(directionUpdate){
		switch (direction) {
			case Direction::kUp:
				head_y -= speed;
				break;

			case Direction::kDown:
				head_y += speed;
				break;

			case Direction::kLeft:
				head_x -= speed;
				break;

			case Direction::kRight:
				head_x += speed;
				break;
		}
		directionUpdate = false;
	}  
}

// Inefficient method to check if cell is occupied by player.
bool Player::PlayerCell(int x, int y) {
	if (head_x == static_cast<int>(x) && head_y == static_cast<int>(y)) {
		return true;
	}

	return false;
}