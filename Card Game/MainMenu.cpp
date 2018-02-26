#include "MainMenu.h"


MainMenu::MainMenu()
{
	numChoices = 5;
	strcpy_s( m_menuItem[ 0 ].itemName, 32, "Play Game" );
	strcpy_s( m_menuItem[ 1 ].itemName, 32, "Options" );
	strcpy_s( m_menuItem[ 2 ].itemName, 32, "Instructions" );
	strcpy_s( m_menuItem[ 3 ].itemName, 32, "Reset Scores" );
	strcpy_s( m_menuItem[ 4 ].itemName, 32, "Exit" );

	strcpy_s( m_menuItem[ 0 ].desc, 200, "Start a new game" );
	strcpy_s( m_menuItem[ 1 ].desc, 200, "Set Options/Cheats/Mods" );
	strcpy_s( m_menuItem[ 2 ].desc, 200, "Learn how to play" );
	strcpy_s( m_menuItem[ 3 ].desc, 200, "Reset all the high scores" );
	strcpy_s( m_menuItem[ 4 ].desc, 200, "Exit the Game" );

	gameRuns = 0;
}

MainMenu::MainMenu( bool second ) : MainMenu::MainMenu()
{
	if ( second )
		currChoice = 1;
}

MainMenu::~MainMenu()
{

}

void MainMenu::Draw( void )
{
	Sleep( 5 );
	System::Console::Lock( true );
	Sleep( 5 );
	System::Console::BackgroundColor( System::DarkBlue );
	System::Console::Clear();

	System::Console::ForegroundColor( System::Red );
	System::Console::SetCursorPosition( 10, 3 );
	std::cout << "Main Menu";

	System::Console::ForegroundColor( PLAYER_COL );
	for ( int i = 0; i < numChoices; i++ )
	{
		System::Console::SetCursorPosition( 10, 5 + i );
		std::cout << m_menuItem[ i ].itemName;
	}
	System::Console::ForegroundColor( CURR_PLAYER_COL );
	System::Console::SetCursorPosition( 10 - 4, 5 + currChoice );
	std::cout << "--> ";
	std::cout << m_menuItem[ currChoice ].itemName;
	System::Console::SetCursorPosition( 10, 5 + numChoices + 2 );
	std::cout << m_menuItem[ currChoice ].desc;

	System::Console::ResetColor();
	Sleep( 5 );
	System::Console::Lock( false );
	Sleep( 5 );
}

GAMESTATE MainMenu::Update( short _keypress )
{
	switch ( _keypress )
	{
		case 1:
		{
			currChoice <= 0 ?
				currChoice = numChoices - 1 :
				currChoice--;
		}
		break;
		case 2:
		{
			currChoice >= numChoices - 1 ?
				currChoice = 0 :
				currChoice++;
		}
		break;
		case 5:
		{
			switch ( currChoice )
			{
				case 0: //"Play Game"
					return GAME_INIT;
					break;
				case 1: //"Options"
					return GFMODS_MENU;
					break;
				case 2: //"Instructions"
					gfhowtopage = 0;
					return GF_HOWTO;
					break;
				case 3: //"Reset Scores"
					return CLEAR_SCORES;
					break;
				case 4: //"Exit"
					return EXIT_GAME;
					break;
				default:
					break;
			}
		}
		default:
			break;
	}

	return MENU_LOOP;
}