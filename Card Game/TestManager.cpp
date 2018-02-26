#include "TestManager.h"
#include "src\\UnitTest++.h"
#include <algorithm>
#include <fstream>

#define CYAN Console::ForegroundColor(Cyan);
#define RED  Console::ForegroundColor(Red);

#define TXT(txt)\
	Console::ForegroundColor(Cyan);\
	cout << '\t' << txt << '\n';\
	Console::ForegroundColor(Red);

//#if LAB1
#include "Card.h"
//#endif

//#if LAB2
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include <type_traits>
//#endif

//#if LAB3
#include "Deck.h"
//#endif

//#if LAB4
#include "Player.h"
//#endif

//#if LAB5
#if LAB5_STACK_TEMPLATE
#include "Stack.h"
#endif

#include "Player.h"
#include <string>

#if LAB7
#include "Player.h"
#include <type_traits>
#endif

#pragma region TestManager (ctor/dtor)
CTestManager::CTestManager( void )
{

}


CTestManager::~CTestManager( void )
{
}
#pragma endregion

#pragma region TestManager Lab 1 Methods
#if LAB1_CARD_CTOR
void CTestManager::Lab1CardConstructorNoParams()
{
	Card testCard;
#if GO_FISH
	TXT( "Defaults are 2 for the face and " << char( 3 ) << " (3) for the suit" )
		CHECK_EQUAL( 2, testCard.m_face );
	CHECK_EQUAL( 3, testCard.m_suit );
#elif UNO	
	TXT("Defaults are 0 for the face and B for the color\n")
		CHECK_EQUAL(0, testCard.m_face);
	CHECK_EQUAL('B', testCard.m_suit);
#endif
}

void CTestManager::Lab1CardConstructorOneParam()
{
#if GO_FISH
	int nFace = rand() % 13 + 2;
#elif UNO
	int nFace = rand()%15;

#endif

	TXT( "Calling Card(" << nFace << ")" )
		Card testCard( nFace );
	CHECK_EQUAL( nFace, testCard.m_face );
}

void CTestManager::Lab1CardConstructorTwoParams()
{
#if GO_FISH
	int nFace = rand() % 13 + 2, nSuit = rand() % 4 + 3;
	Card testCard( nFace, ( char )nSuit );


	TXT( "Calling Card(" << nFace << ", " << nSuit << ")" )
		CHECK_EQUAL( nFace, testCard.m_face );
	CHECK_EQUAL( nSuit, toupper( testCard.m_suit ) );
#elif UNO
	int nFace = rand()%15;
	char chColors[4] = { 'B', 'G', 'R', 'Y' };
	char chColor = chColors[rand()%4];
	Card testCard(nFace, chColor);

	TXT("Calling Card(" << nFace << ", \' << chColor << \')\n")
		CHECK_EQUAL(nFace, testCard.m_face);
	CHECK_EQUAL(chColor, toupper(testCard.m_suit));
#endif	
}
#endif

#if LAB1_CARD_GETFACE
void CTestManager::Lab1CardGetFace()
{
	Card testCard;

#if GO_FISH
	int nFace = rand() % 13 + 2;
#elif UNO
	int nFace = rand()%15;
#endif

	testCard.m_face = nFace;

	CHECK_EQUAL( nFace, testCard.GetFace() );
}
#endif

#if LAB1_CARD_GETSUIT
void CTestManager::Lab1CardGetSuit()
{
	Card testCard;

#if GO_FISH
	int nSuit = rand() % 4 + 3;
	testCard.m_suit = static_cast< char >( nSuit );
	CHECK_EQUAL( nSuit, static_cast< int >( testCard.GetSuit() ) );
#elif UNO
	char chColors[4] = { 'B', 'G', 'R', 'Y' };
	char chColor = chColors[rand()%4];
	testCard.m_suit = chColor;
	CHECK_EQUAL(chColor, testCard.GetSuit());
#endif

}
#endif

#if LAB1_CARD_SETFACE
void CTestManager::Lab1CardSetFace()
{
	Card testCard;
#if GO_FISH
	int nFace = rand() % 13 + 2;
#elif UNO
	int nFace = rand()%15;
#endif

	testCard.SetFace( nFace );
	CHECK_EQUAL( nFace, testCard.m_face );
}
#endif

#if LAB1_CARD_SETSUIT
void CTestManager::Lab1CardSetSuit()
{
	Card testCard;

#if GO_FISH
	int nSuit = rand() % 4 + 3;
	testCard.SetSuit( char( nSuit ) );

	CHECK_EQUAL( nSuit, static_cast< int >( testCard.m_suit ) );
#elif UNO
	char chColors[4] = { 'B', 'G', 'R', 'Y' };
	char chColor = chColors[rand()%4];
	testCard.SetSuit(chColor);

	CHECK_EQUAL(chColor, testCard.m_suit);
#endif
}
#endif

#if LAB1_CARD_REL_OP
void CTestManager::Lab1CardRelationalOps()
{
#if GO_FISH
	const Card testCard1( rand() % 14 + 2 ), testCard2( rand() % 14 + 2 );
#elif UNO
	const Card testCard1(rand()%15), testCard2(rand()%15);
#endif
	TXT( "Testing for face values only" )
		TXT( "Calling Card::operator>" )
		CHECK( ( testCard1 > testCard2 ) == ( testCard1.m_face > testCard2.m_face ) );
	TXT( "Calling Card::operator<" )
		CHECK( ( testCard1 < testCard2 ) == ( testCard1.m_face < testCard2.m_face ) );
	TXT( "Calling Card::operator>=" )
		CHECK( ( testCard1 >= testCard2 ) == ( testCard1.m_face >= testCard2.m_face ) );
	TXT( "Calling Card::operator<=" )
		CHECK( ( testCard1 <= testCard2 ) == ( testCard1.m_face <= testCard2.m_face ) );
	TXT( "Calling Card::operator!=" )
		CHECK( ( testCard1 != testCard2 ) == ( testCard1.m_face != testCard2.m_face ) );
	TXT( "Calling Card::operator==" )
		CHECK( ( testCard1 == testCard2 ) == ( testCard1.m_face == testCard2.m_face ) );
}
#endif

#if LAB1_CARD_SHOW
void CTestManager::Lab1CardShow()
{
	TXT( "Calling Card::Show() (non-automated test)" )
		Console::ForegroundColor( Yellow );

#if GO_FISH
	Card testCard( rand() % 4 + 11, rand() % 4 + 3 );
#elif UNO
	char chColors[4] = { 'B', 'G', 'R', 'Y' };
	char chColor = chColors[rand()%4];
	Card testCard(rand()%5+10, chColor);
#endif
	testCard.Show();
	cout << '\n';
	Console::ResetColor();
}
#endif

#if LAB1_CARD_INSERT_OP
void CTestManager::Lab1CardOverloadedInsertionOp()
{
	TXT( "Calling Card's operator<< (non-automated test)" )
		Console::ForegroundColor( Yellow );

#if GO_FISH
	Card testCard( rand() % 4 + 11, rand() % 4 + 3 );
#elif UNO
	char chColors[4] = { 'B', 'G', 'R', 'Y' };
	char chColor = chColors[rand()%4];
	Card testCard(rand()%5+10, chColor);
#endif
	cout << testCard << '\n';
	Console::ResetColor();
}
#endif

/*
void CTestManager::Lab1ConstTest()
{
Card card;

TXT("Checking for const on Card::GetFace")
CHECK(CardGetFace<Card>(card));
TXT("Checking for const on Card::GetSuit")
CHECK(CardGetSuit<Card>(card));
TXT("Checking for const on Card::Show")
CHECK(CardShow<Card>(card));

TXT("Check for const on operator<<")
// Reading the file
ifstream cardFile("card.h");
string line;
char szLine[256];
while(!cardFile.eof())
{
cardFile.getline(szLine, 256);
line = szLine;
// Looking for the correct line
if(line.find("friend ostream") != string::npos)
break;
}
cardFile.close();

int nNumSearches = 0;
size_t pos = 0;
while(pos != string::npos)
if(pos = line.find("const", pos+1))
nNumSearches++;

// Needs to be two because two "finds" are needed
// One to find the first const,
// and one to check the rest of the string to see
// if there are any other consts (there should only be one)
CHECK_EQUAL(nNumSearches, 2);
}
*/


#pragma endregion

#pragma region TestManager Lab 2 Methods

#if LAB2_PLAYER_CTOR
void CTestManager::Lab2PlayerConstructorNoParams()
{
	TXT( "Defaults are \"Player\" for the name and 7 for the maxCards" )
		Player player;

	CHECK_EQUAL( "Player", player.m_name );
	CHECK_EQUAL( 7, player.m_maxCards );
	CHECK_EQUAL( 0, player.m_numCards );
	CHECK_EQUAL( 0, player.m_score );
}
void CTestManager::Lab2PlayerConstructorOneParam()
{
	TXT( "Calling Player(\"One Param\")" );

	const char* szName = "One Param";
	Player player( szName );

	CHECK_EQUAL( "One Param", player.m_name );
	CHECK_EQUAL( 7, player.m_maxCards );
	CHECK_EQUAL( 0, player.m_numCards );
	CHECK_EQUAL( 0, player.m_score );

}
void CTestManager::Lab2PlayerConstructorTwoParams()
{
	TXT( "Calling Player(\"Two Params\", 3)" );

	const char* szName = "Two Params";
	Player player( szName, 3 );

	CHECK_EQUAL( "Two Params", player.m_name );
	CHECK_EQUAL( 3, player.m_maxCards );
	CHECK_EQUAL( 0, player.m_numCards );
	CHECK_EQUAL( 0, player.m_score );
}
#endif

#if LAB2_PLAYER_GETNAME
void CTestManager::Lab2PlayerGetName()
{
	Player player;
	strcpy_s( player.m_name, 32, "GetName" );

	CHECK_EQUAL( "GetName", player.m_name );
}
#endif

#if LAB2_PLAYER_GETCARD
void CTestManager::Lab2PlayerGetCard()
{
	TXT( "Populating hand with 5 random cards, and accessing each one." )
		Player player( "GetCard" );
	Card tempCards[ 5 ];
	Card playerHand[ 5 ];

	player.m_numCards = 5;
	for ( int i = 0; i < 5; ++i )
	{
		tempCards[ i ] = Card( rand() % 4 + 3, rand() % 12 + 2 );
		player.m_hand[ i ] = tempCards[ i ];
		// Testing each individual card
		player.GetCard( i, playerHand[ i ] );
		CHECK_EQUAL( tempCards[ i ], playerHand[ i ] );
	}

	TXT( "Testing to see if \"out of bounds\" returns false." )

		// Testing a card "not in hand" 
		player.m_numCards = 4;
	Card storedValue;
	CHECK_EQUAL( false, player.GetCard( 4, storedValue ) );
}
#endif

#if LAB2_PLAYER_GETSCORE
void CTestManager::Lab2PlayerGetScore()
{
	Player player( "GetScore" );
	player.m_score = 10;

	CHECK_EQUAL( 10, player.GetScore() );
}
#endif

#if LAB2_PLAYER_SETNAME
void CTestManager::Lab2PlayerSetName()
{
	Player player;
	const char* szName = "SetName";
	player.SetName( szName );

	CHECK_EQUAL( "SetName", player.m_name );
}
#endif

#if LAB2_PLAYER_ADDSCORE
void CTestManager::Lab2PlayerAddToScore()
{
	Player player;
	player.AddToScore( 3 );

	CHECK_EQUAL( 3, player.m_score );

	player.AddToScore( 1 );

	CHECK_EQUAL( 4, player.m_score );
}
#endif

#if LAB2_PLAYER_ADDCARD
void CTestManager::Lab2PlayerAddCard()
{
#if GO_FISH
	Card tempCard, hand[ 5 ] =
	{
		Card( rand() % 13 + 2, rand() % 4 + 3 ),
		Card( rand() % 13 + 2, rand() % 4 + 3 ),
		Card( rand() % 13 + 2, rand() % 4 + 3 ),
		Card( rand() % 13 + 2, rand() % 4 + 3 ),
		Card( rand() % 13 + 2, rand() % 4 + 3 ),
	};

#elif UNO
	char chColors[4] = { 'B', 'G', 'R', 'Y' };
	Card tempCard, hand[5] = 
	{
		Card(rand()%15, chColors[rand()%4]),
		Card(rand()%15, chColors[rand()%4]),
		Card(rand()%15, chColors[rand()%4]),
		Card(rand()%15, chColors[rand()%4]),
		Card(rand()%15, chColors[rand()%4]),
	};

#endif

	Player addCardPlayer;
	addCardPlayer.m_maxCards = 5;

	TXT( "Adding 5 random cards to the hand.  Ensuring that they go to the right index." )


		// Adding five cards
		for ( int i = 0; i < 5; ++i )
		{
			// Making sure that the number of cards is correct before the add
			CHECK_EQUAL( i, addCardPlayer.m_numCards );
			// Adding the card
			CHECK( addCardPlayer.AddCard( hand[ i ] ) );
			// Making sure that the number of cards is correct after
			CHECK_EQUAL( i + 1, addCardPlayer.m_numCards );
			// Making sure the card is actually in the array at the correct index
			CHECK_EQUAL( hand[ i ], addCardPlayer.m_hand[ i ] );
		}

	TXT( "Making sure adding any cards past MaxCards fails." )
		// Adding a sixth card (should return false)
		CHECK_EQUAL( false, addCardPlayer.AddCard( Card() ) );
}
#endif

#if LAB2_PLAYER_DISCARD
void CTestManager::Lab2PlayerDiscard()
{

#if GO_FISH

	Card tempCard, hand[ 5 ] =
	{
		Card( rand() % 13 + 2, rand() % 4 + 3 ),
		Card( rand() % 13 + 2, rand() % 4 + 3 ),
		Card( rand() % 13 + 2, rand() % 4 + 3 ),
		Card( rand() % 13 + 2, rand() % 4 + 3 ),
		Card( rand() % 13 + 2, rand() % 4 + 3 ),
	};
#elif UNO
	char chColors[4] = { 'B', 'G', 'R', 'Y' };
	Card tempCard, hand[5] = 
	{
		Card(rand()%15, chColors[rand()%4]),
		Card(rand()%15, chColors[rand()%4]),
		Card(rand()%15, chColors[rand()%4]),
		Card(rand()%15, chColors[rand()%4]),
		Card(rand()%15, chColors[rand()%4]),
	};
#endif

	Player discardPlayer;

	TXT( "Making sure you can't discard out of an empty hand" )
		// Making sure you can't discard out of an empty hand
		for ( int i = 0; i < 6; ++i )
			CHECK_EQUAL( false, discardPlayer.Discard( i, tempCard ) );

	TXT( "Populating hand with 5 random cards" )

		// Adding 5 cards (full hand)
		for ( int i = 0; i < 5; ++i )
			discardPlayer.m_hand[ i ] = hand[ i ];
	discardPlayer.m_numCards = 5;

	TXT( "Attempting to discard an out of bounds index" )

		CHECK_EQUAL( false, discardPlayer.Discard( 5, tempCard ) );

	TXT( "Discarding last card" )

		// Discarding last card
		CHECK( discardPlayer.Discard( 4, tempCard ) );
	CHECK_EQUAL( hand[ 4 ].m_face, tempCard.m_face );
	CHECK_EQUAL( hand[ 4 ].m_suit, tempCard.m_suit );

	for ( int i = 0; i < discardPlayer.m_numCards; ++i )
	{
		discardPlayer.GetCard( i, tempCard );
		CHECK_EQUAL( hand[ i ].m_face, discardPlayer.m_hand[ i ].m_face );
		CHECK_EQUAL( hand[ i ].m_suit, discardPlayer.m_hand[ i ].m_suit );
	}

	CHECK_EQUAL( 4, discardPlayer.m_numCards );

	TXT( "Discarding first card" )

		// Discarding first card
		CHECK( discardPlayer.Discard( 0, tempCard ) );
	for ( int i = 0; i < discardPlayer.m_numCards; ++i )
	{
		tempCard = discardPlayer.m_hand[ i ];
		CHECK_EQUAL( hand[ i + 1 ].m_face, tempCard.m_face );
		CHECK_EQUAL( hand[ i + 1 ].m_suit, tempCard.m_suit );
	}

	TXT( "Discarding second (middle) card" )

		// Discarding middle card
		CHECK( discardPlayer.Discard( 1, tempCard ) );
	tempCard = discardPlayer.m_hand[ 0 ];
	CHECK_EQUAL( hand[ 1 ].m_face, tempCard.m_face );
	CHECK_EQUAL( hand[ 1 ].m_suit, tempCard.m_suit );
	tempCard = discardPlayer.m_hand[ 1 ];
	CHECK_EQUAL( hand[ 3 ].m_face, tempCard.m_face );
	CHECK_EQUAL( hand[ 3 ].m_suit, tempCard.m_suit );

	TXT( "Attempting to discard an out of bounds index" )

		// Discarding 3rd card (only two cards in hand)
		CHECK_EQUAL( false, discardPlayer.Discard( 2, tempCard ) );
}
#endif

#if LAB2_PLAYER_CLEAR
void CTestManager::Lab2PlayerClear()
{
	Player clear;
	clear.m_numCards = 10;

	// "Clearing" the hand
	clear.Clear();

	CHECK_EQUAL( 0, clear.m_numCards );
}
#endif

#if LAB2_HUMAN_CTOR
void CTestManager::Lab2HumanConstructorNoParams()
{
	TXT( "Default for the name is \"Human\")" )

		// Creating a Human using upcasting
		Player* pUpcastingToHuman = new Human;

	// Making sure information was passed back
	CHECK_EQUAL( "Human", pUpcastingToHuman->m_name );
	CHECK_EQUAL( 7, pUpcastingToHuman->m_maxCards );
	CHECK_EQUAL( 0, pUpcastingToHuman->m_numCards );
	CHECK_EQUAL( 0, pUpcastingToHuman->m_score );

	delete pUpcastingToHuman;
}
void CTestManager::Lab2HumanConstructorOneParam()
{
	TXT( "Calling Human(\"Homo Sapien\")" )

		// Creating a Human using upcasting
		Player* pUpcastingToHuman = new Human( "Homo Sapien" );

	// Making sure information was passed back
	CHECK_EQUAL( "Homo Sapien", pUpcastingToHuman->m_name );
	CHECK_EQUAL( 7, pUpcastingToHuman->m_maxCards );
	CHECK_EQUAL( 0, pUpcastingToHuman->m_numCards );
	CHECK_EQUAL( 0, pUpcastingToHuman->m_score );

	delete pUpcastingToHuman;
}
#endif

#if LAB2_HUMAN_SHOW
void CTestManager::Lab2HumanShow()
{
	TXT( "Calling Human::Show() (non-automated test)" )

		Human human( "Human" );
#if GO_FISH
	for ( int i = 0; i < 3; ++i )
		human.m_hand[ i ] = Card( rand() % 13 + 2, rand() % 4 + 3 );
#elif UNO
	char chColors[4] = { 'B', 'G', 'R', 'Y' };
	for(int i = 0; i < 3; ++i)
		human.m_hand[i] = Card(rand()%15, chColors[rand()%4]);
#endif
	human.m_numCards = 3;

	human.Show();
	cout << '\n';
}
#endif

#if LAB2_CPU_CTOR
void CTestManager::Lab2ComputerConstructorNoParams()
{
	TXT( "Default for the name is \"Computer\")" )

		// Creating a Human using upcasting
		Player* pUpcastingToComputer = new Computer;

	// Making sure information was passed back
	CHECK_EQUAL( "Computer", pUpcastingToComputer->m_name );
	CHECK_EQUAL( 7, pUpcastingToComputer->m_maxCards );
	CHECK_EQUAL( 0, pUpcastingToComputer->m_numCards );
	CHECK_EQUAL( 0, pUpcastingToComputer->m_score );

	delete pUpcastingToComputer;
}
void CTestManager::Lab2ComputerConstructorOneParam()
{
	TXT( "Calling Computer(\"CPU\")" )

		// Creating a Human using upcasting
		Player* pUpcastingToComputer = new Computer( "CPU" );

	// Making sure information was passed back
	CHECK_EQUAL( "CPU", pUpcastingToComputer->m_name );
	CHECK_EQUAL( 7, pUpcastingToComputer->m_maxCards );
	CHECK_EQUAL( 0, pUpcastingToComputer->m_numCards );
	CHECK_EQUAL( 0, pUpcastingToComputer->m_score );

	delete pUpcastingToComputer;
}
#endif

#if LAB2_CPU_SHOW
void CTestManager::Lab2ComputerShow()
{
	TXT( "Calling Computer::Show() (non-automated test)" )

		Player* pComputer = new Computer;
	for ( int i = 0; i < 3; ++i )
		pComputer->m_hand[ i ] = Card( rand() % 12 + 2, rand() % 4 + 3 );
	pComputer->m_numCards = 3;

	pComputer->Show();
	cout << '\n';

	delete pComputer;
}
#endif

/*
void CTestManager::Lab2ConstTest()
{
Player player;
Human human;
Computer computer;

TXT("Checking for const on Player::GetNumCards")
CHECK(PlayerGetNumCards<Player>(player));
TXT("Checking for const on Player::GetMaxCards")
CHECK(PlayerGetMaxCards<Player>(player));
TXT("Checking for const on Player::GetScore")
CHECK(PlayerGetScore<Player>(player));
TXT("Checking for const on Player::GetName")
CHECK(PlayerGetName<Player>(player));
TXT("Checking for const on Player::GetCard")
CHECK(PlayerGetCard<Player>(player));
TXT("Checking for const on Player::Show")
CHECK(PlayerShow<Player>(player));

TXT("Checking for const on Human::Show")
CHECK(HumanShow<Human>(human));
TXT("Checking for const on Computer::Show")
CHECK(ComputerShow<Computer>(computer));
}
*/
#pragma endregion

#pragma region TestManager Lab 3 Methods

#if LAB3_DECK_INIT	
void CTestManager::Lab3DeckInitialize()
{

	Deck deck;
	deck.Initialize();

	// Getting the test values
	ifstream valfile;

#if GO_FISH
	TXT( "Verifying 52 unique cards" )

		Card refDeck[ 52 ];
	int nFace;
	char chSuit;

	// Read in the reference deck
	valfile.open( "GoFishDeck.txt" );
	for ( int i = 0; i < 52; ++i )
	{
		valfile >> nFace >> chSuit;
		refDeck[ i ] = Card( nFace, chSuit );
	}
	valfile.close();

	// Sort the decks
	Sort( refDeck );
	Sort( deck.m_cards );
	CHECK( !memcmp( refDeck, deck.m_cards, sizeof( Card ) * 52 ) );

#elif UNO
	TXT("Verifying correct UNO deck (108 cards)")

		Card refDeck[108];
	int nFace;
	char chColor;
	// Read in the reference deck
	valfile.open("UnoDeck.txt");
	for(int i = 0; i < 108; ++i)
	{
		valfile >> nFace >> chColor;
		refDeck[i] = Card(nFace, chColor);
	}
	valfile.close();

	// Sort the decks
	Sort(refDeck);
	Sort(deck.m_cards);	

	CHECK(!memcmp(refDeck, deck.m_cards, sizeof(Card)*108));
#endif

}
#endif

#if LAB3_DECK_SHUFFLE
void CTestManager::Lab3DeckShuffle()
{
	Deck baseDeck, shuffleDeck;
	int nNumSame = 0;

	baseDeck.Initialize();	// For safety
	shuffleDeck.Shuffle();

	TXT("Making sure no more than 20% of the deck is in its original position")

#if GO_FISH
		for(int i = 0; i < 52; ++i)
			if(baseDeck.m_cards[i].m_face  == shuffleDeck.m_cards[i].m_face &&
				baseDeck.m_cards[i].m_suit == shuffleDeck.m_cards[i].m_suit)
				++nNumSame;

	// No more than 20% of the deck
	CHECK(nNumSame <= 10);

#elif UNO
		for(int i = 0; i < 108; ++i)
			if(baseDeck.m_cards[i].m_face  == shuffleDeck.m_cards[i].m_face &&
				baseDeck.m_cards[i].m_suit == shuffleDeck.m_cards[i].m_suit)
				++nNumSame;

	// No more than 20% of the deck
	CHECK(nNumSame <= 21);

#endif

	TXT("Making sure the deck is still correct")
		Sort(baseDeck.m_cards);
	Sort(shuffleDeck.m_cards);

#if GO_FISH
	CHECK(!memcmp(baseDeck.m_cards, shuffleDeck.m_cards, sizeof(Card)*52));
#elif UNO
	CHECK(!memcmp(baseDeck.m_cards, shuffleDeck.m_cards, sizeof(Card)*108));
#endif

}
#endif

#if LAB3_DECK_DRAW
void CTestManager::Lab3DeckDraw()
{
	Deck deck;
	Card discard;
	deck.m_Stack.Push(deck.m_cards[0]);

	TXT("Pushing a card to the stack to see if Draw gets correct value (and returns true)")
		// Test to see if draw returns correct value (and true)
		CHECK(deck.Draw(discard));
	CHECK_EQUAL(deck.m_cards[0], discard);

	TXT("Checking to see if Draw returns false when the deck is empty")
		// Now deck should be empty, should return false
		CHECK(!deck.Draw(discard));
}
#endif

#if LAB3_DECK_CLEAR
void CTestManager::Lab3DeckClear()
{
	Deck deck;

	deck.Shuffle();

	TXT("Adding some cards to the stack and then clearing")
		CHECK(deck.m_Stack.GetCurrSize());

	deck.Clear();

	CHECK(!deck.m_Stack.GetCurrSize());
}
#endif

#if LAB3_DECK_ISEMPTY
void CTestManager::Lab3DeckIsEmpty()
{
	Deck deck;

	TXT("Testing for true on an empty deck")
		// Testing for empty (true)
		CHECK(deck.IsEmpty());

	deck.Shuffle();

	TXT("Testing for false on a non-empty deck")
		// Testing for empty (false)
		CHECK(!deck.IsEmpty());
}
#endif

/*
void CTestManager::Lab3ConstTest()
{
Deck deck;
TXT("Checking for const on Deck::IsEmpty")
CHECK(DeckIsEmpty<Deck>(deck));
}
*/

void CTestManager::Sort( Card* deck )
{

#if GO_FISH
	// First sort by suit
	std::sort( deck, deck + 52, SortBySuit );
	// H
	std::sort( deck, deck + 13, SortByFace );
	// D
	std::sort( deck + 13, deck + 26, SortByFace );
	// C
	std::sort( deck + 26, deck + 39, SortByFace );
	// S
	std::sort( deck + 39, deck + 52, SortByFace );
#elif UNO
	// First sort by suit
	sort(deck, deck+108, SortBySuit);
	// B
	sort(deck, deck+27, SortByFace);
	// G
	sort(deck+27, deck+54, SortByFace);
	// R
	sort(deck+54, deck+81, SortByFace);
	// Y
	sort(deck+81, deck+108, SortByFace);

#endif
}

bool CTestManager::SortBySuit( Card& cardA, Card& cardB )
{
	return cardA.m_suit < cardB.m_suit;
}

bool CTestManager::SortByFace( Card& cardA, Card& cardB )
{
	return cardA.m_face < cardB.m_face;
}
#pragma endregion

#pragma region TestManager Lab 4 Methods
#if LAB4_PLAYER_CTOR
void CTestManager::Lab4PlayerConstructor()
{
	int nNumCards = rand()%10+1;
	Player  player("Dynamic Memory", nNumCards);

	TXT("Checking to see if name and hand have been changed to pointers")
		// Testing to make sure data members are correct type
		CHECK_EQUAL("char *", typeid(player.m_name).name());
	CHECK_EQUAL("class Card *", typeid(player.m_hand).name());

	TXT("Testing for deep copy of name")
		//Testing to make sure params were copied over
		CHECK_EQUAL("Dynamic Memory", player.m_name);
	CHECK_EQUAL(nNumCards, player.m_maxCards);
}
#endif

#if LAB4_PLAYER_COPYCTOR
void CTestManager::Lab4PlayerCopyConstructor()
{
	TXT("Testing for deep copy of name and hand, shallow copies of everything else")
		int nNumCards = rand()%10+1;
	Player player("Copy ctor", nNumCards);
	player.m_numCards = nNumCards;
	Card* pHand = new Card[nNumCards];

#if GO_FISH
	for(int i = 0; i < nNumCards; ++i)
		player.m_hand[i] = pHand[i] = Card(rand()%4+3, rand()%12+2);

#elif UNO
	char chColors[4] = { 'B', 'G', 'R', 'Y' };
	for(int i = 0; i < nNumCards; ++i)
		player.m_hand[i] = pHand[i] = Card(rand()%15, chColors[rand()%4]);
#endif
	delete[] pHand;

	// Copy ctor
	Player copy = player;

	// Testing to make sure data members are correct type
	CHECK_EQUAL("char *", typeid(copy.m_name).name());
	CHECK_EQUAL("class Card *", typeid(copy.m_hand).name());

	// Checking the actual values
	CHECK_EQUAL("Copy ctor", copy.m_name);
	CHECK_EQUAL(player.m_numCards, copy.m_numCards);
	CHECK_EQUAL(player.m_maxCards, copy.m_maxCards);
	CHECK_EQUAL(player.m_numCards, copy.m_numCards);
	CHECK_EQUAL(player.m_score, copy.m_score);
	CHECK_ARRAY_EQUAL(player.m_hand, copy.m_hand, nNumCards);

	// Making sure deep copies are being made
	CHECK(player.m_name != copy.m_name);
	CHECK(player.m_hand != copy.m_hand);
}
#endif

#if LAB4_PLAYER_ASSIGNOP
void CTestManager::Lab4PlayerAssignmentOperator()
{
	TXT("Testing for deep copy of name and hand, shallow copies of everything else")

		int nNumCards = rand()%10+1;
	Player player("Copy ctor", nNumCards);
	player.m_numCards = nNumCards;
	Card* pHand = new Card[nNumCards];

#if GO_FISH
	for(int i = 0; i < nNumCards; ++i)
		player.m_hand[i] = pHand[i] = Card(rand()%4+3, rand()%12+2);

#elif UNO
	char chColors[4] = { 'B', 'G', 'R', 'Y' };
	for(int i = 0; i < nNumCards; ++i)
		player.m_hand[i] = pHand[i] = Card(rand()%15, chColors[rand()%4]);
#endif
	delete[] pHand;

	// Assignment operator
	Player copy;
	copy = player;

	// Testing to make sure data members are correct type
	CHECK_EQUAL("char *", typeid(copy.m_name).name());
	CHECK_EQUAL("class Card *", typeid(copy.m_hand).name());

	// Checking the actual values
	CHECK_EQUAL("Copy ctor", copy.m_name);
	CHECK_EQUAL(player.m_numCards, copy.m_numCards);
	CHECK_EQUAL(player.m_maxCards, copy.m_maxCards);
	CHECK_EQUAL(player.m_numCards, copy.m_numCards);
	CHECK_EQUAL(player.m_score, copy.m_score);
	CHECK_ARRAY_EQUAL(player.m_hand, copy.m_hand, nNumCards);

	// Making sure deep copies are being made
	CHECK(player.m_name != copy.m_name);
	CHECK(player.m_hand != copy.m_hand);

	TXT("Checking for ability to daisy-chain")
		// Checking for daisy-chaining
		Player daisy;
	daisy = copy = player;
	CHECK_EQUAL("Copy ctor", daisy.m_name);
	CHECK_EQUAL(player.m_numCards, daisy.m_numCards);
	CHECK_EQUAL(player.m_maxCards, daisy.m_maxCards);
	CHECK_EQUAL(player.m_numCards, daisy.m_numCards);
	CHECK_EQUAL(player.m_score, daisy.m_score);
	CHECK_ARRAY_EQUAL(player.m_hand, daisy.m_hand, nNumCards);

	TXT("Testing for self-assignment")
		// Testing for self-assignment
		copy = copy;
	CHECK_EQUAL("Copy ctor", copy.m_name);
	CHECK_EQUAL(player.m_numCards, copy.m_numCards);
	CHECK_EQUAL(player.m_maxCards, copy.m_maxCards);
	CHECK_EQUAL(player.m_numCards, copy.m_numCards);
	CHECK_EQUAL(player.m_score, copy.m_score);
	CHECK_ARRAY_EQUAL(player.m_hand, copy.m_hand, nNumCards);
}
#endif
#pragma endregion

#pragma region TestManager Lab 5 Methods

#if LAB5_STACK_TEMPLATE
void CTestManager::Lab5StackTemplate()
{
	TXT("Ensuring that the CStack class is templated")

		ifstream file("stack.h");
	char szLine[500];
	string strLine;
	int nFound = 0;
	while(!file.eof())
	{
		file.getline(szLine, 128);
		strLine = szLine;
		if((strLine.find("template") != string::npos && 
			strLine.find("typename") != string::npos) ||
			(strLine.find("template") != string::npos && 
			strLine.find("class") != string::npos))
			nFound++;
	}
	file.close();

	// Making sure we see the template header multiple times
	CHECK(nFound >= 6);
}
#endif

#if LAB5_CONSTDATAMEMBER
void CTestManager::Lab5ConstDataMember()
{
	TXT("Ensuring that Player::m_maxCards is a const data member")

		ifstream file("player.h");
	char szLine[128];
	string strLine;
	int nFound;
	while(!file.eof())
	{
		file.getline(szLine, 128);
		strLine = szLine;
		if(strLine.find("m_maxCards") != string::npos && 
			strLine.find("const int") != string::npos)
		{
			nFound = 1;
			break;
		}
	}
	file.close();

	CHECK(nFound == 1);
}
#endif

#pragma endregion

#pragma region TestManager Lab 7 Methods
#if LAB7_PLAYER_ABC
void CTestManager::Lab7PlayerIsABC()
{
	TXT("Ensuring that Player is an Abstract Base Class")

		CHECK(std::is_abstract<Player>::value);
}
#endif

#pragma endregion