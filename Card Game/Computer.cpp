#include "Computer.h"
// Default ctor
Computer::Computer( const char* _name ) : Player( _name )
{
	/* DONE (i think) Lab2:
			Implement this method.

			Send back the appropriate information to the parent/base class.
			*/

	numCPUs++;
	compNumber = numCPUs;
}

void Computer::CreateName( int _playerNum )
{
	_playerNum = compNumber;
	std::ostringstream o;
	o << "CPU_" << _playerNum;
	SetName( o.str().c_str() );
}

// Display the computer's name and card backs
void Computer::Show() const
{
	/* DONE (i think) Lab2:
			Implement this method.

			Should display the name of the player as well as their card backs.

			Example:		Computer
			XX XX XX XX Dos Equis x4

			*/

	std::cout << GetName() << "\n";
	for ( int i = 0; i < GetNumCards(); i++ )
	{
		if ( ( mods & GFMOD_ALLCPU ) || ( mods & GFMOD_SHOWALLCARDS ) )
		{
			Card card;
			if ( GetCard( i, card ) )
			{
				card.Show();
			}
		}
		else
		{
			System::Console::BackgroundColor( System::Red );
			System::Console::ForegroundColor( System::White );
			int card = 177;
			std::cout << ( unsigned char )card << ( unsigned char )card << ( unsigned char )card;
			System::Console::ResetColor();
		}
		if ( i != GetNumCards() - 1 )
			std::cout << ' ';
	}

}

void Computer::ShowFish() const
{
	if ( mods & ( GFMOD_ALLCPU | GFMOD_SHOWALLCARDS ) ) //if ( ( mods & GFMOD_ALLCPU ) || ( mods & GFMOD_SHOWALLCARDS ) )
	{
		if ( GetNumCards() == 0 )
			return; // Display nothing

		Card card;
		GetCard( GetNumCards() - 1, card );
		card.Show();
	}
	else
	{
		System::Console::BackgroundColor( System::Red );
		System::Console::ForegroundColor( System::White );
		int card = 177;
		std::cout << ( unsigned char )card << ( unsigned char )card << ( unsigned char )card;
		System::Console::ResetColor();
	}
}

int Computer::AskValue( const char* _target ) const
{
	if ( mods & GFMOD_SHOWCPUASK )
	{
		std::cout << "You are asking ";
		System::Console::ForegroundColor( PLAYER_COL );
		std::cout << _target << std::endl;
		System::Console::ResetColor();
		std::cout << "Which card do you want to ask for?" << std::endl;
	}

	if ( GetNumCards() == 0 )
		return 0;

	Card card;
	if ( !GetCard( rand() % GetNumCards(), card ) )
		return 0;

	if ( !( mods & GFMOD_ALLCPU ) && !( mods & GFMOD_NODELAYCPUASK ) )
		Sleep( rand() % 2101 + 750 );

	if ( mods & GFMOD_SHOWCPUASK )
	{
		int faceValue = card.GetFace();
		char face[ 3 ] = "0";

		switch ( faceValue )
		{
			case 2:
				strcpy_s( face, 3, "2" );
				break;
			case 3:
				strcpy_s( face, 3, "3" );
				break;
			case 4:
				strcpy_s( face, 3, "4" );
				break;
			case 5:
				strcpy_s( face, 3, "5" );
				break;
			case 6:
				strcpy_s( face, 3, "6" );
				break;
			case 7:
				strcpy_s( face, 3, "7" );
				break;
			case 8:
				strcpy_s( face, 3, "8" );
				break;
			case 9:
				strcpy_s( face, 3, "9" );
				break;
			case 10:
				strcpy_s( face, 3, "10" );
				break;
			case 11:
				strcpy_s( face, 3, "J" );
				break;
			case 12:
				strcpy_s( face, 3, "Q" );
				break;
			case 13:
				strcpy_s( face, 3, "K" );
				break;
			case 14:
				strcpy_s( face, 3, "A" );
				break;
			default:
				break;
		}

		std::cout << face;
		std::cout << std::endl;
	}

	if ( !( mods & GFMOD_ALLCPU ) && !( mods & GFMOD_NODELAYCPUASK ) )
		Sleep( 450 );

	return card.GetFace();
}

int Computer::AskTarget( int _numPlayers, int _currPlayer ) const
{
	int target = _currPlayer;
	while ( target == _currPlayer )
		target = rand() % _numPlayers;

	if ( !( mods & GFMOD_ALLCPU ) && !( mods & GFMOD_NODELAYCPUASK ) )
		Sleep( rand() % 1201 + 750 );

	if ( mods & GFMOD_SHOWCPUASK )
	{
		std::cout << target;
		if ( !( mods & GFMOD_ALLCPU ) && !( mods & GFMOD_NODELAYCPUASK ) )
			Sleep( 450 );
		std::cout << std::endl;
	}
	else if ( !( mods & GFMOD_ALLCPU ) && !( mods & GFMOD_NODELAYCPUASK ) )
		Sleep( 450 );
	return target;
}

// ☻☺ トニー ☺☻ //