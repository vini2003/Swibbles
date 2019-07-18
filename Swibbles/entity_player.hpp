#pragma once
#ifndef _ENTITY_player_
#define _ENTITY_player_

#include "entity_item.hpp"

#include <vector>
#include <map>
#include <string>

class entity_player {
public:
	// ----------- //
	// Constructor //
	entity_player(char, char, int, int, int*, std::string);

	// ---- //
	// Head //
	char head_symbol;
	char body_symbol;
	int head_x_pos;
	int head_y_pos;
	int player_number;
	std::string player_color;

	// ---- //
	// Body //
	std::vector<entity_item> body_vector;
};

#endif