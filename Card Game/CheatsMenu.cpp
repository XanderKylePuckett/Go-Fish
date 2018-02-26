#include "CheatsMenu.h"

CheatsMenu::CheatsMenu() : BaseMenu()
{
	numChoices = 12;
	strcpy_s( m_settingsItem[ 0 ].itemName, 32, "AutoRun" ); // 0x0001 // 2^0
	strcpy_s( m_settingsItem[ 1 ].itemName, 32, "MaxAuto" ); // 0x0002 // 2^1
	strcpy_s( m_settingsItem[ 2 ].itemName, 32, "CumulativeScore" ); // 0x0004 // 2^2
	strcpy_s( m_settingsItem[ 3 ].itemName, 32, "AllCPU" ); // 0x0008 // 2^3
	strcpy_s( m_settingsItem[ 4 ].itemName, 32, "ShowCPUAsk" ); // 0x0010 // 2^4
	strcpy_s( m_settingsItem[ 5 ].itemName, 32, "NoDelayCPUAsk" ); // 0x0020 // 2^5
	strcpy_s( m_settingsItem[ 6 ].itemName, 32, "VocaloidNames" ); // 0x0040 // 2^6
	strcpy_s( m_settingsItem[ 7 ].itemName, 32, "ShowAllCards" ); // 0x0080 // 2^7
	strcpy_s( m_settingsItem[ 8 ].itemName, 32, "DisplayMods" ); // 0x0100 // 2^8
	strcpy_s( m_settingsItem[ 9 ].itemName, 32, "ShowDeck" ); // 0x0200 // 2^9
	strcpy_s( m_settingsItem[ 10 ].itemName, 32, "SkipCPU" ); // 0x0400 // 2^10
	for ( int i = 0; i <= 10; i++ )
	{
		m_settingsItem[ i ].numChoices = 2;
		m_settingsItem[ i ].currChoice = 0;
		strcpy_s( m_settingsItem[ i ].itemChoice[ 0 ], 32, "ON" );
		strcpy_s( m_settingsItem[ i ].itemChoice[ 1 ], 32, "OFF" );
	}

	strcpy_s( m_settingsItem[ 11 ].itemName, 32, "Exit" );
	m_settingsItem[ 11 ].numChoices = 3;
	m_settingsItem[ 11 ].currChoice = 0;
	strcpy_s( m_settingsItem[ 11 ].itemChoice[ 0 ], 32, "Main Menu" );
	strcpy_s( m_settingsItem[ 11 ].itemChoice[ 1 ], 32, "Play Game" );
	strcpy_s( m_settingsItem[ 11 ].itemChoice[ 2 ], 32, "Exit Game" );
	strcpy_s( m_settingsItem[ 11 ].desc, 200, "Exit Menu" );

	strcpy_s( m_settingsItem[ 0 ].desc, 200, "Run several games between only CPU players (This WILL turn on AllCPU)" );		   //"AutoRun" );
	strcpy_s( m_settingsItem[ 1 ].desc, 200, "Auto runs the maximum number of games between only CPU players (AutoRun must be ON)" );		   //"MaxAuto" );
	strcpy_s( m_settingsItem[ 2 ].desc, 200, "Allow score to accumulate between all games in a session" );   //"CumulativeScore" );
	strcpy_s( m_settingsItem[ 3 ].desc, 200, "Watch a game of only CPU players (If ON, this WILL turn on NoDelayCPUAsk and turn off ShowCPUAsk)" );	  //"AllCPU" );
	strcpy_s( m_settingsItem[ 4 ].desc, 200, "Show prompts when CPU is choosing (AllCPU must be OFF)" );	   //"ShowCPUAsk" );
	strcpy_s( m_settingsItem[ 5 ].desc, 200, "Disable \"human-like\" delay when CPU is choosing (delay will stay disabled if AllCPU is ON)" );	   //"NoDelayCPUAsk" );
	strcpy_s( m_settingsItem[ 6 ].desc, 200, "CPU Players have the names of Japanese Vocaloids" );	   //"VocaloidNames" );
	strcpy_s( m_settingsItem[ 7 ].desc, 200, "CHEAT: Show All of your opponents' cards" );	   //"ShowAllCards" );
	strcpy_s( m_settingsItem[ 8 ].desc, 200, "Show which mods are active during the game" );	   //"DisplayMods" );
	strcpy_s( m_settingsItem[ 9 ].desc, 200, "CHEAT: Show the next 10 cards from the top of the deck" );		   //"ShowDeck" );
	strcpy_s( m_settingsItem[ 10 ].desc, 200, "CHEAT: CPU players will always go fish until the deck and all human players' hands are empty (AllCPU must be OFF)" );		   //"SkipCPU" );
}


CheatsMenu::~CheatsMenu()
{

}

// draw menu
void CheatsMenu::Draw()
{
	Sleep( 5 );
	System::Console::Lock( true );
	Sleep( 5 );
	System::Console::BackgroundColor( System::Gray );
	System::Console::Clear();

	System::Console::ForegroundColor( System::Red );
	System::Console::SetCursorPosition( 10, 3 );
	std::cout << "Options";

	System::Console::ForegroundColor( PLAYER_COL );
	for ( int i = 0; i < numChoices; i++ )
	{
		System::Console::SetCursorPosition( 10, 5 + i );
		if ( i == 7 || i == 9 || i == 10 )
		{
			System::Console::ForegroundColor( System::Green );
			std::cout << "<CHEAT> ";
			System::Console::ForegroundColor( PLAYER_COL );
		}
		std::cout << m_settingsItem[ i ].itemName;
		for ( int j = 0; j < m_settingsItem[ i ].numChoices; j++ )
		{
			System::Console::SetCursorPosition( 40 + 15 * j, 5 + i );
			for ( int k = 0; k < ( int )strlen( m_settingsItem[ i ].itemChoice[ j ] ); k++ )
				std::cout << ( char )tolower( m_settingsItem[ i ].itemChoice[ j ][ k ] );
		}
		System::Console::SetCursorPosition( 40 + 15 * m_settingsItem[ i ].currChoice - 4, 5 + i );
		std::cout << "--> ";
		for ( int j = 0; j < ( int )strlen( m_settingsItem[ i ].itemChoice[ m_settingsItem[ i ].currChoice ] ); j++ )
			std::cout << ( char )toupper( m_settingsItem[ i ].itemChoice[ m_settingsItem[ i ].currChoice ][ j ] );
	}
	System::Console::ForegroundColor( CURR_PLAYER_COL );
	System::Console::SetCursorPosition( 10 - 4, 5 + currChoice );
	std::cout << "--> ";
	if ( currChoice == 7 || currChoice == 9 || currChoice == 10 )
	{
		System::Console::ForegroundColor( System::Red );
		std::cout << "<CHEAT> ";
		System::Console::ForegroundColor( CURR_PLAYER_COL );
	}
	std::cout << m_settingsItem[ currChoice ].itemName;
	System::Console::SetCursorPosition( 40 + 15 * m_settingsItem[ currChoice ].currChoice - 4, 5 + currChoice );
	std::cout << "--> ";
	for ( int j = 0; j < ( int )strlen( m_settingsItem[ currChoice ].itemChoice[ m_settingsItem[ currChoice ].currChoice ] ); j++ )
		std::cout << ( char )toupper( m_settingsItem[ currChoice ].itemChoice[ m_settingsItem[ currChoice ].currChoice ][ j ] );
	System::Console::SetCursorPosition( 10, 5 + numChoices + 2 );
	std::cout << m_settingsItem[ currChoice ].desc;

	System::Console::ResetColor();
	Sleep( 5 );
	System::Console::Lock( false );
	Sleep( 5 );
}

// in: key (0=nokey) (1up,2down,3left,4right,5enter,6esc), return: new Gamestate
GAMESTATE CheatsMenu::Update( short _keypress )
{
	if ( !( mods & GFMOD_AUTORUN ) ) mods &= ~GFMOD_MAXAUTO;
	autoRuns = ( ( mods & GFMOD_MAXAUTO ) ? INT_MAX : 12 );
	if ( ( mods & GFMOD_AUTORUN ) && autoRuns <= 0 ) autoRuns = 1;
	if ( !( mods & GFMOD_AUTORUN ) ) autoRuns = 0;
	if ( autoRuns == 0 ) autoRunPlayers = 0;
	else autoRunPlayers = 4;
	if ( autoRuns > 0 ) mods |= GFMOD_ALLCPU;
	if ( mods & GFMOD_ALLCPU )
	{
		mods |= GFMOD_NODELAYCPUASK;
		mods &= ~GFMOD_SHOWCPUASK;
		mods &= ~GFMOD_SKIPCPU;
	}

	for ( int i = 0; i < numChoices - 1; i++ )
	{
		m_settingsItem[ i ].currChoice = ( mods & ( 1 << i ) ) ? 0 : 1;
	}

	switch ( _keypress )
	{
		case 1:
		{
			if ( currChoice == numChoices - 1 )
				m_settingsItem[ currChoice ].currChoice = 0;
			currChoice <= 0 ?
				currChoice = numChoices - 1 :
				currChoice--;
		}
		break;
		case 2:
		{
			if ( currChoice == numChoices - 1 )
				m_settingsItem[ currChoice ].currChoice = 0;
			currChoice >= numChoices - 1 ?
				currChoice = 0 :
				currChoice++;
		}
		break;
		case 3:
		{
			m_settingsItem[ currChoice ].currChoice <= 0 ?
				m_settingsItem[ currChoice ].currChoice = m_settingsItem[ currChoice ].numChoices - 1 :
				m_settingsItem[ currChoice ].currChoice--;
			if ( currChoice != numChoices - 1 )
			{
				if ( m_settingsItem[ currChoice ].currChoice == 0 )
					mods |= ( 1 << currChoice );
				else if ( m_settingsItem[ currChoice ].currChoice == 1 )
					mods &= ~( 1 << currChoice );
			}
		}
		break;
		case 4:
		{
			m_settingsItem[ currChoice ].currChoice >= m_settingsItem[ currChoice ].numChoices - 1 ?
				m_settingsItem[ currChoice ].currChoice = 0 :
				m_settingsItem[ currChoice ].currChoice++;
			if ( currChoice != numChoices - 1 )
			{
				if ( m_settingsItem[ currChoice ].currChoice == 0 )
					mods |= ( 1 << currChoice );
				else if ( m_settingsItem[ currChoice ].currChoice == 1 )
					mods &= ~( 1 << currChoice );
			}
		}
		break;
		case 5:
		{
			if ( currChoice == numChoices - 1 ) //exit
			{
				switch ( m_settingsItem[ currChoice ].currChoice )
				{
					case 0: // Main Menu
						return GFMAIN_MENU;
						break;
					case 1: // Play Game
						return GAME_INIT;
						break;
					case 2: // Exit Game
						return EXIT_GAME;
						break;
					default:
						break;
				}
			}
			else
				currChoice >= numChoices - 1 ? currChoice = 0 : currChoice++;
		}
		break;
		case 6:
			return GFMAIN_MENU2;
			break;
		default:
			break;
	}

	return MENU_LOOP;
}

// ☻☺ トニー ☺☻ //