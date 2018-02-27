#pragma once
#include "stdafx.h"

class BaseMenu
{
protected:

	struct SettingsItem
	{
		char itemName[ 32 ];
		char itemChoice[ 10 ][ 32 ];
		int numChoices;
		int currChoice;
		char desc[ 200 ];
	};

	struct MenuItem
	{
		char itemName[ 32 ];
		char desc[ 200 ];
	};

	int currChoice;
	int numChoices;

	MenuItem m_menuItem[ 32 ];
	SettingsItem m_settingsItem[ 32 ];

public:
	BaseMenu();
	virtual ~BaseMenu() = 0;

	virtual void Draw( void ) = 0; // draw menu

	// return key (0=nokey) (1up,2down,3left,4right,5enter,6esc)
	static short Input( void );

	virtual GAMESTATE Update( short ) = 0; // in: key (0=nokey) (1up,2down,3left,4right,5enter,6esc), return: new Gamestate
};

// ☻☺ トニー ☺☻ //