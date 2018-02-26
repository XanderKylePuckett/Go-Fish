#include "Deck.h"

// Default ctor
Deck::Deck()
{
	Initialize();
}

// Sets up the array of cards to be a unique deck
void Deck::Initialize()
{
	int index = 0;
	for ( int i = 3; i <= 6; i++ )
	{
		for ( int j = 2; j <= 14; j++ )
		{
			m_cards[ index ].SetSuit( ( char )i );
			m_cards[ index ].SetFace( j );
			index++;
		}
	}
}

int Deck::Size() const
{
	return m_Stack.GetCurrSize();
}

/* Clears any cards that are already in the stack, shuffles the array, and then pushes
   all of the shuffled cards onto the stack. */
void Deck::Shuffle()
{
	Clear();

	for ( int i = 0; i < SHUFFLE_SWAP_COUNT; i++ )
		std::swap<Card>( m_cards[ rand() % 52 ], m_cards[ rand() % 52 ] );

	for ( Card i : m_cards )
		m_Stack.Push( i );
}

// Draw the top-most card off of the stack
bool Deck::Draw( Card& _card )
{
	return m_Stack.Pop( _card );
}

// Clear the stack for re-use
void Deck::Clear()
{
	m_Stack.Clear();
}

// Check to see if there are any cards left in the stack
bool Deck::IsEmpty() const
{
	return m_Stack.GetCurrSize() == 0;
}

bool Deck::Restore( const Card& _card )
{
	return m_Stack.Push( _card );
}

// ☻☺ トニー ☺☻ //