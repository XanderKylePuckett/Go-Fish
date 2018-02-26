#pragma once

#include "stdafx.h"
#include "TestController.h"
#include "TestManager.h"
#include "src\\UnitTest++.h"

SUITE(PG2_LAB7_Tests)
{
#if LAB7_PLAYER_ABC
	TEST(PG2_LAB7_Player_ABC)
	{
		HEADER("Testing Player for ABC")

		CTestManager::Lab7PlayerIsABC();

		FOOTER
	}
#endif
}


