/***********************************************************************
 * Source File:
 *    KING
 * Author:
 *    Nathan Bird, Brock Hoskins, Jared Davey
 * Summary:
 *    The King class
 ************************************************************************/

#include "board.h"
#include "move.h"
#include "piece.h"
#include "pieceKing.h"
#include "pieceType.h"
#include "position.h"
#include "uiDraw.h"
#include <cassert>
#include <set>

 /**********************************************
  * KING : GET POSITIONS
  *********************************************/
void King::getMoves(set<Move>& possible, const Board& board) const
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

      if (newPos.isValid() && (fWhite != board[newPos].isWhite() || board[newPos].getType() == SPACE))
         possible.insert(createNewMove(newPos, board));
   }

   // King-side Castle
   Position ksRookPos(col + 3, row);
   Position ksCastleMovePos(col + 2, row);
   Position rightOfKingPos(col + 1, row);
   if (nMoves == 0 &&  // King hasn't moved
       ksRookPos.isValid() &&        // Three spaces
       ksCastleMovePos.isValid() &&  // right of king
       rightOfKingPos.isValid() &&   // are valid.
       board[ksRookPos].getType() == PieceType::ROOK &&  // Piece in King-side rook starting spot is rook.
       board[ksRookPos].getNMoves() == 0 &&              // King-side rook hasn't moved.
       board[rightOfKingPos].getType() == PieceType::SPACE &&  // Pieces between king
       board[ksCastleMovePos].getType() == PieceType::SPACE)   // and rook are spaces.
      possible.insert(createCastleMove(ksCastleMovePos, Move::MoveType::CASTLE_KING));

   // Queen-side Castle
   Position qsRookPos(col - 4, row);
   Position rightOfRookPos(col - 3, row);
   Position qsCastleMovePos(col - 2, row);
   Position leftOfKingPos(col - 1, row);
   if (nMoves == 0 &&  // King hasn't moved
       qsRookPos.isValid() &&        // Four spaces
       rightOfRookPos.isValid() &&   // left of
       qsCastleMovePos.isValid() &&  // king are
       leftOfKingPos.isValid() &&    // valid.
       board[qsRookPos].getType() == PieceType::ROOK &&  // Piece in Queen-side rook starting spot is rook.
       board[qsRookPos].getNMoves() == 0 &&              // Queen-side rook hasn't moved.
       board[leftOfKingPos].getType() == PieceType::SPACE &&    // Empty spaces
       board[qsCastleMovePos].getType() == PieceType::SPACE &&  // between king
       board[rightOfRookPos].getType() == PieceType::SPACE)     // and rook.
      possible.insert(createCastleMove(qsCastleMovePos, Move::MoveType::CASTLE_QUEEN));
}

/***************************************************
 * KING : DRAW
 * Draw the king.
 ***************************************************/
void King::display(ogstream* pgout) const
{
   pgout->drawKing(position, !fWhite);
}

Move King::createCastleMove(const Position& newPos, Move::MoveType castleType) const
{
   assert(castleType == Move::MoveType::CASTLE_KING || castleType == Move::MoveType::CASTLE_QUEEN);
   return Move(position, newPos, PieceType::INVALID, PieceType::SPACE, castleType, fWhite);
}
