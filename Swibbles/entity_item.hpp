#pragma once
#ifndef _ENTITY_ITEM_
#define _ENTITY_ITEM_

class entity_item
{
public:
	// ----------- //
	// Constructor //
	entity_item(char symbol_c, int entity_x_pos_c, int entity_y_pos_c);

	// ---- //
	// Item //
	char symbol;
	int x_pos;
	int y_pos;
};

#endif
