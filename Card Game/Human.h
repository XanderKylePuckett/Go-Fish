#pragma once
#include "stdafx.h"

/* DONE Lab2:
		Make Human a child of Player
		*/

#include "Player.h"

class Human : public Player
{

public:
	// Default ctor
	// In:	_name		The name of the human player

	/* DONE Lab2:
	Set the default value of _name to "Human"
	*/
	Human( const char* _name = "Human" );
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