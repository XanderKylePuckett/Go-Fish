#pragma once
#include "stdafx.h"
#include "Card.h"
#include "Stack.h"

// A Deck of cards
class Deck
{
	// Needed for unit tests
	// DO NOT REMOVE OR RENAME
#if GO_FISH
	Card m_cards[ 52 ];
#elif UNO
	//Card m_cards[108];
#endif

	Stack <Card> m_Stack;

public:

	// Default ctor
	Deck();

	// Sets up the array of cards to be a unique deck
	void Initialize();

	/* Clears any cards that are already in the stack, shuffles the array, and then pushes
	   all of the shuffled cards onto the stack. */
	void Shuffle();

	// Draw the top-most card off of the stack
	bool Draw( Card& _card );

	bool Restore( const Card& _card );

	// Clear the stack for re-use
	void Clear();

	// Check to see if there are any cards left in the stack
	bool IsEmpty() const;

	int Deck::Size() const;

	// Needed for unit tests
	// DO NOT REMOVE
	friend class CTestManager;

};

// ☻☺ トニー ☺☻ //