#include <windows.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "color_utilites.hpp"
#include "random_generator.hpp"
#include "entity_item.hpp"
#include "entity_player.hpp"
#include "event_handler.hpp"


int height;
int width;
int player_amount;

std::vector<event_type> player_direction;
std::vector<int> color_number_pool;

struct pixel {
	char symbol;
	std::string color;
};

std::map<int, std::vector<pixel>> screen;
std::map<int, std::vector<pixel>> screen_buffer;

std::map<int, std::string> entity_player_color_vector;

int main() {
	entity_player_color_vector[1] = foreground::lightBlue;
	entity_player_color_vector[2] = foreground::lightCyan;
	entity_player_color_vector[3] = foreground::lightGreen;
	entity_player_color_vector[4] = foreground::lightMagenta;
	entity_player_color_vector[5] = foreground::lightRed;
	entity_player_color_vector[6] = foreground::lightWhite;
	entity_player_color_vector[7] = foreground::lightYellow;

	color_number_pool = { 1, 2, 3, 4, 5, 6, 7 };

	std::cout << "Total players (max. 2): ";
	std::cin >> player_amount;
	std::cout << "Height: ";
	std::cin >> height;
	std::cout << "Width: ";
	std::cin >> width;
	system("cls"); // What are you gonna do, kill me?

	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(StdHandle, &bufferInfo);

	std::vector<entity_item> entity_item_vector;
	std::vector<entity_player> entity_player_vector;

	while (true) {

		// ----------------------- //
		// Set up player direction //
		int player_iterator = 1;
		do {
			player_direction.push_back(MOVE_UPWARD);
			++player_iterator;
		} while (player_iterator <= player_amount);

		// ------------------------- //
		// Set up screen with spaces //
		for (int h = 0; h <= height; ++h) {
			for (int w = 0; w <= width; ++w) {
				screen[h].push_back({
					' ',
					""
					});
			}
		}

		// ---------------------- //
		// Set up player entities //
		player_iterator = 1;
		do {
			entity_player player = {
				'O',
				'o',
				random_between(2, width - 2),
				random_between(2, height - 2),
				nullptr,
				entity_player_color_vector[random_between(color_number_pool[color_number_pool[0]], color_number_pool[color_number_pool.size() - 1])]
			};
			entity_player_vector.push_back(player);
			++player_iterator;
		} while (player_iterator <= player_amount);

		// -------------------- //
		// Set up item entities //
		player_iterator = 1;
		do {
			entity_item_vector.push_back({
				'*',
				random_between(2, width - 2),
				random_between(2, height - 2)
				});
			++player_iterator;
		} while (player_iterator <= player_amount);

		screen_buffer = screen;

		// -------------- //
		// Main game loop //
		while (true) {
			Sleep(250);

			// --------------------- //
			// Set up screen borders //
			for (int h = 0; h <= height; ++h) {
				for (int w = 0; w <= width; ++w) {
					if (h == 0 || h == height || w == 0 || w == width) {
						screen[h][w] = {
							'#',
							""
						};
					}
				}
			}

			// ------------------------------ //
			// Set up item entities in screen //
			for (auto& entity_temporary : entity_item_vector) {
				screen[entity_temporary.y_pos][entity_temporary.x_pos] = {
					entity_temporary.symbol,
					""
				};
			}

			// -------------------- //
			// Get player direction //
			player_iterator = 1;
			do {
				event_process(ENTITY_MOVE, &entity_player_vector[player_iterator - 1], nullptr, player_amount, player_iterator, &player_direction, nullptr, nullptr);
				++player_iterator;
			} while (player_iterator <= player_amount);

			// ----------- //
			// Move player //
			player_iterator = 1;
			do {
				event_process(player_direction.at(player_iterator - 1), &entity_player_vector[player_iterator - 1], nullptr, player_amount, player_iterator, &player_direction, nullptr, nullptr);
				++player_iterator;
			} while (player_iterator <= player_amount);

			// -------------------------------- //
			// Set up player entities in screen //
			for (auto& entity_temporary : entity_player_vector) {
				switch (screen_buffer[entity_temporary.head_y_pos][entity_temporary.head_x_pos].symbol) {

					// -------------------------------- //
					// If next position is body or head //
				case ('o'):
				case ('O'): {
					event_process(INTERACT_PLAYER, &entity_temporary, nullptr, NULL, NULL, nullptr, &width, &height);
					break;
				}

							// ------------------------- //
							// If next position is fruit //
				case ('*'): {
					event_process(INTERACT_FRUIT, &entity_temporary, &entity_item_vector[std::distance(entity_item_vector.begin(), std::find_if(std::begin(entity_item_vector), std::end(entity_item_vector), [&](entity_item& item) { return item.x_pos == entity_temporary.head_x_pos && item.y_pos == entity_temporary.head_y_pos; }))], player_amount, NULL, nullptr, &width, &height);
					screen[entity_temporary.head_y_pos][entity_temporary.head_x_pos] = {
						entity_temporary.head_symbol,
						entity_temporary.player_color
					};
					break;
				}

							// ------------------------ //
							// If next position is wall //
				case ('#'): {
					event_process(INTERACT_WALL, &entity_temporary, nullptr, NULL, NULL, nullptr, &width, &height);
					break;
				}

							// ------------------------- //
							// If next position is space //
				case (' '): {
					screen[entity_temporary.head_y_pos][entity_temporary.head_x_pos] = {
						entity_temporary.head_symbol,
						entity_temporary.player_color
					};
					break;
				}
				}

				// ------------------------------ //
				// Set up body entities in screen //
				for (auto& body_temporary : entity_temporary.body_vector) {
					screen[body_temporary.y_pos][body_temporary.x_pos] = {
						body_temporary.symbol,
						entity_temporary.player_color
					};
				}
			}

			// ----------- //
			// Draw screen //
			for (auto& row : screen) {
				for (auto& pxl : row.second) {
					std::cout << pxl.color << pxl.symbol << foreground::reset;
				}
				std::cout << std::endl;
			}

			// --------------- //
			// Draw scoreboard //
			for (auto& entity_temporary : entity_player_vector) {
				for (int w = 0; w <= width; ++w) {
					if (w == 0 || w == width) {
						std::cout << "#";
					}
					else if (w == (width / 2) - 1) {
						std::cout << entity_temporary.player_color << entity_temporary.player_number << foreground::reset << ": " << entity_temporary.body_vector.size();
						w += (std::to_string(entity_temporary.player_number).size() + 1 + std::to_string(entity_temporary.body_vector.size()).size());
					}
					else {
						std::cout << " ";
					}
				}
				std::cout << std::endl;
			}
			for (int w = 0; w <= width; ++w) {
				std::cout << "#";
			}

			screen_buffer = screen;

			// ------------ //
			// Clear screen //
			for (auto& row : screen) {
				for (auto& pxl : row.second) {
					pxl.color = foreground::reset;
					pxl.symbol = ' ';
				}
			}

			// -------------------- //
			// Reset console cursor //
			SetConsoleCursorPosition(StdHandle, bufferInfo.dwCursorPosition);
		}
	}
}