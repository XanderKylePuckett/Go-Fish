#include "Human.h"

// Default ctor
Human::Human( const char* _name ) : Player( _name )
{
	/* DONE (i think) Lab2:
	Implement this method.

	Send back the appropriate information to the parent/base class.
	*/
}


// Display the computer's name and card backs
void Human::Show() const
{
	/* DONE (i think) Lab2:
	Implement this method.

	Should display the name of the player as well as their card faces

	Example:		Human
	7♥ 3♣ 5♦ 9♥

	*/

	std::cout << GetName() << "\n";
	for ( int i = 0; i < GetNumCards(); i++ )
	{
		Card card;
		if ( GetCard( i, card ) )
		{
			card.Show();
			if ( i != GetNumCards() - 1 )
				std::cout << ' ';
		}
	}
}

void Human::ShowFish() const
{
	if ( GetNumCards() == 0 )
		return; // Display nothing

	Card card;
	GetCard( GetNumCards() - 1, card );
	card.Show();
}

void Human::CreateName( int _playerNum )
{
	std::cout << "Player " << _playerNum << ":\n";
	char name[ NAME_MAX_LENGTH ];
	for ( ;; )
	{
		std::cout << "Name: ";
		if ( std::cin.get( name, NAME_MAX_LENGTH ) )
		{
			std::cin.ignore( INT_MAX, '\n' );
			break;
		}
		std::cin.clear();
		std::cin.ignore( INT_MAX, '\n' );
	}

	SetName( name );
}

int Human::AskValue( const char* _target ) const
{
	char faceValue[ 4 ];
	int value;
	Card card;

	for ( ;; )
	{
		for ( ;; )
		{
			std::cout << "You are asking ";
			System::Console::ForegroundColor( PLAYER_COL );
			std::cout << _target << std::endl;
			System::Console::ResetColor();
			std::cout << "Which card do you want to ask for?" << std::endl;
			if ( std::cin.get( faceValue, 4 ) )
			{
				std::cin.ignore( INT_MAX, '\n' );

				if ( faceValue[ 0 ] == '1' && faceValue[ 1 ] == '0' && faceValue[ 2 ] == '\0' )
					value = 10;
				else if ( faceValue[ 1 ] != '\0' )
					continue;
				else
					switch ( toupper( faceValue[ 0 ] ) )
					{
						case 'A':
							value = 14;
							break;
						case 'J':
							value = 11;
							break;
						case 'Q':
							value = 12;
							break;
						case 'K':
							value = 13;
							break;
						default:
							if ( ( int )faceValue[ 0 ] >= '2' && ( int )faceValue[ 0 ] <= '9' )
								value = ( int )faceValue[ 0 ] - '0';
							else
								continue;
					}
				break;
			}
			std::cin.clear();
			std::cin.ignore( INT_MAX, '\n' );
		}

		for ( int i = 0; i < GetNumCards(); i++ )
		{
			GetCard( i, card );
			if ( card.GetFace() == value )
				return value;
		}

		System::Console::ForegroundColor( System::Yellow );
		std::cout << "You do not have that card in your hand" << std::endl;
		System::Console::ResetColor();
	}
}

int Human::AskTarget( int _numPlayers, int _currPlayer ) const
{
	int target = _numPlayers;
	System::Console::FlushKeys();
	while ( target < 0 || target >= _numPlayers || target == _currPlayer )
	{
		if ( GetAsyncKeyState( '0' ) || GetAsyncKeyState( VK_NUMPAD0 ) )
		{
			System::Console::FlushKeys();
			target = 0;
		}
		else if ( GetAsyncKeyState( '1' ) || GetAsyncKeyState( VK_NUMPAD1 ) )
		{
			System::Console::FlushKeys();
			target = 1;
		}
		else if ( GetAsyncKeyState( '2' ) || GetAsyncKeyState( VK_NUMPAD2 ) )
		{
			System::Console::FlushKeys();
			target = 2;
		}
		else if ( GetAsyncKeyState( '3' ) || GetAsyncKeyState( VK_NUMPAD3 ) )
		{
			System::Console::FlushKeys();
			target = 3;
		}
	}

	return target;
}

// ☻☺ トニー ☺☻ //