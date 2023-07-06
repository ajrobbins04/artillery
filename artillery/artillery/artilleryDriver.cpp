/*************************************************************
 * 1. Name:
 *      Amber Robbins
 * 2. Assignment Name:
 *      Lab 13: Artillery Final
 * 3. Assignment Description:
 *      Simulate firing of M777 Howitzer artillery.
 *****************************************************************/
#include "game.h"
#include "uiInteract.h"

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL.
   Game* pGame = (Game*)p;
   
   pGame->input(pUI);
   pGame->advance();
   pGame->draw(pUI);
}

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
	  "Game",   /* name on the window */
	   ptUpperRight);
	
   // Initialize the game
   Game game(ptUpperRight);

   // set everything into action
   ui.run(callBack, &game);

	return 0;
	
}

