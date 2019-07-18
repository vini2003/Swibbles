#include "entity_item.hpp"

// ----------- //
// Constructor //
entity_item::entity_item(char symbol_c, int entity_x_pos_c, int entity_y_pos_c) {
	entity_item::symbol = symbol_c;
	entity_item::x_pos = entity_x_pos_c;
	entity_item::y_pos = entity_y_pos_c;
}