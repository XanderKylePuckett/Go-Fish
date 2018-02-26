#pragma once
#include "stdafx.h"

#include <sstream>

/* DONE Lab2:
		Make Computer a child of Player
		*/
#include "Player.h"

class Computer : public Player
{
	int compNumber;

	public:
	// Default ctor
	// In:	_name		The name of the computer player

	/* DONE Lab2:
			Set the default value of _name to "Computer"
			*/
	Computer( const char* _name = "Computer" );

	void CreateName( int _playerNum );

	// Display the computer's name and card backs
	void Show() const;
	void ShowFish() const;

	int AskValue( const char* _target ) const;
	int AskTarget( int _numPlayers, int _currPlayer ) const;

	// Needed for unit tests
	// DO NOT REMOVE
	friend class CTestManager;
};

// ☻☺ トニー ☺☻ //