/**********************************************************************
* Source File:
*    Lab 06: Chess Final
* Author:
*    Nathan Bird, Jared Davey, Brock Hoskins
* Summary:
*    Play the game of chess
************************************************************************/


#include "board.h"        // for BOARD
#include "move.h"
#include "piece.h"
#include "pieceType.h"
#include "test.h"
#include "uiDraw.h"       // for OGSTREAM
#include "uiInteract.h"   // for Interface
#include <set>
using namespace std;


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(Interface* pUI, void* p)
{

   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL.
   Board* pBoard = (Board*)p;

   Move move;
   set <Move> possible;

   // Get the possible moves from the previous (source) location.
   if (pUI->getPreviousPosition().isValid())
      (*pBoard)[pUI->getPreviousPosition()].getMoves(possible, *pBoard);

   // Create the move that matches the source/dest to one of the possible moves.
   if (pUI->getSelectPosition().isValid() && pUI->getPreviousPosition().isValid())
      move = Move(pUI->getPreviousPosition(), pUI->getSelectPosition(), possible);

   // move
   if (possible.find(move) != possible.end())
   {
      pBoard->move(move);
      pUI->clearSelectPosition();
   }
   // Previous source/dest didn't match any moves in possible, so draw current
   // selection's possible moves.
   else if (pUI->getSelectPosition().isValid())
   {
      possible.clear();
      (*pBoard)[pUI->getSelectPosition()].getMoves(possible, *pBoard);
   }

   // if we clicked on a blank spot, then it is not selected
   if (pUI->getSelectPosition().isValid() && (*pBoard)[pUI->getSelectPosition()].getType() == SPACE)
      pUI->clearSelectPosition();

   pBoard->display(pUI->getHoverPosition(), pUI->getSelectPosition(), possible);
}


/*********************************
 * MAIN - Where it all begins...
 *********************************/
#ifdef _WIN32
#include <windows.h>
#include <sal.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{

   // run all the unit tests
   testRunner();

   // Instantiate the graphics window
   Interface ui("Chess");

   // Initialize the game class
   ogstream* pgout = new ogstream;
   Board board(pgout);
   board.reset();

   // set everything into action
   ui.run(callBack, (void*)(&board));

   // All done.
   delete pgout;
   return 0;
}
