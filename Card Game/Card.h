#pragma once
#include "stdafx.h"

class Card
{
	int m_face;		// 2-14, with 14 being the Ace
	char m_suit;	// 3-6 (3 = Hearts(♥), 4 = Diamonds(♦), 5 = Clubs(♣), 6 = Spades(♠))

public:

	// Default constructor
	Card( int _face = 2, char _suit = 3 );

	// Destructor
	~Card();

	/* Accessors */

	int GetFace() const
	{
		return m_face;
	}

	char GetSuit() const
	{
		return m_suit;
	}

	/* Mutators */

	void SetFace( int _face )
	{
		m_face = _face;
	}

	void SetSuit( char _suit )
	{
		m_suit = _suit;
	}

	// Display a card to the screen
	void Show() const;

	// Relational operators
	bool operator >( const Card &_rhs ) const
	{
		return m_face > _rhs.m_face;
	}

	bool operator >=( const Card &_rhs ) const
	{
		return m_face >= _rhs.m_face;
	}

	bool operator <( const Card &_rhs ) const
	{
		return m_face < _rhs.m_face;
	}

	bool operator <=( const Card &_rhs ) const
	{
		return m_face <= _rhs.m_face;
	}

	bool operator !=( const Card &_rhs ) const
	{
		return m_face != _rhs.m_face;
	}

	bool operator ==( const Card &_rhs ) const
	{
		return m_face == _rhs.m_face;
	}

	// Insertion operator to display Cards with cout (or any other ostream object)
	friend std::ostream& operator<<( std::ostream &_os, const Card &_rhs );

	// Needed for unit tests
	// DO NOT REMOVE
	friend class CTestManager;

};

// ☻☺ トニー ☺☻ //