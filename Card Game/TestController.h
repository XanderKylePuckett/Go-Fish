#pragma once

/*
	Set the appropriate #define to "TRUE" or "1" based
	on what game you are making.
	*/

#define GO_FISH TRUE

#define UNO FALSE

/*
	Set these #defines to "TRUE" or "1" in order to run
	the associated test.

	After the test has successfully completed, you can turn them back to "FALSE"
	or "0", so that they don't run all the time

	You have the option to run all of a particular day's lab at once by just setting
	the "LAB#" #define to TRUE/1.

	However, if you prefer to test one function at a time, you can use the
	#defines for the individual tests (such as LAB1_CARD_CTOR).

	In order to run gameplay, set the "GAME" #define to TRUE/1.
	*/

#define LAB1 FALSE

#if !LAB1
#define LAB1_CARD_CTOR			FALSE
#define LAB1_CARD_GETFACE		FALSE
#define LAB1_CARD_GETSUIT		FALSE
#define LAB1_CARD_SETFACE		FALSE
#define LAB1_CARD_SETSUIT		FALSE
#define LAB1_CARD_REL_OP		FALSE
#define LAB1_CARD_SHOW			FALSE
#define LAB1_CARD_INSERT_OP		FALSE
#else
#define LAB1_CARD_CTOR			TRUE
#define LAB1_CARD_GETFACE		TRUE
#define LAB1_CARD_GETSUIT		TRUE
#define LAB1_CARD_SETFACE		TRUE
#define LAB1_CARD_SETSUIT		TRUE
#define LAB1_CARD_REL_OP		TRUE
#define LAB1_CARD_SHOW			TRUE
#define LAB1_CARD_INSERT_OP		TRUE
#endif


#define LAB2 FALSE

#if !LAB2
#define LAB2_PLAYER_CTOR		FALSE
#define LAB2_PLAYER_GETNAME		FALSE
#define LAB2_PLAYER_GETCARD		FALSE
#define LAB2_PLAYER_GETSCORE	FALSE
#define LAB2_PLAYER_SETNAME		FALSE
#define LAB2_PLAYER_ADDSCORE	FALSE
#define LAB2_PLAYER_ADDCARD		FALSE
#define LAB2_PLAYER_DISCARD		FALSE
#define LAB2_PLAYER_CLEAR		FALSE
#define LAB2_HUMAN_CTOR			FALSE
#define LAB2_HUMAN_SHOW			FALSE
#define LAB2_CPU_CTOR			FALSE
#define LAB2_CPU_SHOW			FALSE
#else
#define LAB2_PLAYER_CTOR		TRUE
#define LAB2_PLAYER_GETNAME		TRUE
#define LAB2_PLAYER_GETCARD		TRUE
#define LAB2_PLAYER_GETSCORE	FALSE
#define LAB2_PLAYER_SETNAME		TRUE
#define LAB2_PLAYER_ADDSCORE	FALSE
#define LAB2_PLAYER_ADDCARD		TRUE
#define LAB2_PLAYER_DISCARD		TRUE
#define LAB2_PLAYER_CLEAR		TRUE
#define LAB2_HUMAN_CTOR			TRUE
#define LAB2_HUMAN_SHOW			TRUE
#define LAB2_CPU_CTOR			TRUE
#define LAB2_CPU_SHOW			TRUE
#endif

#define LAB3 FALSE

#if !LAB3
#define LAB3_DECK_INIT			FALSE
#define LAB3_DECK_SHUFFLE		FALSE
#define LAB3_DECK_DRAW			FALSE
#define LAB3_DECK_CLEAR			FALSE
#define LAB3_DECK_ISEMPTY		FALSE
#else
#define LAB3_DECK_INIT			TRUE
#define LAB3_DECK_SHUFFLE		TRUE
#define LAB3_DECK_DRAW			TRUE
#define LAB3_DECK_CLEAR			TRUE
#define LAB3_DECK_ISEMPTY		TRUE
#endif

#define LAB4 FALSE

#if !LAB4
#define LAB4_PLAYER_CTOR		FALSE
#define LAB4_PLAYER_COPYCTOR	FALSE
#define LAB4_PLAYER_ASSIGNOP	FALSE
#else
#define LAB4_PLAYER_CTOR		TRUE
#define LAB4_PLAYER_COPYCTOR	TRUE
#define LAB4_PLAYER_ASSIGNOP	TRUE
#endif

#define LAB5 FALSE

#if !LAB5
#define LAB5_STACK_TEMPLATE		FALSE
#define LAB5_CONST_DATAMEMBER	FALSE
#else
#define LAB5_STACK_TEMPLATE		TRUE
#define LAB5_CONSTDATAMEMBER	TRUE
#endif

#define LAB7 FALSE

#if !LAB7
#define LAB7_PLAYER_ABC			FALSE
#else
#define LAB7_PLAYER_ABC			TRUE
#endif

#define GAME TRUE

// ☻☺ トニー ☺☻ //