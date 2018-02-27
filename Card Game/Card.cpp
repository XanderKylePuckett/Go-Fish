#include "Card.h"

// Default constructor
// In:	_face			The face value of the card
//		_suit			The suit of the card
Card::Card( int _face, char _suit )
{
	/* DONE Lab1:
			Fill out the constructor body
			*/

	m_face = _face;
	m_suit = _suit;

}

Card::~Card()
{

}


/* Accessors */

/* DONE (inlined) Lab1:
		Define the two accessors if they were not inlined.
		*/

		/* Mutators */

		/* DONE (inlined) Lab1:
				Define the two mutators if they were not inlined.
				*/

				// Display a card to the screen
void Card::Show() const
{
	/* DONE Lab1:
			Display the Card object.

			Make sure that "face" cards (Jack-Ace) display as 'J', 'Q', 'K', 'A'
			or something similar instead of their numeric value.

			*Note - This unit test is not automated, so make sure you verify
			the face card is displaying correctly.
			*/

	System::Console::BackgroundColor( System::White );
	System::Console::ForegroundColor( ( WORD )( ( ( int )m_suit <= 4 ) ? ( System::Red ) : ( System::Black ) ) );
	std::cout << *this;
	System::Console::ResetColor();
}

// Relational operators

/* DONE (inlined) Lab1:
		Define the six relational operators if they were not inlined.
		*/

		// Insertion operator to display Cards with cout (or any other ostream object)

		/* TODO Lab1:
				Define the insertion operator to display a card.

				Make sure that "face" cards (Jack-Ace) display as 'J', 'Q', 'K', 'A'
				or something similar instead of their numeric value.

				*Note - This unit test is not automated, so make sure you verify
				the face card is displaying correctly.
				*/

std::ostream& operator<<( std::ostream& _os, const Card& _rhs )
{
	if ( _rhs.GetFace() > 10 )
	{
		switch ( _rhs.GetFace() )
		{
			case 11:
				_os << 'J';
				break;
			case 12:
				_os << 'Q';
				break;
			case 13:
				_os << 'K';
				break;
			case 14:
				_os << 'A';
				break;
			default:
				break;
		}
	}
	else
	{
		_os << _rhs.GetFace();
	}

	if ( _rhs.GetFace() != 10 )
		_os << ' ';

	_os << _rhs.GetSuit();

	return _os;
}

// ☻☺ トニー ☺☻ //