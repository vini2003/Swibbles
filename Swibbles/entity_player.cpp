#include "entity_player.hpp"

// ----------- //
// Constructor //
entity_player::entity_player(char head_symbol_c, char body_symbol_c, int entity_x_pos_c, int entity_y_pos_c, int* null, std::string player_color) {
	entity_player::head_symbol = head_symbol_c;
	entity_player::body_symbol = body_symbol_c;
	entity_player::head_x_pos = entity_x_pos_c;
	entity_player::head_y_pos = entity_y_pos_c;
	entity_player::player_color = player_color;
}