#pragma once
#include "stdafx.h"
#include "Card.h"
#include "Deck.h"

class Player
{

private:

	char* m_name;
	Card* m_hand;
	int m_numCards;
	const int m_maxCards;

public:

	// Default ctor
	Player( const char* _name = "Player", int _maxCards = MAX_HAND );

	//copy ctor
	Player( const Player& _obj );

	// Dtor
	virtual ~Player() = 0;

	//Prototype the assignment operator
	Player& operator=( const Player& _obj );


	const char* GetName() const
	{
		return m_name;
	}

	int GetNumCards() const
	{
		return m_numCards;
	}

	int GetMaxCards() const
	{
		return m_maxCards;
	}

	// Access a Card from the player's hand
	bool GetCard( int _index, Card& _card ) const;

	// Change the player's name to the value passed in
	void SetName( const char* _name );

	// Update the player's score by some amount
	void AddToScore( int _add );

	// Add a Card to the player's hand
	bool AddCard( const Card& _card );

	// Remove a Card from the player's hand
	bool Discard( int _index, Card& _discard );

	// Clear the player's hand so that they are holding 0 cards
	void Clear();

	virtual void CreateName( int _playerNum ) = 0;

	// Display method
	virtual void Show() const = 0;

	virtual void ShowFish() const = 0;

	virtual int AskValue( const char* _target ) const = 0;
	virtual int AskTarget( int _numPlayers, int _currPlayer ) const = 0;

	// Needed for unit tests
	// DO NOT REMOVE
	friend class CTestManager;
};

// ☻☺ トニー ☺☻ //