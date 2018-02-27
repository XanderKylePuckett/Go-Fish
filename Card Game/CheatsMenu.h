#pragma once
#include "BaseMenu.h"

class CheatsMenu : public BaseMenu
{
public:
	CheatsMenu();
	~CheatsMenu();

	void Draw( void ); // draw menu
	GAMESTATE Update( short ); // in: key (0=nokey) (1up,2down,3left,4right,5enter,6esc), return: new Gamestate
};

// ☻☺ トニー ☺☻ //