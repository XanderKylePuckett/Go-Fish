#pragma once

#include "stdafx.h"

#define HEADER(text)\
	Console::ForegroundColor(White);\
	cout << text << '\n';\
	Console::ForegroundColor(Red);

#define FOOTER\
	Console::ResetColor();	

// Forward class declarations of essential components
class Card;
class Deck;
class Player;
class Human;
class Computer;

#pragma region Do not look at this
#define CONST_STRUCT(return, name)\
	template<typename U, return (U::*)() const> struct name {};

#define CONST_TEST(funcName, method, has, struct)\
	template<typename U> static char funcName(struct<U, &U::method>*);\
	template<typename U> static int funcName(...);\
	static const bool has = sizeof(funcName<T>(0)) == sizeof(char);

#define CONST_FUNC(func, check)\
	template<typename TMap>\
	bool func(const TMap& m)\
	{\
		return CheckForConst<TMap>::check;\
	}

template<typename T>
struct CheckForConst
{
	CONST_STRUCT(int, SFINAEint)
	CONST_STRUCT(char, SFINAEchar)
	CONST_STRUCT(void, SFINAEvoid)
	CONST_STRUCT(const char*, SFINAEconstcharptr)
	CONST_STRUCT(bool, SFINAEbool)
	template<typename U, bool (U::*)(int, Card&) const> struct SFINAEboolintCard {};

	// Lab 1 const tests
	CONST_TEST(TestCardGetFace, GetFace, HasCardGetFace, SFINAEint)
	CONST_TEST(TestCardGetSuit, GetSuit, HasCardGetSuit, SFINAEchar)
	CONST_TEST(TestCardShow, Show, HasCardShow, SFINAEvoid)

	// Lab 2 const tests
	CONST_TEST(TestPlayerGetNumCards, GetNumCards, HasPlayerGetNumCards, SFINAEint)
	CONST_TEST(TestPlayerGetMaxCards, GetMaxCards, HasPlayerGetMaxCards, SFINAEint)
	CONST_TEST(TestPlayerGetScore, GetScore, HasPlayerGetScore, SFINAEint)
	CONST_TEST(TestPlayerGetName, GetName, HasPlayerGetName, SFINAEconstcharptr)
	CONST_TEST(TestPlayerCard, GetCard, HasPlayerGetCard, SFINAEboolintCard)
	CONST_TEST(TestPlayerShow, Show, HasPlayerShow, SFINAEvoid)
	CONST_TEST(TestComputerShow, Show, HasComputerShow, SFINAEvoid)
	CONST_TEST(TestHumanShow, Show, HasHumanShow, SFINAEvoid)
	
	// Lab 3 const tests
	CONST_TEST(TestDeckEmpty, IsEmpty, HasDeckIsEmpty, SFINAEbool)
};

// Lab 1 const funcs
CONST_FUNC(CardGetFace, HasCardGetFace)
CONST_FUNC(CardGetSuit, HasCardGetSuit)
CONST_FUNC(CardShow, HasCardShow)

// Lab 2 const funcs
CONST_FUNC(PlayerGetNumCards,HasPlayerGetNumCards)
CONST_FUNC(PlayerGetMaxCards,HasPlayerGetMaxCards)
CONST_FUNC(PlayerGetScore, HasPlayerGetScore)
CONST_FUNC(PlayerGetName, HasPlayerGetName)
CONST_FUNC(PlayerShow, HasPlayerShow)
CONST_FUNC(PlayerGetCard, HasPlayerGetCard)
CONST_FUNC(ComputerShow, HasComputerShow)
CONST_FUNC(HumanShow, HasHumanShow)

// Lab 3 const tests
CONST_FUNC(DeckIsEmpty, HasDeckIsEmpty)

#pragma endregion

class CTestManager
{
private:

	CTestManager(void);
	~CTestManager(void);

public:

	// Lab1
#pragma region Lab 1 Test Methods

#if LAB1_CARD_CTOR
	static void Lab1CardConstructorNoParams();
	static void Lab1CardConstructorOneParam();
	static void Lab1CardConstructorTwoParams();
#endif

#if LAB1_CARD_GETFACE
	static void Lab1CardGetFace();
#endif

#if LAB1_CARD_GETSUIT
	static void Lab1CardGetSuit();
#endif

#if LAB1_CARD_SETFACE
	static void Lab1CardSetFace();
#endif

#if LAB1_CARD_SETSUIT
	static void Lab1CardSetSuit();
#endif

#if LAB1_CARD_REL_OP
	static void Lab1CardRelationalOps();
#endif

#if LAB1_CARD_SHOW
	static void Lab1CardShow();
#endif

#if LAB1_CARD_INSERT_OP
	static void Lab1CardOverloadedInsertionOp();
#endif

	// static void Lab1ConstTest();
#pragma endregion

	// Lab 2
#pragma region Lab 2 Test Methods
	
#if LAB2_PLAYER_CTOR
	static void Lab2PlayerConstructorNoParams();
	static void Lab2PlayerConstructorOneParam();
	static void Lab2PlayerConstructorTwoParams();
#endif

#if LAB2_PLAYER_GETNAME
	static void Lab2PlayerGetName();
#endif

#if LAB2_PLAYER_GETCARD
	static void Lab2PlayerGetCard();
#endif

#if LAB2_PLAYER_GETSCORE
	static void Lab2PlayerGetScore();
#endif

#if LAB2_PLAYER_SETNAME
	static void Lab2PlayerSetName();
#endif

#if LAB2_PLAYER_ADDSCORE
	static void Lab2PlayerAddToScore();
#endif

#if LAB2_PLAYER_ADDCARD
	static void Lab2PlayerAddCard();
#endif

#if LAB2_PLAYER_DISCARD
	static void Lab2PlayerDiscard();
#endif

#if LAB2_PLAYER_CLEAR
	static void Lab2PlayerClear();
#endif

#if LAB2_HUMAN_CTOR
	static void Lab2HumanConstructorNoParams();
	static void Lab2HumanConstructorOneParam();
#endif

#if LAB2_HUMAN_SHOW
	static void Lab2HumanShow();
#endif

#if LAB2_CPU_CTOR
	static void Lab2ComputerConstructorNoParams();
	static void Lab2ComputerConstructorOneParam();
#endif

#if LAB2_CPU_SHOW
	static void Lab2ComputerShow();
#endif

	// static void Lab2ConstTest();
#pragma endregion

	// Lab3
#pragma region Lab 3 Test Methods

#if LAB3_DECK_INIT
	static void Lab3DeckInitialize();
#endif

#if LAB3_DECK_SHUFFLE
	static void Lab3DeckShuffle();
#endif

#if LAB3_DECK_DRAW
	static void Lab3DeckDraw();
#endif

#if LAB3_DECK_CLEAR
	static void Lab3DeckClear();
#endif

#if LAB3_DECK_ISEMPTY
	static void Lab3DeckIsEmpty();
#endif

	// static void Lab3ConstTest();

	static void Sort(Card* deck);
	static bool SortBySuit(Card& cardA, Card& cardB);
	static bool SortByFace(Card& cardA, Card& cardB);
#pragma endregion

	// Lab 4
#pragma region Lab 4 Test Methods
	// Lab4


#if LAB4_PLAYER_CTOR
	static void Lab4PlayerConstructor();
#endif

#if LAB4_PLAYER_COPYCTOR
	static void Lab4PlayerCopyConstructor();
#endif

#if LAB4_PLAYER_ASSIGNOP
	static void Lab4PlayerAssignmentOperator();
#endif

/*
#if LAB4_PLAYER_DAISY
	static void Lab4PlayerAssignmentOperatorDaisyChain();
#endif

#if LAB4_PLAYER_SELFASSIGN
	static void Lab4PlayerAssignmentOperatorSelfAssignment();
#endif
*/
#pragma endregion

	// LAB5
#pragma region Lab 5 Test Methods

#if LAB5_STACK_TEMPLATE
	static void Lab5StackTemplate();
#endif

#if LAB5_CONSTDATAMEMBER
	static void Lab5ConstDataMember();
#endif

#pragma endregion

	// LAB7
#pragma region Lab 7 Test Methods
#if LAB7_PLAYER_ABC
	static void Lab7PlayerIsABC();
#endif

#pragma endregion
};

