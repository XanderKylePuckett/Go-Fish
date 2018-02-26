#include "BaseMenu.h"


BaseMenu::BaseMenu()
{
	currChoice = 0;
}


BaseMenu::~BaseMenu()
{

}

// return key (0=nokey) (1up,2down,3left,4right,5enter,6esc)
short BaseMenu::Input()
{
	if ( GetAsyncKeyState( VK_UP ) )
	{
		if ( !GFMkeyPressed )
		{
			GFMkeyPressed = true;
			return 1;
		}
	}
	else if ( GetAsyncKeyState( VK_DOWN ) )
	{
		if ( !GFMkeyPressed )
		{
			GFMkeyPressed = true;
			return 2;
		}
	}
	else if ( GetAsyncKeyState( VK_LEFT ) )
	{
		if ( !GFMkeyPressed )
		{
			GFMkeyPressed = true;
			return 3;
		}
	}
	else if ( GetAsyncKeyState( VK_RIGHT ) )
	{
		if ( !GFMkeyPressed )
		{
			GFMkeyPressed = true;
			return 4;
		}
	}
	else if ( GetAsyncKeyState( VK_RETURN ) )
	{
		if ( !GFMkeyPressed )
		{
			GFMkeyPressed = true;
			return 5;
		}
	}
	else if ( GetAsyncKeyState( VK_ESCAPE ) )
	{
		if ( !GFMkeyPressed )
		{
			GFMkeyPressed = true;
			return 6;
		}
	}
	else
		GFMkeyPressed = false;
	return 0;
}
// ☻☺ トニー ☺☻ //