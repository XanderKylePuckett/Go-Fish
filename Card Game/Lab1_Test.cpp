#pragma once



#include "stdafx.h"
#include "TestController.h"
#include "TestManager.h"
#include "src\\UnitTest++.h"


#include "Card.h"

// SUITE: PG2_Lab1_Tests
//
// This is the group of tests that test the code students
// write for Lab 1.  These are used to test functionality of code
// to ensure that your functions are returning and/or outputting
// the correct values.  These tests do not verify the "constness"
// of your code.
//
// Test code will not compile if any of the following are
// not written:
//
// Card class
//		Default constructor
//		GetFace
//		GetSuit
//		SetFace
//		SetSuit
//		Show
//		All of the relational operators
//		Insertion operator

SUITE(PG2_Lab1_Tests)
{
	// TEST: PG2_Lab1_Card_def_ctor_o_params
	//
	// Ensures that the Card class's default constructor
	// can be called with no params and sets the data
	// members to the "two of hearts"
	//
	// Functions used in this test:
	//		Card::Card (constructor)
#if LAB1_CARD_CTOR
	TEST(PG2_Lab1_Card_def_ctor_o_params)
	{
		HEADER("Testing Card::Card (no params)")
	
		CTestManager::Lab1CardConstructorNoParams();

		FOOTER
	}

	// Test: PG2_Lab1_Card_def_ctor_one_param
	// 
	// Ensures that the Card class's default constructor
	// can be called with one parameter (just the face)
	//
	// Functions used in this test:
	//		Card::Card (constructor)
	TEST(PG2_Lab1_Card_def_ctor_one_param)
	{
		HEADER("Testing Card::Card (one param)")
		
		CTestManager::Lab1CardConstructorOneParam();

		FOOTER
	}

	// Test: PG2_Lab1_Card_def_ctor_two_params
	// 
	// Ensures that the Card class's default constructor
	// can be called with two parameters
	//
	// Functions used in this test:
	//		Card::Card (constructor)
	TEST(PG2_Lab1_Card_def_ctor_two_params)
	{
		HEADER("Testing Card::Card (two params)")
	
		CTestManager::Lab1CardConstructorTwoParams();

		FOOTER
	}
#endif

	// TEST: PG2_Lab1_Card_GetFace
	//
	// Ensures that the GetFace method returns the face
	// data member.
	//
	// Functions used in this test:
	//		Card::GetFace
#if LAB1_CARD_GETFACE
	TEST(PG2_Lab1_Card_GetFace)
	{
		HEADER("Testing Card::GetFace")

		CTestManager::Lab1CardGetFace();

		FOOTER
	}
#endif

	// TEST: PG2_Lab1_Card_GetFace
	//
	// Ensures that the GetFace method returns the face
	// data member.
	//
	// Functions used in this test:
	//		Card::GetFace
#if LAB1_CARD_GETSUIT
	TEST(PG2_Lab1_Card_GetSuit)
	{
		HEADER("Testing Card::GetSuit")

		CTestManager::Lab1CardGetSuit();

		FOOTER
	}	
#endif

	// TEST: PG2_Lab1_Card_SetFace
	// 
	// Ensures that the SetFace method sets the face data
	// member.
	// 
	// Functions used in this test:
	//		Card::GetFace
#if LAB1_CARD_SETFACE
	TEST(PG2_Lab1_Card_SetFace)
	{
		HEADER("Testing Card::SetFace")
		
		CTestManager::Lab1CardSetFace();

		FOOTER
	}
#endif

	// TEST: PG2_Lab1_Card_SetSuit
	// 
	// Ensures that the SetSuit method sets the suit data
	// member.
	//
	// Functions used in this test:
	//		Card::SetSuit
#if LAB1_CARD_SETSUIT
	TEST(PG2_Lab1_Card_SetSuit)
	{
		HEADER("Testing Card::SetSuit")
		
		CTestManager::Lab1CardSetSuit();
		
		FOOTER
	}
#endif

	// TEST: PG2_Lab1_Card_Relational_Operators
	// 
	// Calls all six of the relational operators for the
	// Card class, and verifies that they return the 
	// correct result (true or false), based on the
	// values of the two card's face values (with
	// the Ace being the highest valued card)
	//
	// Functions used in this test:
	//		Card::operator>
	//		Card::operator<
	//		Card::operator>=
	//		Card::operator<=
	//		Card::operator==
	//		Card::operator!=
#if LAB1_CARD_REL_OP
	TEST(PG2_Lab1_Card_Relational_Operators)
	{
		HEADER("Testing Card's Relational Operators")
	
		CTestManager::Lab1CardRelationalOps();

		FOOTER
	}
#endif

	// TEST: PG2_Lab1_Card_Show
	//
	// Tests that your Card::Show method is displaying correctly.  
	// The test requires that your Show method displays *ONLY* the suit and face
	// without any additional newlines or spacing.  Example: 2♥ or K♣
	// Functions used in this test:
	//		Card::Show
#if LAB1_CARD_SHOW
	TEST(PG2_Lab1_Card_Show)
	{
		HEADER("Testing Card::Show")

		CTestManager::Lab1CardShow();

		FOOTER
	}
#endif

	// TEST: PG2_Lab1_Card_Overloaded_Insertion_Op
	//
	// Tests that your insertion operator for Cards is displaying correctly.  
	// The test requires that your insertion operator displays *ONLY* the suit and face
	// without any additional newlines or spacing.  Example: 2♥ or K♣
	// Functions used in this test:
	//		Card::Card (constructor)
	//		operator<<
#if LAB1_CARD_INSERT_OP
	TEST(PG2_Lab1_Card_Overloaded_Insertion_Op)
	{
		HEADER("Testing Card's overloaded <<")

		CTestManager::Lab1CardOverloadedInsertionOp();

		FOOTER
	}
#endif

	/*
	TEST(PG2_Lab1_const_test)
	{
		HEADER("Testing Card constness")

		CTestManager::Lab1ConstTest();

		FOOTER
	}
	*/
}

