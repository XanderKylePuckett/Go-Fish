#pragma once

#include "stdafx.h"
#include "TestController.h"
#include "TestManager.h"
#include "src\\UnitTest++.h"


SUITE(PG2_Lab5_Tests)
{
#if LAB5_STACK_TEMPLATE
	TEST(PG2_Lab5_Stack_Templated)
	{
		HEADER("Testing CStack for template")

		CTestManager::Lab5StackTemplate();

		FOOTER
	}
#endif

#if LAB5_CONSTDATAMEMBER
		TEST(PG2_Lab5_Const_Data_Member)
	{
		HEADER("Testing Player::m_MaxHand for const")

		CTestManager::Lab5ConstDataMember();

		FOOTER
	}
#endif
}
