// main.cpp : Entry point for the project

// This includes all of our standard headers
#include "src\\UnitTest++.h"
#include "src\\TestReporterStdout.h"

#include "stdafx.h"

#include "TestManager.h"

#include "Game.h"

/***********/
/* Globals */
/***********/

int numCPUs;
int gameRuns;
int autoRuns;
int autoRunPlayers;
unsigned int randSeed;
WORD mods;
bool GFMkeyPressed;
int gfhowtopage;

#if SOUND
int s_freq;
int s_dur;
#endif
bool runningGame;

/**************/
/* Prototypes */
/**************/
#if SOUND
void Sound( void );
#endif

// Our primary routine.  This is called when the program starts.
//
// Return:	We always return 0.
int main( int, const char** )
{
	// This will check for memory leaks.  They will show up in your
	// output window along with the line number.  Replace the 
	// -1 argument in the second call with the allocation number
	// and then trace back through the call stack to find the leak.
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetBreakAlloc( -1 );

	randSeed = unsigned int( time( nullptr ) );
	srand( randSeed );
	randSeed = rand();
	srand( randSeed );

	GFMkeyPressed = false;
	runningGame = true;
#if SOUND
	s_freq = 0;
	s_dur = 0;
	thread soundthread( Sound );
#endif

#if GAME
	Game game;
	game.Run();
#else
	UnitTest::RunAllTests();
#endif

	std::cout << "\n\n";

#if GAME
	System::Console::ResetColor();
#else
	system( "pause" );
#endif

	runningGame = false;
#if SOUND
	soundthread.join();
#endif

	return 0;
}

#if SOUND
void Sound()
{
	for ( ;; )
	{
		if ( !runningGame )
			break;
		if ( s_freq <= 0 || s_dur <= 0 )
			continue;

		Beep( ( DWORD )s_freq, ( DWORD )s_dur );

		s_freq = 0;
		s_dur = 0;
	}
}
#endif

// ☻☺ トニー ☺☻ //