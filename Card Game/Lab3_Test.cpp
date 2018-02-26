#pragma once

#include "stdafx.h"
#include "TestController.h"
#include "TestManager.h"
#include "src\\UnitTest++.h"

// SUITE: PG2_Lab3_Tests
//
// This is the group of tests that test the code students
// write for Lab 2.  These are used to test functionality of code
// to ensure that your functions are returning and/or outputting
// the correct values. 
//
// Test code will not compile if any of the following are
// not written:
//
// Deck class
//		Default constructor
//		Initialize
//		Shuffle
//		Draw
//		Clear
//		IsEmpty

SUITE(PG2_Lab3_Tests)
{
	// TEST: PG2_Lab3_Deck_Initialize
	// 
	// Ensures that the deck is initialized with the 
	// correct cards for the game being made
	//
	// Functions used in this test
	//		Deck::Deck (constructor)
	//		Deck::Initialize
	//		Card::Card (constructor)
#if LAB3_DECK_INIT
	TEST(PG2_Lab3_Deck_Initialize)
	{
		HEADER("Testing Deck::Initialize")
		
		CTestManager::Lab3DeckInitialize();

		FOOTER
	}
#endif

	// TEST: PG2_Lab3_Deck_Shuffle
	//
	// Ensures that the deck is shuffled adequately.
	// Tests to make sure that a certain percentage of 
	// cards are not in their original position.
	// 
	// Functions used in this test
	//		Deck::Deck (constructor)
	//		Deck::Shuffle
#if LAB3_DECK_SHUFFLE
	TEST(PG2_Lab3_Deck_Shuffle)
	{
		HEADER("Testing Deck::Shuffle");

		CTestManager::Lab3DeckShuffle();

		FOOTER
	}
#endif

#if LAB3_DECK_DRAW
	TEST(PG2_Lab3_Deck_Draw)
	{
		HEADER("Testing Deck::Draw");

		CTestManager::Lab3DeckDraw();

		FOOTER
	}
#endif

#if LAB3_DECK_CLEAR
	TEST(PG2_Lab3_Deck_Clear)
	{
		HEADER("Testing Deck::Clear");

		CTestManager::Lab3DeckClear();

		FOOTER
	}
#endif

#if LAB3_DECK_ISEMPTY
	TEST(PG2_Lab3_Deck_IsEmpty)
	{
		HEADER("Testing Deck::IsEmpty");

		CTestManager::Lab3DeckIsEmpty();

		FOOTER
	
	}
#endif

	/*
	TEST(PG2_Lab3_const_test)
	{
		HEADER("Testing Deck constness");

		CTestManager::Lab3ConstTest();

		FOOTER
	}
	*/
}
