/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    Nathan Bird, Brock Hoskins, Jared Davey
 * Summary:
 *    The knight class
 ************************************************************************/

#include "board.h"
#include "move.h"
#include "piece.h"
#include "pieceKnight.h"
#include "pieceType.h"
#include "position.h"
#include "uiDraw.h"    // for draw*()
#include <set>

/**********************************************
 * KNIGHT : GET POSITIONS
 *********************************************/
void Knight::getMoves(set <Move>& possible, const Board& board) const
{
   int row = position.getRow();
   int col = position.getCol();
   RelativePos moves[8] =
   {
            {-1,  2}, { 1,  2},
   {-2,  1},                    { 2,  1},
   {-2, -1},                    { 2, -1},
            {-1, -2}, { 1, -2}
   };
   int r, c;
   for (int i = 0; i < 8; i++)
   {
      r = row + moves[i].row;
      c = col + moves[i].col;
      Position newPos(c, r);

      if (0 <= r && r <= 7 && 0 <= c && c <= 7)
         if (board[newPos].getType() == SPACE || (fWhite != board[newPos].isWhite()))
            possible.insert(createNewMove(newPos, board));
   }
}

/***************************************************
 * KNIGHT : Draw
 * Draw the knight.
 ***************************************************/
void Knight::display(ogstream* pgout) const
{
   pgout->drawKnight(position, !fWhite);
}
