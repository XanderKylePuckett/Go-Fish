#pragma once

#include "stdafx.h"
#include "TestController.h"
#include "TestManager.h"
#include "src\\UnitTest++.h"


// SUITE: PG2_Lab2_Tests
//
// This is the group of tests that test the code students
// write for Lab 2.  These are used to test functionality of code
// to ensure that your functions are returning and/or outputting
// the correct values. 
//
// Test code will not compile if any of the following are
// not written:
//
// Player class
//		Default constructor
//		AddCard
//		Discard
//		SetName
//		AddToScore
//		GetName
//		GetCard
//		Clear
//		Show
//
// Human class
//		Default constructor
//		Show
//
// Computer class
//		Default constructor
//		Show

SUITE(PG2_Lab2_Tests)
{
	// TEST: PG2_Lab2_Player_def_ctor_o_params
	// 
	// Ensures that the Player class's default constructor
	// can be called with no params and sets the data
	// members to "Player" for the name and 5 for the max
	//
	// Functions used in this test
	//		Player::Player (constructor
#if LAB2_PLAYER_CTOR
	TEST(PG2_Lab2_Player_def_ctor_o_params)
	{
		HEADER("Testing Player::Player (no params)")
		
		CTestManager::Lab2PlayerConstructorNoParams();

		FOOTER
	}

	// Test: PG2_Lab2_Player_def_ctor_one_param
	//
	// Ensures that the Player class's default constructor
	// can be called with one param (just the name)
	//
	// Functions used in this test:
	//		Player::Player (constructor)
	TEST(PG2_Lab2_Player_def_ctor_one_param)
	{
		HEADER("Testing Player::Player (one param)")
		
		CTestManager::Lab2PlayerConstructorOneParam();
	
		FOOTER
	}

	// Test: PG2_Lab2_Player_def_ctor_two_params
	//
	// Ensures that the Player class's default constructor
	// can be called with two params (the name and the max cards)
	//
	// Functions used in this test:
	//		Player::Player (constructor)
	TEST(PG2_Lab2_Player_def_ctor_two_params)
	{
		HEADER("Testing Player::Player (two params)")
		
		CTestManager::Lab2PlayerConstructorTwoParams();

		FOOTER
	}
#endif

	// TEST: PG2_Lab2_Player_GetName
	//
	// Ensures that the GetName method returns the name
	// data member.
	//
	// Functions used in this test:
	//		Player::Player (constructor)
	//		Card::GetName
#if LAB2_PLAYER_GETNAME
	TEST(PG2_Lab1_Card_GetName)
	{
		HEADER("Testing Player::GetName")

		CTestManager::Lab2PlayerGetName();

		FOOTER
	}	
#endif

	// TEST: PG2_Lab2_Player_GetCard
	//
	// Ensures that the GetCard method returns the card
	// from the 'hand' data member at the specified index.
	//
	// Functions used in this test:
	//		Card::Card (constructor)
	//		Player::Player (constructor)
	//		Card::GetCard
#if LAB2_PLAYER_GETCARD
	TEST(PG2_Lab1_Card_GetCard)
	{
		HEADER("Testing Player::GetCard")

		CTestManager::Lab2PlayerGetCard();

		FOOTER
	}
#endif

	// TEST: PG2_Lab2_Player_GetScore
	//
	// Ensures that the GetScore method returns the 
	// score data member
	//
	// Functions used in this test:
	//		Player::Player (constructor)
	//		Card::GetScore
#if LAB2_PLAYER_GETSCORE
	TEST(PG2_Lab1_Card_GetScore)
	{
		HEADER("Testing Player::GetScore")

		CTestManager::Lab2PlayerGetScore();

		FOOTER
	}	
#endif

	// Test: PG2_Lab2_Player_SetName
	//
	// Ensures that the Player::SetName method copies
	// the name passed as a parameter into the data
	// member of the class
	//
	// Functions used in this test:
	//		Player::Player (constructor)
	//		Player::SetName
#if LAB2_PLAYER_SETNAME
	TEST(PG2_Lab2_Player_SetName)
	{
		HEADER("Testing Player::SetName")

		CTestManager::Lab2PlayerSetName();

		FOOTER
	}
#endif

	// Test: PG2_Lab2_Player_AddToScore
	//
	// Ensures that the Player::AddToScore method 
	// increments the m_score data member by the value
	// passed in.
	//
	// Functions used in this test:
	//		Player::Player (constructor)
	//		Player::AddToScore
#if LAB2_PLAYER_ADDSCORE
	TEST(PG2_Lab2_Player_AddToScore)
	{
		HEADER("Testing Player::AddToScore")

		CTestManager::Lab2PlayerAddToScore();

		FOOTER
	}
#endif

	// Test: PG2_Lab2_Player_AddCard
	//
	// Ensures that the Player::AddCard method
	// works correctly under all scenarios.
	// Function needs to:
	//		Copy the parameter into the first "available" index
	//			and return success if able
	//		Increment the number of cards in the hand
	//		Fail if the player is already at their maximum capacity
	// 
	// Functions used in this test:
	//		Card::Card (constructor)
	//		Player::Player (constructor)
	//		Player::AddCard
#if LAB2_PLAYER_ADDCARD
	TEST(PG2_Lab2_Player_AddCard)
	{
		HEADER("Testing Player::AddCard")

		CTestManager::Lab2PlayerAddCard();

		FOOTER
	}
#endif

	// Test: PG2_Lab2_Player_Discard
	//
	// Ensures that the Player::Discard method
	// works correctly under all scenarios.
	// Function needs to:
	//		Copy the card at the passed index into the
	//			reference that is passed in (as the second param)
	//		Indicate success if there is a "valid" card
	//			at that index
	//		Decrement the number of cards in the hand
	//		Fail if the player is already at their maximum capacity
	// 
	// Functions used in this test:
	//		Card::Card (constructor)
	//		Player::Player (constructor)
	//		Player::Discard
#if LAB2_PLAYER_DISCARD
	TEST(PG2_Lab2_Player_Discard)
	{
		HEADER("Testing Player::Discard")
		
		CTestManager::Lab2PlayerDiscard();

		FOOTER
	}
#endif

	// Test: PG2_Lab2_Player_Clear
	//
	// Ensures that the Player::Clear method works correctly.
	//
	// Functions used in this test:
	//		Card::Card (constructor)
	//		Player::Player (constructor)
	//		Player::Clear
#if LAB2_PLAYER_CLEAR
	TEST(PG2_Lab2_Player_Clear)
	{
		HEADER("Testing Player::Clear")
		
		CTestManager::Lab2PlayerClear();

		FOOTER
	}
#endif

	// Test: PG2_Lab2_Human_def_ctor_o_params
	//
	// Ensures that the Human's default constructor
	// uses the member initializer to pass back information
	// to the parent class.
	//
	// Functions used in this test:
	//		Human::Human (constructor)
#if LAB2_HUMAN_CTOR
	TEST(PG2_Lab2_Human_def_ctor_o_params)
	{
		HEADER("Testing Human::Human (no params)")

		CTestManager::Lab2HumanConstructorNoParams();

		FOOTER
	}
	
	// Test: PG2_Lab2_Human_def_ctor_one_param
	//
	// Ensures that the Human's default constructor
	// uses the member initializer to pass back information
	// to the parent class.
	//
	// Functions used in this test:
	//		Human::Human (constructor)
	TEST(PG2_Lab2_Human_def_ctor_one_param)
	{
		HEADER("Testing Human::Human (one param)")

		CTestManager::Lab2HumanConstructorOneParam();

		FOOTER
	}
#endif

	// Test: PG2_Lab2_uman_Show
	//
	// Ensures that the Human's Show method
	// displays the player's name, cards (face up)
	// as well as their score
#if LAB2_HUMAN_SHOW
	TEST(PG2_Lab2_Human_Show)
	{
		Console::ForegroundColor(White);
		cout << "Testing Human::Show (not an automated test)\n";
		Console::ForegroundColor(Cyan);

		CTestManager::Lab2HumanShow();

		FOOTER
	}
#endif

	// Test: PG2_Lab2_Computer_def_ctor_o_params
#if LAB2_CPU_CTOR
	TEST(PG2_Lab2_Computer_def_ctor_o_params)
	{
		HEADER("Testing Computer::Computer (no params)")

		CTestManager::Lab2ComputerConstructorNoParams();

		Console::ResetColor();
	}

	// Test: PG2_Lab2_Computer_def_ctor_one_param
	TEST(PG2_Lab2_Computer_def_ctor_one_param)
	{
		HEADER("Testing Computer::Computer (one param)")

		CTestManager::Lab2ComputerConstructorOneParam();

		Console::ResetColor();
	}
#endif

	// Test: PG2_Lab2_Computer_Show
	//
	// Ensures that the Computer's Show method
	// displays the player's name, cards (face down)
	// as well as their score
#if LAB2_CPU_SHOW
	TEST(PG2_Lab2_Computer_Show)
	{
		Console::ForegroundColor(White);
		cout << "Testing Computer::Show (not an automated test)\n";
		Console::ForegroundColor(Cyan);

		CTestManager::Lab2ComputerShow();

		FOOTER
	}
#endif

	/*
	// Test: PG2_Lab2_const_test
	//
	// Ensures that all methods that need to protect
	// the invoking object are doing so.
	TEST(PG2_Lab2_const_test)
	{
		HEADER("Testing Player/Human/Computer constness")

		CTestManager::Lab2ConstTest();

		FOOTER
	}
	*/
}