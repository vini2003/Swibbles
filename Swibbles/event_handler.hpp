#pragma once
#ifndef _EVENT_HANDLER_
#define _EVENT_HANDLER_

#include "entity_item.hpp"
#include "entity_player.hpp"

#include <windows.h>
#include <map>
#include <string>

enum keybind_type {
	// ---------- //
	// Player one //
	MOVE_UPWARD_0 = 'W',
	MOVE_DOWNWARD_0 = 'S',
	MOVE_RIGHT_0 = 'D',
	MOVE_LEFT_0 = 'A',

	// ---------- //
	// Player two //
	MOVE_UPWARD_1 = VK_UP,
	MOVE_DOWNWARD_1 = VK_DOWN,
	MOVE_RIGHT_1 = VK_RIGHT,
	MOVE_LEFT_1 = VK_LEFT
};


enum event_type {
	// -------- //
	// Movement //
	ENTITY_MOVE = 0,
	MOVE_UPWARD = 1,
	MOVE_DOWNWARD = 2,
	MOVE_RIGHT = 3,
	MOVE_LEFT = 4,

	// ------ //
	// Action //
	INTERACT_FRUIT = 5,
	INTERACT_WALL = 6,
	INTERACT_PLAYER = 7,
	INTERACT_QUIT = VK_ESCAPE,
};

struct event_package {
	// ----- //
	// Event //
	event_type type;
	entity_player entity_player_temporary;
	entity_item entity_item_temporary;
};

void event_process(event_type event_type_temporary, entity_player* entity_player_temporary, entity_item* entity_item_temporary, int player_amount, int player_current, std::vector<event_type>* player_direction, int* height, int* width);

#endif