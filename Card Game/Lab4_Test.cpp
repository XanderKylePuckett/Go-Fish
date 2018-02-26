#pragma once

#include "stdafx.h"
#include "TestController.h"
#include "TestManager.h"
#include "src\\UnitTest++.h"

SUITE(PG2_Lab4_Tests)
{
#if LAB4_PLAYER_CTOR
	TEST(PG2_Lab4_Player_Constructor)
	{
		HEADER("Testing Player::Player (default constructor)")

		CTestManager::Lab4PlayerConstructor();

		FOOTER
	}
#endif

#if LAB4_PLAYER_COPYCTOR
	TEST(PG2_Lab4_Player_Copy_Constructor)
	{
		HEADER("Testing Player::Player (copy constructor)")

		CTestManager::Lab4PlayerCopyConstructor();

		FOOTER
	}
#endif

#if LAB4_PLAYER_ASSIGNOP
	TEST(PG2_Lab4_Player_Assignment_Operator)
	{
		HEADER("Testing Player::operator=")

		CTestManager::Lab4PlayerAssignmentOperator();

		FOOTER

	}
#endif

}

