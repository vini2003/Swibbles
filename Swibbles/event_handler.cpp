#include "event_handler.hpp"
#include "random_generator.hpp"

#include <iostream>
#include <windows.h>

// ---------------- //
// Event processing //
void event_process(event_type event_type_temporary, entity_player* entity_player_temporary, entity_item* entity_item_temporary, int player_amount, int player_current, std::vector<event_type>* player_direction, int* height, int* width) {
	// ------------ //
	// Get movement //
	if (event_type_temporary == ENTITY_MOVE && player_current >= 0 && player_current <= 2 && entity_player_temporary != nullptr && player_direction != nullptr) {
		int MOVE_UPWARD_C;
		int MOVE_DOWNWARD_C;
		int MOVE_RIGHT_C;
		int MOVE_LEFT_C;
		if (player_current == 1) {
			MOVE_UPWARD_C = MOVE_UPWARD_0;
			MOVE_DOWNWARD_C = MOVE_DOWNWARD_0;
			MOVE_RIGHT_C = MOVE_RIGHT_0;
			MOVE_LEFT_C = MOVE_LEFT_0;
		}
		else if (player_current == 2) {
			MOVE_UPWARD_C = MOVE_UPWARD_1;
			MOVE_DOWNWARD_C = MOVE_DOWNWARD_1;
			MOVE_RIGHT_C = MOVE_RIGHT_1;
			MOVE_LEFT_C = MOVE_LEFT_1;
		}
		if (GetKeyState(MOVE_UPWARD_C) < 0) {
			player_direction->at(player_current - 1) = MOVE_UPWARD;
		}
		else if (GetKeyState(MOVE_DOWNWARD_C) < 0) {
			player_direction->at(player_current - 1) = MOVE_DOWNWARD;
		}
		else if (GetKeyState(MOVE_RIGHT_C) < 0) {
			player_direction->at(player_current - 1) = MOVE_RIGHT;
		}
		else if (GetKeyState(MOVE_LEFT_C) < 0) {
			player_direction->at(player_current - 1) = MOVE_LEFT;
		}
		else if (GetKeyState(INTERACT_QUIT) < 0) {
			system("cls"); // Yeah, it's unsafe, I don't care.
			std::exit(EXIT_SUCCESS);
		}
	}

	// ----------- //
	// Do movement //
	if (event_type_temporary == MOVE_UPWARD ||
		event_type_temporary == MOVE_DOWNWARD ||
		event_type_temporary == MOVE_RIGHT ||
		event_type_temporary == MOVE_LEFT &&
		entity_player_temporary != nullptr) {
		int prev_y_pos_0;
		int prev_y_pos_1;
		int prev_y_pos_2;
		int prev_x_pos_0;
		int prev_x_pos_1;
		int prev_x_pos_2;
		prev_y_pos_0 = entity_player_temporary->head_y_pos;
		prev_y_pos_1 = entity_player_temporary->head_y_pos;
		prev_x_pos_0 = entity_player_temporary->head_x_pos;
		prev_x_pos_1 = entity_player_temporary->head_x_pos;
		for (auto& element : entity_player_temporary->body_vector) {
			prev_y_pos_2 = element.y_pos;
			prev_x_pos_2 = element.x_pos;
			element.y_pos = prev_y_pos_1;
			element.x_pos = prev_x_pos_1;
			prev_y_pos_1 = prev_y_pos_2;
			prev_x_pos_1 = prev_x_pos_2;
		}
		switch (event_type_temporary) {
		case MOVE_UPWARD: {
			--entity_player_temporary->head_y_pos;
			break;
		}
		case MOVE_DOWNWARD: {
			++entity_player_temporary->head_y_pos;
			break;
		}
		case MOVE_RIGHT: {
			++entity_player_temporary->head_x_pos;
			break;
		}
		case MOVE_LEFT: {
			--entity_player_temporary->head_x_pos;
			break;
		}
		}
	}

	// --------- //
	// Hit fruit //
	switch (event_type_temporary) {
	case INTERACT_FRUIT: {
		if (entity_player_temporary != nullptr && entity_item_temporary != nullptr) {
			if (entity_player_temporary->body_vector.size() > 0) {
				entity_player_temporary->body_vector.push_back({
					'o',
					entity_player_temporary->body_vector[entity_player_temporary->body_vector.size() - 1].x_pos,
					entity_player_temporary->body_vector[entity_player_temporary->body_vector.size() - 1].y_pos
					});
			}
			else if (entity_player_temporary->body_vector.size() == 0) {
				entity_player_temporary->body_vector.push_back({
					'o',
					entity_player_temporary->head_x_pos,
					entity_player_temporary->head_y_pos
				});
			}
			entity_item_temporary->y_pos = random_between(2, *height - 2);
			entity_item_temporary->x_pos = random_between(2, *width - 2);
		}
		break;
	}

	// -------- //
	// Hit wall //
	case INTERACT_WALL: {
		if (player_amount >= 0 && player_amount <= 2 && entity_player_temporary != nullptr) {
			if (entity_player_temporary != nullptr &&
				player_amount >= 0 &&
				player_amount <= 2 &&
				entity_player_temporary->player_number >= 0 &&
				entity_player_temporary->player_number <= 1) {
				if (entity_player_temporary->head_x_pos == 0) {
					entity_player_temporary->head_x_pos = *width - 1;
				}
				else if (entity_player_temporary->head_x_pos == *width) {
					entity_player_temporary->head_x_pos = 1;
				}
				if (entity_player_temporary->head_y_pos == 0) {
					entity_player_temporary->head_y_pos = *height - 1;
				}
				else if (entity_player_temporary->head_y_pos == *height) {
					entity_player_temporary->head_y_pos = 1;
				}
			}
			break;
		}
	}

	// ---------- //
	// Hit player //
	case INTERACT_PLAYER: {
		if (player_amount >= 0 && player_amount <= 2 && entity_player_temporary != nullptr) {
			entity_player_temporary->body_vector.clear();
			entity_player_temporary->head_y_pos = random_between(2, *height - 2);
			entity_player_temporary->head_x_pos = random_between(2, *width - 2);
		}
		break;
	}
	}
}