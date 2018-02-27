#include "Game.h"

// Default ctor
Game::Game()
{
	m_state = GAME_INIT_ONCE;
}

// Dtor
Game::~Game()
{
	for ( int i = 0; i < MAX_PLAYERS; i++ )
	{
		delete m_players[ i ];
		m_players[ i ] = nullptr;
	}
}

void Game::Run()
{
	// Bool to control whether the game should continue to run.
	bool bRun = true;
	BaseMenu* menu = nullptr;

	// Loop while our bool remains true.
	while ( bRun )
	{
		switch ( m_state )
		{
			case GFMODS_MENU:
				delete menu;
				menu = new CheatsMenu();
				m_state = MENU_LOOP;
				break;
			case GFMAIN_MENU:
			case GFMAIN_MENU2:
				delete menu;
				menu = new MainMenu( m_state == GFMAIN_MENU2 );
				System::Console::FlushKeys();
				m_state = MENU_LOOP;
				break;
			case MENU_LOOP:
				if ( menu == nullptr )
				{
					m_state = GFMAIN_MENU;
					break;
				}
				m_state = menu->Update( menu->Input() );
				menu->Draw();
				break;
			case CLEAR_SCORES:
				ResetScores();
				break;
			case GF_HOWTO:
				m_state = ShowInstructions();
				break;
			case GAME_INIT_ONCE:

				SetMods();
				SetConsole();
				for ( int i = 0; i < MAX_PLAYERS; i++ )
					m_players[ i ] = nullptr;
				for ( int i = 0; i < MAX_PLAYERS; i++ )
					score[ i ] = 0;
				m_state = GFMAIN_MENU;
				break;
			case GAME_INIT:
			{
				for ( int i = 0; i < MAX_PLAYERS; i++ )
					score[ i ] = 0;
				delete menu;
				menu = nullptr;
				System::Console::Clear();
				int askNumPlayers = ( ( gameRuns > 0 && ( mods & GFMOD_CUMULATIVESCORE ) ) ? m_numPlayers : AskNumPlayers() );
				Initialize( askNumPlayers );
			}
			m_state = GAME_START;
			break;
			case GAME_START:
				StartIt();
				break;
			case GAME_RESTART:
				if ( ~mods & GFMOD_CUMULATIVESCORE )
					for ( int i = 0; i < MAX_PLAYERS; i++ )
						score[ i ] = 0;
				m_currPlayer = 0;
				m_Deck.Shuffle();
				m_state = GAME_START;
				break;
			case GAME_PLAY:

			{


				/*========================= PUUL HET =========================*/
				if ( CheckEmptyHand() ) break;

				int targetPlayer = m_currPlayer;
				if ( m_numPlayers == 2 )
				{
					DisplayTable();
					targetPlayer = ( m_currPlayer == 0 ? 1 : 0 );
				}
				else
				{
					while ( targetPlayer == m_currPlayer || m_players[ targetPlayer ]->GetNumCards() <= 0 )
					{
						DisplayTable();
						if ( CheckEmptyHand() ) break;
						targetPlayer = AskTarget();
					}
				}

				if ( CheckEmptyHand() ) break;

				if ( m_currPlayer == 0 && ( ~mods & GFMOD_ALLCPU ) && m_numPlayers > 2 )
					DisplayTable();
				int face = m_players[ m_currPlayer ]->AskValue( m_players[ targetPlayer ]->GetName() );

				if ( ( m_currPlayer != 0 ) && ( mods & GFMOD_SKIPCPU ) && m_players[ 0 ]->GetNumCards() > 0 && !m_Deck.IsEmpty() )
					face = 0;

				System::Console::ForegroundColor( CURR_PLAYER_COL );
				std::cout << m_players[ m_currPlayer ]->GetName();
				System::Console::ResetColor();
				std::cout << " asks ";
				System::Console::ForegroundColor( PLAYER_COL );
				std::cout << m_players[ targetPlayer ]->GetName();
				System::Console::ResetColor();
				if ( face == 0 )
					std::cout << " for nothing\n";
				else
				{
					std::cout << " for" << ( ( face == 8 || face == 14 ) ? " an " : " a " );

					System::Console::ForegroundColor( System::DarkRed );
					if ( face > 10 )
						switch ( face )
						{
							case 11:
								std::cout << 'J';
								break;
							case 12:
								std::cout << 'Q';
								break;
							case 13:
								std::cout << 'K';
								break;
							case 14:
								std::cout << 'A';
								break;
							default:
								std::cout << '?';
								break;
						}
					else
						std::cout << face;
					std::cout << '\n';
				}
				System::Console::ResetColor();

				Card temp;
				bool matchMade = false;
				for ( int i = 0; i < m_players[ targetPlayer ]->GetNumCards(); i++ )
				{
					m_players[ targetPlayer ]->GetCard( i, temp );
					if ( temp.GetFace() == face )
					{
						matchMade = true;
						m_players[ targetPlayer ]->Discard( i, temp );
						break;
					}
				}
				if ( matchMade )
				{
					score[ m_currPlayer ]++;
					System::Console::ForegroundColor( System::Green );
					std::cout << "MATCH FOUND. :D\n";
					System::Console::ForegroundColor( System::Magenta );
					std::cout << "New Score: " << score[ m_currPlayer ] << "\n\n";
					System::Console::ResetColor();
					table[ m_currPlayer ].Push( temp );
					for ( int i = 0; i < m_players[ m_currPlayer ]->GetNumCards(); i++ )
					{
						m_players[ m_currPlayer ]->GetCard( i, temp );
						if ( temp.GetFace() == face )
						{
							m_players[ m_currPlayer ]->Discard( i, temp );
							table[ m_currPlayer ].Push( temp );
							break;
						}
					}
				}
				else
				{
					System::Console::ForegroundColor( PLAYER_COL );
					if ( face != 0 )
					{
						std::cout << m_players[ targetPlayer ]->GetName();
						System::Console::ResetColor();
						std::cout << " does not have that card :(";
					}
					std::cout << '\n';
					if ( !m_Deck.IsEmpty() )
					{
						System::Console::ForegroundColor( System::Cyan );
						std::cout << "Go Fish\n";
						System::Console::ResetColor();

						if ( !GoFish() )
						{
							System::Console::ForegroundColor( System::Red );
							std::cout << "HAND OVERFLOW ERROR: TOO MANY CARDS IN HAND\nCANNOT GO FISH: CARD RETURNED TO DECK\n";
							System::Console::ResetColor();
						}
						else
						{
							m_players[ m_currPlayer ]->ShowFish();
							Card fish;
							m_players[ m_currPlayer ]->GetCard( m_players[ m_currPlayer ]->GetNumCards() - 1, fish );
							if ( face == fish.GetFace() )
								matchMade = true;
							std::cout << '\n';
						}
					}
				}

				if ( matchMade )
					m_currPlayer--;

				NextPlayer();
				/*========================= ｹﾞｰﾑﾌﾟﾚｰ =========================*/


				if ( !autoRuns )
					system( "pause" );
			}

			break;
			case GAME_END:
				if ( EndGame() )
				{
					m_state = GAME_RESTART;
				}
				else
				{
					m_state = GFMAIN_MENU;
				}
				break;
			case EXIT_GAME:
				bRun = false;
				delete menu;
				menu = nullptr;
				return;
				break;
			default:
				m_state = GAME_END;
				break;
		}
	}
	delete menu;
	menu = nullptr;
}

int Game::AskNumPlayers()
{
	int number = 0;

	if ( autoRuns > 0 )
		number = autoRunPlayers;
	else
	{
		std::cout << "How many players (2 - " << MAX_PLAYERS << ")? ";
		System::Console::FlushKeys();
		while ( number < 2 || number > MAX_PLAYERS )
		{
			if ( GetAsyncKeyState( '2' ) || GetAsyncKeyState( VK_NUMPAD2 ) )
			{
				System::Console::FlushKeys();
				number = 2;
			}
			else if ( GetAsyncKeyState( '3' ) || GetAsyncKeyState( VK_NUMPAD3 ) )
			{
				System::Console::FlushKeys();
				number = 3;
			}
			else if ( GetAsyncKeyState( '4' ) || GetAsyncKeyState( VK_NUMPAD4 ) )
			{
				System::Console::FlushKeys();
				number = 4;
			}
		}

		System::Console::Clear();
		System::Console::ForegroundColor( System::Yellow );
		std::cout << number << " Player Game" << std::endl;
		System::Console::ResetColor();
	}

	return number;
}

void Game::Initialize( int _numPlayers )
{
	for ( int i = 0; i < MAX_PLAYERS; i++ )
	{
		m_players[ i ] = nullptr;
		if ( ~mods & GFMOD_CUMULATIVESCORE )
			score[ i ] = 0;
	}

	m_numPlayers = _numPlayers;
	// Create Players
	if ( mods & GFMOD_ALLCPU )
		m_players[ 0 ] = new Computer;
	else
		m_players[ 0 ] = new Human;
	for ( int i = 1; i < m_numPlayers; i++ )
		m_players[ i ] = new Computer;

	for ( int i = 0; i < m_numPlayers; i++ )
	{
		m_players[ i ]->CreateName( i + 1 );
	}

	if ( mods & GFMOD_VOCALOIDNAMES )
	{
		if ( mods & GFMOD_ALLCPU )
			m_players[ 0 ]->SetName( "GUMI" ); //GUMI
		m_players[ 1 ]->SetName( "Hatsune Miku" ); //初音ミク
		if ( m_numPlayers > 2 )
			m_players[ 2 ]->SetName( "Megurine Luka" ); //巡音ルカ
		if ( m_numPlayers > 3 )
			m_players[ 3 ]->SetName( "Kagamine Rin" ); //鏡音リン
	}

	m_currPlayer = 0;
	m_Deck.Shuffle();
}

void Game::StartIt( void )
{
	Card tempCard;

	if ( m_numPlayers < 2 )
	{
		m_state = GAME_END;
		return;
	}

	if ( m_players[ 0 ]->GetNumCards() < START_HAND )
	{
		for ( int i = 0; i < m_numPlayers; i++ )
		{
			if ( !m_Deck.Draw( tempCard ) )
			{
				m_state = GAME_PLAY;
				return;
			}
			if ( !m_players[ i ]->AddCard( tempCard ) )
			{
				m_Deck.Restore( tempCard );
			}
		}
	}
	else
	{
		m_state = GAME_PLAY;
	}
}

bool Game::EndGame( void )
{
	System::Console::Clear();
	System::Console::ForegroundColor( System::Red );
	System::Console::BackgroundColor( System::Gray );
	std::cout << "\nGAME OVER\n\n";
	System::Console::ResetColor();
	DisplayScore();
	std::cout << "\n\n";
	if ( ~mods & GFMOD_AUTORUN )
	{
		Sleep( 1000 );
		system( "pause" );
	}
	System::Console::Clear();

	System::Console::ForegroundColor( System::Yellow );
	for ( int i = 0; i < m_numPlayers; i++ )
	{
		std::cout << m_players[ i ]->GetName() << ": " << score[ i ] << '\n';
	}
	std::cout << "\n\n";
	System::Console::ForegroundColor( System::Magenta );
	int winner = GetWinnerScore();
	for ( int i = 0; i < m_numPlayers; i++ )
	{
		if ( score[ i ] == winner )
		{
			std::cout << "Winner: " << m_players[ i ]->GetName() << std::endl;
		}
	}

	System::Console::ResetColor();

	numCPUs = 0;
	gameRuns++;

	bool restart = false;

	std::cout << "\n";
	if ( ~mods & GFMOD_CUMULATIVESCORE )
		ShowHighScores();
	std::cout << "\n";

	if ( gameRuns < autoRuns )
	{
		restart = true;
	}
	else if ( autoRuns > 0 )
	{
		restart = false;
	}
	else
	{
		std::cout << "\nWould you like to play again (restart with";
		if ( ~mods & GFMOD_CUMULATIVESCORE )
			std::cout << "out";
		std::cout << " cumulative score)? (y/n) ";
		System::Console::FlushKeys();
		for ( ;; )
		{
			if ( GetAsyncKeyState( 'Y' ) )
			{
				System::Console::FlushKeys();
				restart = true;
				break;
			}
			else if ( GetAsyncKeyState( 'N' ) )
			{
				System::Console::FlushKeys();
				restart = false;
				break;
			}
		}
	}

	if ( ( !restart ) && ( mods & GFMOD_CUMULATIVESCORE ) )
		ShowHighScores();

	std::cout << "\n\n";
	if ( ( ~mods & GFMOD_ALLCPU && ( ( ~mods & GFMOD_CUMULATIVESCORE ) || ( ( !restart ) && ( mods & GFMOD_CUMULATIVESCORE ) ) ) ) )
		system( "pause" );
	System::Console::Clear();


	for ( int i = 0; i < MAX_PLAYERS; i++ )
	{
		table[ i ].Clear();
	}
	return restart;
}

void Game::NextPlayer( void )
{
	m_currPlayer++;
	if ( m_currPlayer >= m_numPlayers )
		m_currPlayer = 0;
}

int Game::AskTarget( void ) const
{
	if ( ( mods & GFMOD_SHOWCPUASK ) || ( m_currPlayer == 0 && ( ~mods & GFMOD_ALLCPU ) ) )
	{
		std::cout << "Who do you want to ask?\n";
		for ( int i = 0; i < m_numPlayers; i++ )
		{
			if ( i == m_currPlayer )
				continue;
			std::cout << i << ": " << m_players[ i ]->GetName() << '\n';
		}
	}

	return m_players[ m_currPlayer ]->AskTarget( m_numPlayers, m_currPlayer );
}

bool Game::GoFish( void )
{
	Card card;
	m_Deck.Draw( card );

	if ( m_players[ m_currPlayer ]->AddCard( card ) )
		return true;

	m_Deck.Restore( card );

	return false;
}

void Game::DisplayScore( void )
{
	System::Console::ResetColor();
	System::Console::ForegroundColor( System::Green );
	std::cout << "Cards in Deck: " << m_Deck.Size() << "  ";
	if ( mods & GFMOD_SHOWDECK )
		ShowDeck();
	std::cout << "\n\n";

	for ( int i = 0; i < m_numPlayers; i++ )
	{
		if ( i == m_currPlayer )
		{
			System::Console::ForegroundColor( CURR_PLAYER_COL );
			std::cout << " --> ";
		}
		else
		{
			System::Console::ForegroundColor( PLAYER_COL );
			std::cout << "     ";
		}
		std::cout << m_players[ i ]->GetName() << " ";
		System::Console::ForegroundColor( System::Magenta );
		std::cout << "Score:" << score[ i ] << '\n';
		System::Console::ResetColor();
		if ( table[ i ].GetCurrSize() != 0 )
		{
			std::cout << "Pairs: ";
			Stack<Card> tempStack;
			Card tempCard;
			while ( table[ i ].Pop( tempCard ) )
			{
				tempStack.Push( tempCard );
			}
			while ( tempStack.Pop( tempCard ) )
			{
				tempCard.Show();
				std::cout << '+';
				table[ i ].Push( tempCard );

				tempStack.Pop( tempCard );
				tempCard.Show();
				std::cout << "  ";
				table[ i ].Push( tempCard );
			}
			std::cout << "\n\n";
		}
		else
		{
			std::cout << "Pairs: NONE\n\n";
		}
	}

	std::cout << "\n";
}

void Game::ClearAllPairs( void )
{
	Card card1, card2;
	for ( int i = 0; i < m_numPlayers; i++ )
	{
		for ( int j = 0; j < m_players[ i ]->GetNumCards() - 1; j++ )
		{
			for ( int k = j + 1; k < m_players[ i ]->GetNumCards(); k++ )
			{
				m_players[ i ]->GetCard( j, card1 );
				m_players[ i ]->GetCard( k, card2 );
				if ( card1.GetFace() == card2.GetFace() )
				{
					m_players[ i ]->Discard( k, card2 );
					m_players[ i ]->Discard( j, card1 );
					j--;
					k -= 2;
					table[ i ].Push( card1 );
					table[ i ].Push( card2 );
					score[ i ]++;

					if ( i == m_currPlayer )
						System::Console::ForegroundColor( CURR_PLAYER_COL );
					else
						System::Console::ForegroundColor( PLAYER_COL );
					std::cout << m_players[ i ]->GetName();
					System::Console::ForegroundColor( System::Magenta );
					std::cout << " found a pair in their hand: ";
					card1.Show(); std::cout << '+'; card2.Show();
					std::cout << '\n';
				}
			}
		}
	}
}

bool Game::CheckEmptyHand( void )
{
	bool stillInGame = false;
	for ( int i = 0; i < m_numPlayers; i++ )
	{
		if ( m_players[ i ]->GetNumCards() > 0 )
		{
			stillInGame = true;
			break;
		}
	}

	if ( !stillInGame )
	{
		m_state = GAME_END;
		return true;
	}

	for ( int i = 0; i < m_numPlayers; i++ )
	{
		bool is = true; // wtf is this?
		if ( m_currPlayer + i >= m_numPlayers )
			is = m_players[ m_currPlayer + i - m_numPlayers ]->GetNumCards() <= 0 && !m_Deck.IsEmpty();
		else
			is = m_players[ m_currPlayer + i ]->GetNumCards() <= 0 && !m_Deck.IsEmpty();
		if ( is )
		{
			Card temp;
			for ( int o = 0; o < 7; o++ )
			{
				if ( m_Deck.Draw( temp ) )
					if ( !m_players[ m_currPlayer ]->AddCard( temp ) )
					{
						m_Deck.Restore( temp );
					}
			}
		}
	}

	if ( m_players[ m_currPlayer ]->GetNumCards() <= 0 && m_Deck.IsEmpty() )
	{
		NextPlayer();
		return true;
	}

	return false;
}

void Game::DisplayTable( void )
{
	CheckEmptyHand();

	Sleep( 5 );
	System::Console::Lock( true );
	Sleep( 5 );
	System::Console::Clear();

	if ( mods & GFMOD_DISPLAYMODS )
		DisplayMods();

	DisplayScore();
	ClearAllPairs();
	CheckEmptyHand();
	std::cout << "\n\n";

	for ( int o = 0; o < m_numPlayers - 1; o++ )
	{
		NextPlayer();
		System::Console::ForegroundColor( PLAYER_COL );
		std::cout << m_players[ m_currPlayer ]->GetName() << ": ";
		for ( int i = 0; i < m_players[ m_currPlayer ]->GetNumCards(); i++ )
		{
			if ( mods & GFMOD_SHOWALLCARDS )
			{
				Card card;
				m_players[ m_currPlayer ]->GetCard( i, card );
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
			if ( i != m_players[ m_currPlayer ]->GetNumCards() - 1 )
				std::cout << ' ';
		}
		std::cout << "\n\n";
	}

	NextPlayer();
	std::cout << '\n';
	System::Console::ForegroundColor( CURR_PLAYER_COL );
	m_players[ m_currPlayer ]->Show();
	System::Console::ResetColor();
	std::cout << "\n\n";
	Sleep( 5 );
	System::Console::Lock( false );
	Sleep( 5 );
}

void Game::SetMods( void )
{
	//=========== <MODS> ===========//
	mods = GFMOD_NODELAYCPUASK | GFMOD_VOCALOIDNAMES | GFMOD_DISPLAYMODS;

	autoRuns = 12;
	autoRunPlayers = 4;
	//=========== ^MODS^ ===========//

	if ( mods & GFMOD_MAXAUTO ) mods |= GFMOD_AUTORUN;
	autoRuns = ( ( mods & GFMOD_MAXAUTO ) ? INT_MAX : autoRuns );
	if ( ( mods & GFMOD_AUTORUN ) && autoRuns <= 0 ) autoRuns = 1;
	if ( ~mods & GFMOD_AUTORUN ) autoRuns = 0;
	if ( autoRuns == 0 ) autoRunPlayers = 0;
	if ( autoRuns > 0 ) mods |= GFMOD_ALLCPU;
	if ( mods & GFMOD_ALLCPU )
	{
		mods |= GFMOD_NODELAYCPUASK;
		mods &= ~GFMOD_SHOWCPUASK;
	}
}

void Game::DisplayMods( void ) const
{
	System::Console::ForegroundColor( System::DarkGray );
	std::cout << "Active Mods: ";
	System::Console::ForegroundColor( System::DarkGreen );
	if ( mods & GFMOD_DISPLAYMODS ) std::cout << "/displayMods/";
	System::Console::ForegroundColor( System::Red );
	if ( mods & GFMOD_AUTORUN ) std::cout << "/autoRun/";
	if ( mods & GFMOD_MAXAUTO ) std::cout << "/maxAuto/";
	if ( autoRuns != 0 && ( ~mods & GFMOD_MAXAUTO ) ) std::cout << "/autoRuns=" << autoRuns << "/";
	if ( autoRunPlayers ) std::cout << "/autoRunPlayers=" << autoRunPlayers << "/";
	System::Console::ForegroundColor( System::Green );
	if ( mods & GFMOD_CUMULATIVESCORE ) std::cout << "/cumulativeScore/";
	System::Console::ForegroundColor( System::Red );
	if ( mods & GFMOD_ALLCPU ) std::cout << "/AllCPU/";
	System::Console::ForegroundColor( System::Green );
	if ( mods & GFMOD_SHOWCPUASK ) std::cout << "/ShowCPUAsk/";
	if ( mods & GFMOD_NODELAYCPUASK ) std::cout << "/NoDelayCPUAsk/";
	if ( mods & GFMOD_VOCALOIDNAMES ) std::cout << "/vocaloidNames/";

	std::cout << "\n             ";

	if ( mods & GFMOD_SHOWALLCARDS )
	{
		System::Console::ForegroundColor( System::White );
		std::cout << "/<";
		System::Console::ForegroundColor( System::Cyan );
		std::cout << "CHEAT";
		System::Console::ForegroundColor( System::White );
		std::cout << ":";
		System::Console::ForegroundColor( System::Cyan );
		std::cout << "ShowAllCards";
		System::Console::ForegroundColor( System::White );
		std::cout << ">/";
	}
	if ( mods & GFMOD_SHOWDECK )
	{
		System::Console::ForegroundColor( System::White );
		std::cout << "/<";
		System::Console::ForegroundColor( System::Cyan );
		std::cout << "CHEAT";
		System::Console::ForegroundColor( System::White );
		std::cout << ":";
		System::Console::ForegroundColor( System::Cyan );
		std::cout << "ShowDeck";
		System::Console::ForegroundColor( System::White );
		std::cout << ">/";
	}
	if ( mods & GFMOD_SKIPCPU )
	{
		System::Console::ForegroundColor( System::White );
		std::cout << "/<";
		System::Console::ForegroundColor( System::Cyan );
		std::cout << "CHEAT";
		System::Console::ForegroundColor( System::White );
		std::cout << ":";
		System::Console::ForegroundColor( System::Cyan );
		std::cout << "SkipCPU";
		System::Console::ForegroundColor( System::White );
		std::cout << ">/";
	}

	System::Console::ForegroundColor( System::Yellow );
	std::cout << "/randSeed=" << randSeed << "/";
	std::cout << "/gameRuns=" << gameRuns << "/";
	std::cout << std::endl;
	System::Console::ResetColor();
}

void Game::SetConsole( void )
{
	System::Console::CursorVisible( false );
	System::Console::EOLWrap( false );
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos( consoleWindow, 0, 56, 16, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
	System::Console::SetWindowSize( 176, 46 );
	System::Console::SetBufferSize( System::Console::WindowWidth(), System::Console::WindowHeight() );
}

// TODO : Fix Cumulative High Scores

char* Game::GetScoresFileName( void ) const
{
	switch ( m_numPlayers )
	{
		case 2:
			return ( ( mods & GFMOD_CUMULATIVESCORE ) ? "scores2P_c.bin" : "scores2P.bin" );
			break;
		case 3:
			return ( ( mods & GFMOD_CUMULATIVESCORE ) ? "scores3P_c.bin" : "scores3P.bin" );
			break;
		case 4:
			return ( ( mods & GFMOD_CUMULATIVESCORE ) ? "scores4P_c.bin" : "scores4P.bin" );
			break;
		default:
			return "scores.bin";
			break;
	}
}

void Game::ScoresToBin( void ) const
{
	bool doBlob = false;
	if ( ( mods & GFMOD_ALLCPU ) && !doBlob ) return;

	std::fstream bout;
	bout.open( GetScoresFileName(), std::ios_base::out | std::ios_base::app | std::ios_base::binary );
	if ( bout.is_open() )
	{
		char name[ NAME_MAX_LENGTH ];
		strcpy_s( name, NAME_MAX_LENGTH, m_players[ 0 ]->GetName() );

		if ( ( mods & GFMOD_ALLCPU ) && doBlob )
			strcpy_s( name, NAME_MAX_LENGTH, System::Console::RandomName() );

		bout.write( ( char* )( &( name ) ), NAME_MAX_LENGTH );
		bout.write( ( char* )( &( score[ 0 ] ) ), sizeof( int ) );

		bout.close();
	}
}

scoreData* Game::ReadScores( int& _size ) const
{
	std::fstream bin;
	bin.open( GetScoresFileName(), std::ios_base::in | std::ios_base::binary );
	if ( bin.is_open() )
	{
		bin.seekg( 0, std::ios_base::end );
		_size = ( int )bin.tellg() / ( sizeof( scoreData ) );

		if ( _size > 0 )
		{
			scoreData* sd = new scoreData[ _size ];
			bin.seekg( 0, std::ios_base::beg );

			for ( int i = 0; i < _size; i++ )
			{
				bin.read( ( char* )( &( sd[ i ] ) ), sizeof( scoreData ) );
			}

			bin.close();
			return sd;
		}
		bin.close();
	}
	else
		_size = -1;

	scoreData* sd = new scoreData[ 1 ];
	char xName[ NAME_MAX_LENGTH ] = "NO_DATA";
	strcpy_s( sd[ 0 ].sdName, NAME_MAX_LENGTH, xName );
	sd[ 0 ].sdScore = -1;

	return sd;
}

void Game::UpdateScoresFile( int _maxScores ) const
{
	int sdSize = -1;
	scoreData* sd = ReadScores( sdSize );

	if ( sdSize > 0 )
	{
		std::fstream bout;
		bout.open( GetScoresFileName(), std::ios_base::out | std::ios_base::trunc | std::ios_base::binary );
		if ( bout.is_open() )
		{
			SortScores( sd, sdSize );

			if ( sdSize > _maxScores ) sdSize = _maxScores;
			bout.write( ( char* )( &( sd[ 0 ] ) ), sizeof( scoreData ) * sdSize );

			bout.close();
		}
	}

	delete[ ] sd;

	ScoreBinText( _maxScores );
}

void Game::SortScores( scoreData* _sd, int _sdSize ) const
{
	for ( int i = 0; i < _sdSize - 1; ++i )
	{
		for ( int j = i + 1; j < _sdSize; ++j )
		{
			if ( _sd[ i ].sdScore < _sd[ j ].sdScore )
			{
				char tempN[ NAME_MAX_LENGTH ];
				strcpy_s( tempN, NAME_MAX_LENGTH, _sd[ i ].sdName );
				strcpy_s( _sd[ i ].sdName, NAME_MAX_LENGTH, _sd[ j ].sdName );
				strcpy_s( _sd[ j ].sdName, NAME_MAX_LENGTH, tempN );
				int tempS = _sd[ i ].sdScore;
				_sd[ i ].sdScore = _sd[ j ].sdScore;
				_sd[ j ].sdScore = tempS;
			}
		}
	}
}

int Game::GetWinnerScore( void ) const
{
	int winnerScore = 0;
	for ( int i = 0; i < m_numPlayers; i++ )
	{
		if ( score[ i ] > winnerScore )
			winnerScore = score[ i ];
	}
	return winnerScore;
}

void Game::ShowHighScores( void ) const
{
	ScoresToBin();
	UpdateScoresFile();
	int sdSize = -1;
	scoreData* sd = ReadScores( sdSize );
	System::Console::ForegroundColor( System::Yellow );
	std::cout << "\nHigh Scores (" << m_numPlayers << "-player, " << ( ( mods & GFMOD_CUMULATIVESCORE ) ? "" : "non-" ) << "cumulative score):\n";
	if ( sdSize > 0 )
	{
		for ( int i = 0; i < NUM_HIGH_SCORES; i++ )
		{
			if ( i < 9 )
				std::cout << '0';
			std::cout << i + 1 << ": ";
			if ( i < sdSize )
			{
				std::cout << sd[ i ].sdName << " - " << sd[ i ].sdScore << std::endl;
			}
			else
			{
				std::cout << "No Smith - 999" << std::endl;
			}
		}
	}
	else
	{
		System::Console::ForegroundColor( System::Red );
		std::cout << "Can't Access High Scores" << std::endl;
	}
	System::Console::ResetColor();
	delete[ ] sd;
}

void Game::ResetScores( void )
{
	System::Console::ForegroundColor( System::Yellow );
	System::Console::BackgroundColor( System::DarkRed );
	System::Console::Clear();

	System::Console::SetCursorPosition( 10, 8 );
	std::cout << "Are you sure you want to clear all high scores? (y/n)";
	System::Console::FlushKeys();
	for ( ;; )
	{
		if ( GetAsyncKeyState( 'Y' ) )
		{
			System::Console::Clear();
			GFMkeyPressed = true;
			while ( GFMkeyPressed )
			{
				if ( !GetAsyncKeyState( 'Y' ) )
					GFMkeyPressed = false;
			}

			System::Console::FlushKeys();
			Sleep( 500 );
			System::Console::SetCursorPosition( 10, 8 );
			std::cout << "Are you REALLY sure you want to clear ALL high scores? (y/n)";
			System::Console::FlushKeys();
			for ( ;; )
			{
				if ( GetAsyncKeyState( 'Y' ) )
				{
					break;
				}
				else if ( GetAsyncKeyState( 'N' ) || GetAsyncKeyState( VK_ESCAPE ) )
				{
					m_state = MENU_LOOP;
					System::Console::FlushKeys();
					System::Console::ResetColor();
					return;
				}
			}
			System::Console::FlushKeys();
			// CLEAR //
			{
				std::ofstream sc;
				char* filnam[ 7 ] = { "scores2P.bin", "scores2P_c.bin", "scores3P.bin", "scores3P_c.bin", "scores4P.bin", "scores4P_c.bin", "High Scores.txt" };
				System::Console::Clear();
				for ( int i = 0; i < 7; i++ )
				{
					System::Console::ForegroundColor( System::DarkYellow );
					Sleep( 6 );
					std::cout << ( ( i == 6 ) ? "Updating" : "Making empty" ) << " file: \"" << filnam[ i ] << "\"...";
					if ( i != 6 )
						sc.open( filnam[ i ], std::ios_base::trunc | std::ios_base::out | std::ios_base::binary );
					Sleep( 10 );

					if ( i == 6 && ScoreBinText( NUM_HIGH_SCORES ) )
					{
						Sleep( 150 );
						System::Console::BackgroundColor( System::DarkRed );
						System::Console::ForegroundColor( System::DarkGreen );
						std::cout << " DONE";
					}
					else if ( sc.is_open() )
					{
						sc.close();
						System::Console::ForegroundColor( System::DarkGreen );
						std::cout << " DONE";
					}
					else
					{
						Sleep( 250 );
						System::Console::ForegroundColor( System::Red );
						std::cout << " ERROR";
					}
					std::cout << '\n';
				}
				std::cout << std::endl;
				System::Console::ForegroundColor( System::White );
				Sleep( 16 );
				system( "pause" );
				System::Console::FlushKeys();
				GFMkeyPressed = true;
			}
			// ----- //
			System::Console::FlushKeys();
			m_state = GFMAIN_MENU;
			break;
		}
		else if ( GetAsyncKeyState( 'N' ) || GetAsyncKeyState( VK_ESCAPE ) )
		{
			System::Console::FlushKeys();
			m_state = MENU_LOOP;
			break;
		}
	}

	System::Console::ResetColor();
}

GAMESTATE Game::ShowInstructions( void ) const
{
	short keyPress = BaseMenu::Input();

	switch ( keyPress )
	{
		case 1:
		case 3: // prev
			gfhowtopage <= 0 ? gfhowtopage = 8 : gfhowtopage--;
			break;
		case 2:
		case 4: // next
			gfhowtopage >= 8 ? gfhowtopage = 0 : gfhowtopage++;
			break;
		case 6: // esc
			gfhowtopage = 0;
			return MENU_LOOP;
			break;
		default:
			break;
	}

	Sleep( 5 );
	System::Console::Lock( true );
	Sleep( 5 );
	System::Console::BackgroundColor( System::DarkCyan );
	System::Console::ForegroundColor( System::DarkMagenta );
	System::Console::Clear();
	System::Console::DrawBox( System::Console::WindowWidth() / 2 - 25, System::Console::WindowHeight() / 2 - 5, 50, 10, true );

	System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 5, System::Console::WindowHeight() / 2 - 10 );
	System::Console::ForegroundColor( System::Cyan );
	std::cout << "How to Play";
	System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 7, System::Console::WindowHeight() / 2 - 9 );
	System::Console::ForegroundColor( System::Green );
	std::cout << "GO FISH DELUXE";
	System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 27, System::Console::WindowHeight() / 2 - 7 );
	System::Console::ForegroundColor( System::Cyan );
	std::cout << "Source: http://www.pagat.com/invented/gofish_vars.html";

	//      System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23 + 0, System::Console::WindowHeight() / 2 - 4 + 0 );   //
	//      std::cout << "                                             ";                                                                     //

	System::Console::ForegroundColor( System::DarkRed );
	switch ( gfhowtopage )
	{
		case 0:
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 20, System::Console::WindowHeight() / 2 - 2 );
			std::cout << "Play with a standard 52-card deck. Every";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 20, System::Console::WindowHeight() / 2 - 1 );
			std::cout << "player starts with 7 cards. Any pairs in";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 22, System::Console::WindowHeight() / 2 );
			std::cout << "players' hands are put face up on the table";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 6, System::Console::WindowHeight() / 2 + 1 );
			std::cout << "immediately.";
			break;
		case 1:
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 22, System::Console::WindowHeight() / 2 - 4 );
			std::cout << "Play like standard Go-Fish except that pairs";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 - 3 );
			std::cout << "(not sets of 4) count. Any pairs you form are";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 22, System::Console::WindowHeight() / 2 - 2 );
			std::cout << "placed face up on the table, not face down -";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 22, System::Console::WindowHeight() / 2 - 1 );
			std::cout << "which is the usual rule for Go Fish. If you";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 );
			std::cout << "ask for a card of a particular rank, you must";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 22, System::Console::WindowHeight() / 2 + 1 );
			std::cout << "hold a card of that rank. If your request is";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 20, System::Console::WindowHeight() / 2 + 2 );
			std::cout << "successful, you must put the pair on the";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 3, System::Console::WindowHeight() / 2 + 3 );
			std::cout << "table.";
			break;
		case 2:
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 - 2 );
			std::cout << "If your request is not successful but you draw";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 21, System::Console::WindowHeight() / 2 - 1 );
			std::cout << "a card of the same rank you had asked for,";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 );
			std::cout << "your turn continues. You must put the pair on";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 5, System::Console::WindowHeight() / 2 + 1 );
			std::cout << "the table.";
			break;
		case 3:
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 - 3 );
			std::cout << "If your request is not successful but you draw";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 22, System::Console::WindowHeight() / 2 - 2 );
			std::cout << "a card of a rank different from the rank you";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 21, System::Console::WindowHeight() / 2 - 1 );
			std::cout << "had asked for, your turn ends. If the card";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 );
			std::cout << "drawn creates a pair, you must put the pair on";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 5, System::Console::WindowHeight() / 2 + 1 );
			std::cout << "the table.";
			break;
		case 4:
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 22, System::Console::WindowHeight() / 2 - 4 );
			std::cout << "If you run out of cards before the game ends";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 - 3 );
			std::cout << "(which will happen if you pair your last card";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 20, System::Console::WindowHeight() / 2 - 2 );
			std::cout << "by asking for it or drawing it from the";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 21, System::Console::WindowHeight() / 2 - 1 );
			std::cout << "stock), you draw 7 from the stock (or the";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 );
			std::cout << "remainder of the stock if there are 7 or fewer";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 + 1 );
			std::cout << "cards in it) to replenish your hand. Your turn";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 8, System::Console::WindowHeight() / 2 + 2 );
			std::cout << "then continues.";
			break;
		case 5:
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 - 3 );
			std::cout << "If it is not your turn to ask and you run out";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 22, System::Console::WindowHeight() / 2 - 2 );
			std::cout << "of cards (which will happen if a player asks";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 - 1 );
			std::cout << "for your last card), draw 7 from the stock (or";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 22, System::Console::WindowHeight() / 2 );
			std::cout << "the remainder of the stock if there are 7 or";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 21, System::Console::WindowHeight() / 2 + 1 );
			std::cout << "fewer cards in it) to replenish your hand.";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 18, System::Console::WindowHeight() / 2 + 2 );
			std::cout << "That other player's turn continues.";
			break;
		case 6:
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 21, System::Console::WindowHeight() / 2 - 4 );
			std::cout << "If the stock runs out, the game continues";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 - 3 );
			std::cout << "until all the cards have been paired. If your";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 21, System::Console::WindowHeight() / 2 - 2 );
			std::cout << "request for a card is not successful, your";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 22, System::Console::WindowHeight() / 2 - 1 );
			std::cout << "turn ends and the next player's turn begins.";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 );
			std::cout << "If you run out of cards when the stock is gone";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 23, System::Console::WindowHeight() / 2 + 1 );
			std::cout << "(whether it is your turn to ask or not), then";
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 20, System::Console::WindowHeight() / 2 + 2 );
			std::cout << "you cannot play any longer in the hand.";
			break;
		case 7:
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 14, System::Console::WindowHeight() / 2 - 1 );
			std::cout << "All pairs are 1 point each.";
			break;
		case 8:
			System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 19, System::Console::WindowHeight() / 2 - 1 );
			std::cout << "The player with the most points wins.";
			break;
		default:
			break;
	}

	System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 25, System::Console::WindowHeight() / 2 + 6 );
	System::Console::ForegroundColor( System::Cyan );
	std::cout << "<< PREV <<";

	System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 4, System::Console::WindowHeight() / 2 + 6 );
	System::Console::ForegroundColor( System::DarkBlue );
	std::cout << "Page ";
	System::Console::ForegroundColor( System::Blue );
	std::cout << gfhowtopage + 1;
	System::Console::ForegroundColor( System::DarkBlue );
	std::cout << "/9";

	System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 + 15, System::Console::WindowHeight() / 2 + 6 );
	System::Console::ForegroundColor( System::Cyan );
	std::cout << ">> NEXT >>";

	System::Console::BackgroundColor( System::DarkGray );
	System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 21, System::Console::WindowHeight() / 2 + 10 );
	std::cout << "                                           ";
	System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 21, System::Console::WindowHeight() / 2 + 11 );
	System::Console::ForegroundColor( System::White );
	std::cout << " Press";
	System::Console::ForegroundColor( System::Black );
	std::cout << " ESC ";
	System::Console::ForegroundColor( System::White );
	std::cout << "key to go back to the Main Menu ";
	System::Console::SetCursorPosition( System::Console::WindowWidth() / 2 - 21, System::Console::WindowHeight() / 2 + 12 );
	std::cout << "                                           ";

	System::Console::ResetColor();
	Sleep( 5 );
	System::Console::Lock( false );
	Sleep( 5 );

	return GF_HOWTO;
}

void Game::ShowDeck( void )
{
	Card cards[ 10 ];
	int numCards = 0;

	for ( int i = 0; i < 10; i++ )
	{
		if ( m_Deck.Draw( cards[ i ] ) )
			numCards++;
	}

	if ( numCards > 0 )
	{
		System::Console::ForegroundColor( System::Green );
		std::cout << "->  Next Card in Deck: ";
		cards[ 0 ].Show();
		std::cout << "   ";
	}

	for ( int i = 1; i < numCards; i++ )
	{
		cards[ i ].Show();
		std::cout << ' ';
	}

	for ( int i = numCards - 1; i >= 0; i-- )
	{
		m_Deck.Restore( cards[ i ] );
	}
}

bool Game::ScoreBinText( int _maxScores ) const
{
	std::ofstream highscores;
	highscores.open( "High Scores.txt", std::ios_base::trunc | std::ios_base::out );
	if ( highscores.is_open() )
	{
		char* filnam[ 6 ] = { "scores2P.bin", "scores2P_c.bin", "scores3P.bin", "scores3P_c.bin", "scores4P.bin", "scores4P_c.bin" };
		for ( int o = 0; o < 6; o++ )
		{
			int sdSize = -1;
			scoreData* sd = nullptr;
			std::ifstream bin;
			bin.open( filnam[ o ], std::ios_base::in | std::ios_base::binary );
			if ( bin.is_open() )
			{
				bin.seekg( 0, std::ios_base::end );
				sdSize = ( int )bin.tellg() / ( sizeof( scoreData ) );

				if ( sdSize > 0 )
				{
					sd = new scoreData[ sdSize ];
					bin.seekg( 0, std::ios_base::beg );

					for ( int i = 0; i < sdSize; i++ )
					{
						bin.read( ( char* )( &( sd[ i ] ) ), sizeof( scoreData ) );
					}

					bin.close();
				}
				else
				{
					bin.close();
					sd = new scoreData[ 1 ];
					char xName[ NAME_MAX_LENGTH ] = "NO_DATA";
					strcpy_s( sd[ 0 ].sdName, NAME_MAX_LENGTH, xName );
					sd[ 0 ].sdScore = -1;
				}
			}
			else
			{
				sdSize = -1;
				sd = new scoreData[ 1 ];
				char xName[ NAME_MAX_LENGTH ] = "NO_DATA";
				strcpy_s( sd[ 0 ].sdName, NAME_MAX_LENGTH, xName );
				sd[ 0 ].sdScore = -1;
			}
			System::Console::ForegroundColor( System::Yellow );
			highscores << "\nHigh Scores (" << o / 2 + 2 << "-player, " << ( ( o % 2 == 1 ) ? "cu" : "non-cu" ) << "mulative score):\n";
			if ( sdSize > 0 )
			{
				for ( int i = 0; i < _maxScores; i++ )
				{
					if ( i < 9 )
						highscores << '0';
					highscores << i + 1 << ": ";
					if ( i < sdSize )
					{
						highscores << sd[ i ].sdName << " - " << sd[ i ].sdScore << std::endl;
					}
					else
					{
						highscores << "No Smith - 999" << std::endl;
					}
				}
			}
			else
			{
				System::Console::ForegroundColor( System::Red );
				highscores << "No High Score Data" << std::endl;
			}
			System::Console::ResetColor();
			delete[ ] sd;
			highscores << std::endl;
		}
		highscores.close();
		return true;
	}
	return false;
}

// ☻☺ トニー ☺☻ //