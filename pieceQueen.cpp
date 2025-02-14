/***********************************************************************
 * Source File:
 *    QUEEN
 * Author:
 *    Nathan Bird, Brock Hoskins, Jared Davey
 * Summary:
 *    The Queen class
 ************************************************************************/

#include "board.h"
#include "move.h"
#include "piece.h"
#include "piecePawn.h"
#include "pieceQueen.h"
#include "pieceType.h"
#include "position.h"
#include "uiDraw.h"
#include <set>

 /**********************************************
  * QUEEN : GET POSITIONS
  *********************************************/
void Queen::getMoves(set<Move>& possible, const Board& board) const
{
   int row = position.getRow();
   int col = position.getCol();
   RelativePos moves[8] =
   {
      {-1,  1}, {0,  1}, {1,  1},
      {-1,  0},          {1,  0},
      {-1, -1}, {0, -1}, {1, -1}
   };
   int r, c;
   for (int i = 0; i < 8; i++)
   {
      r = row + moves[i].row;
      c = col + moves[i].col;
      Position newPos(c, r);

      while (r >= 0 && r < 8 && c >= 0 && c < 8 &&
             board[newPos] == PieceType::SPACE)
      {
         possible.insert(createNewMove(newPos, board));
         r += moves[i].row;
         c += moves[i].col;
         newPos = Position(c, r);
      }
      if (newPos.isValid() && (fWhite != board[newPos].isWhite() || board[newPos].getType() == SPACE))
         possible.insert(createNewMove(newPos, board));
   }
}

/***************************************************
 * QUEEN : DRAW
 * Draw the queen.
 ***************************************************/
void Queen::display(ogstream* pgout) const
{
   pgout->drawQueen(position, !fWhite);
}
