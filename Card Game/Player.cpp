#include "Player.h"

// Default ctor
Player::Player( const char* _name, int _maxCards ) : m_maxCards( _maxCards )
{
	m_name = new char[ strlen( _name ) + 1 ];
	strcpy_s( m_name, strlen( _name ) + 1, _name );

	m_hand = new Card[ _maxCards ];

	m_numCards = 0;
};

Player::Player( const Player& _obj ) : m_maxCards( _obj.m_maxCards )
{
	m_name = new char[ strlen( _obj.m_name ) + 1 ];
	strcpy_s( m_name, strlen( _obj.m_name ) + 1, _obj.m_name );

	m_hand = new Card[ m_maxCards ];
	for ( int i = 0; i < m_maxCards; i++ )
	{
		m_hand[ i ].SetFace( _obj.m_hand[ i ].GetFace() );
		m_hand[ i ].SetSuit( _obj.m_hand[ i ].GetSuit() );
	}

	m_numCards = _obj.m_numCards;
};

// Dtor
Player::~Player()
{
	delete[ ] m_name;
	delete[ ] m_hand;
}

/* There will be a small change to this in Lab5 where you will have to comment out
   the m_maxCards assignment, but go ahead and make the copy for now. */
Player& Player::operator=( const Player& _obj )
{
	if ( this != &_obj )
	{
		SetName( _obj.m_name );

		delete[ ] m_hand;
		const int handSize = _obj.GetMaxCards();
		m_hand = new Card[ handSize ];
		for ( int i = 0; i < handSize; i++ )
		{
			m_hand[ i ].SetFace( _obj.m_hand[ i ].GetFace() );
			m_hand[ i ].SetSuit( _obj.m_hand[ i ].GetSuit() );
		}

		m_numCards = _obj.m_numCards;
		//m_maxCards = _obj.m_maxCards;
	}

	return *this;
}

// Access a Card from the player's hand
bool Player::GetCard( int _index, Card& _card ) const
{
	if ( _index < m_numCards )
	{
		_card = m_hand[ _index ];
		return true;
	}

	return false;
}

// Change the player's name to the value passed in
void Player::SetName( const char* _name )
{
	delete[ ] m_name;
	m_name = new char[ strlen( _name ) + 1 ];
	strcpy_s( m_name, strlen( _name ) + 1, _name );
}

// Add a Card to the player's hand
bool Player::AddCard( const Card& _card )
{
	if ( m_numCards < m_maxCards )
	{
		m_hand[ m_numCards ] = _card;
		m_numCards++;
		return true;
	}
	return false;
}

// Remove a Card from the player's hand
bool Player::Discard( int _index, Card& _discard )
{
	if ( _index > m_numCards - 1 )
		return false;

	_discard = m_hand[ _index ];

	for ( int i = _index; i + 1 < m_numCards; i++ )
		m_hand[ i ] = m_hand[ i + 1 ];

	m_numCards--;

	return true;
}

// Clear the player's hand so that they are holding 0 cards
void Player::Clear()
{
	m_numCards = 0;
}

// ☻☺ トニー ☺☻ //