// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _CRTDBG_MAP_ALLOC

#define SOUND 0

#include <Windows.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include "TestController.h"
#include "Console.h"
#if SOUND
#include <thread>
#endif

#define PLAYER_COL (System::DarkCyan)
#define CURR_PLAYER_COL (System::DarkMagenta)
#define NAME_MAX_LENGTH 60
#define NUM_HIGH_SCORES 10
#define START_HAND 7
#define MAX_HAND 15
#define MAX_PLAYERS 4
#define SHUFFLE_SWAP_COUNT 1000


// <MODS>

#define GFMOD_AUTORUN			0x0001 // 0000 0000  0000 0001 //   2 ^  ( 00 )
#define GFMOD_MAXAUTO			0x0002 // 0000 0000  0000 0010 //   2 ^  ( 01 )
#define GFMOD_CUMULATIVESCORE	0x0004 // 0000 0000  0000 0100 //   2 ^  ( 02 )
#define GFMOD_ALLCPU			0x0008 // 0000 0000  0000 1000 //   2 ^  ( 03 )

#define GFMOD_SHOWCPUASK		0x0010 // 0000 0000  0001 0000 //   2 ^  ( 04 )
#define GFMOD_NODELAYCPUASK		0x0020 // 0000 0000  0010 0000 //   2 ^  ( 05 )
#define GFMOD_VOCALOIDNAMES		0x0040 // 0000 0000  0100 0000 //   2 ^  ( 06 )
#define GFMOD_SHOWALLCARDS		0x0080 // 0000 0000  1000 0000 //   2 ^  ( 07 )


#define GFMOD_DISPLAYMODS		0x0100 // 0000 0001  0000 0000 //   2 ^  ( 08 )
#define GFMOD_SHOWDECK			0x0200 // 0000 0010  0000 0000 //   2 ^  ( 09 )
#define GFMOD_SKIPCPU			0x0400 // 0000 0100  0000 0000 //   2 ^  ( 10 )
#define GFMOD_UNUSED_12			0x0800 // 0000 1000  0000 0000 //   2 ^  ( 11 )

#define GFMOD_UNUSED_13			0x1000 // 0001 0000  0000 0000 //   2 ^  ( 12 )
#define GFMOD_UNUSED_14			0x2000 // 0010 0000  0000 0000 //   2 ^  ( 13 )
#define GFMOD_UNUSED_15			0x4000 // 0100 0000  0000 0000 //   2 ^  ( 14 )
#define GFMOD_UNUSED_16			0x8000 // 1000 0000  0000 0000 //   2 ^  ( 15 )

// ^MODS^

extern int gfhowtopage;

extern int numCPUs;
extern int gameRuns;
extern int autoRuns;
extern int autoRunPlayers;
extern unsigned int randSeed;
extern WORD mods;
extern bool GFMkeyPressed;

#if SOUND
extern int s_freq;
extern int s_dur;
#endif

typedef enum
{
	GAME_INIT_ONCE, GAME_INIT, GAME_PLAY, GAME_END, GAME_START, GAME_RESTART, MENU_LOOP, GFMODS_MENU, GFMAIN_MENU, GFMAIN_MENU2, EXIT_GAME, CLEAR_SCORES, GF_HOWTO
} GAMESTATE;

// ☻☺ トニー ☺☻ //驫麤