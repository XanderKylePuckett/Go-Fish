#pragma once
#include "Player.h"
#include "Deck.h"

#include "Human.h"
#include "Computer.h"

#include "MainMenu.h"
#include "CheatsMenu.h"

// Enum of gamestates, you can add and remove from this if you need additional ones
// (examples include: GAME_TITLE, GAME_MENU, GAME_OPTIONS, etc).

struct scoreData
{
	char sdName[ NAME_MAX_LENGTH ];
	int sdScore;
};

class Game
{
	private:

	// Necessary data members
	Player* m_players[ MAX_PLAYERS ];	// The players in the game
	Deck m_Deck;			// The deck of cards
	Stack <Card> table[ MAX_PLAYERS ];
	//Stack table[ PLAYERS ];
	int score[ MAX_PLAYERS ];
	int m_currPlayer;		// Keeps track of which index is currently taking their turn
	int m_numPlayers;		// The number of players playing in the game


	// If you're coding UNO, this data member is necessary as well
	/*
		bool m_reversed;			// Keeps track of the order of play
		*/

	// GAMESTATE object to store the game's current state.
	GAMESTATE m_state;

	// Add game data members as necessary
	//Player *human = m_players[ 0 ];
	//Player *computer = m_players[ 1 ];

	public:
	// Default ctor
	Game();

	// Dtor
	~Game();

	// The main function of the game, this loops until a certain gamestate is set.
	void Run();

	// Modifier for the gamestate data member.
	void SetState( GAMESTATE _state )
	{
		m_state = _state;
	}


	private:
	int AskNumPlayers( void );
	void Initialize( int );
	void StartIt( void );
	bool EndGame( void );
	void NextPlayer( void );
	int AskTarget( void ) const;
	void DisplayScore( void );
	void DisplayTable( void );
	void ClearAllPairs( void );
	bool CheckEmptyHand( void );
	bool GoFish( void );
	void SetMods( void );
	void DisplayMods( void ) const;
	void SetConsole( void );
	void ScoresToBin( void ) const;
	scoreData* ReadScores( int& ) const;
	void UpdateScoresFile( int _maxScores = NUM_HIGH_SCORES ) const;
	void SortScores( scoreData*, int ) const;
	char* GetScoresFileName( void ) const;
	int GetWinnerScore( void ) const;
	void ShowHighScores( void ) const;
	void ResetScores( void );
	GAMESTATE ShowInstructions( void ) const;
	void ShowDeck( void );
	bool ScoreBinText( int ) const;

	// Get the score for the game
	//	For Go Fish, this will take care of pairing
	//  For UNO, this will be used for end of round scoring.
	// int Score(Player* _player);
};

// ☻☺ トニー ☺☻ //