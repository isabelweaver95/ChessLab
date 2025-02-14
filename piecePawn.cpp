/***********************************************************************
 * Source File:
 *    PAWN
 * Author:
 *    Nathan Bird, Brock Hoskins, Jared Davey
 * Summary:
 *    The Pawn class
 ************************************************************************/

#include "board.h"
#include "move.h"
#include "piecePawn.h"
#include "pieceType.h"
#include "position.h"
#include "uiDraw.h"
#include <set>

 /**********************************************
  * PAWN : GET POSITIONS
  *********************************************/
void Pawn::getMoves(set<Move>& possible, const Board& board) const
{
   int row = position.getRow();
   int col = position.getCol();
   int r, c;
   Position newPos;

   if (!fWhite)
   {
      c = col;
      r = row - 2;
      newPos.set(c, r);
      if (row == 6 && board[newPos].getType() == PieceType::SPACE)
         possible.insert(createNewMove(newPos, board));  // forward two blank spaces
      r = row - 1;
      newPos.set(c, r);
      if (r >= 1 && board[newPos].getType() == PieceType::SPACE)
         possible.insert(createNewMove(newPos, board));  // forward one black space
      c = col - 1;
      newPos.set(c, r);
      if (c >= 0 && board[newPos].isWhite() &&
          board[newPos].getType() != PieceType::SPACE &&
          r != 0)
         possible.insert(createNewMove(newPos, board));  // attack left
      c = col + 1;
      newPos.set(c, r);
      if (c < 8 && board[newPos].isWhite() &&
          board[newPos].getType() != PieceType::SPACE &&
          r != 0)
         possible.insert(createNewMove(newPos, board));  // attack right
      
      // Black En Passant
      c = col - 1;
      r = row;
      newPos.set(c, r);
      if ((c >= 0) &&  // Valid column
          (r == 3) &&  // Correct row for en passant
          (board[newPos].getType() == PieceType::PAWN) &&  // Pawn to the left
          (board[newPos].isWhite() != fWhite) &&           // Left pawn is opposite color
          (board[newPos].getLastMove() == board.getCurrentMove()))  // Left pawn just moved
         possible.insert(createNewEnPassantMove(Position(c, r - 1), board));
      c = col + 1;
      r = row;
      newPos.set(c, r);
      if ((c <  8) &&  // Valid column
          (r == 3) &&  // Correct row for en passant
          (board[newPos].getType() == PieceType::PAWN) &&  // Pawn to the right
          (board[newPos].isWhite() != fWhite) &&           // Right pawn is opposite color
          (board[newPos].getLastMove() == board.getCurrentMove()))  // Right pawn just moved
         possible.insert(createNewEnPassantMove(Position(c, r - 1), board));

      // Black Promote
      c = col;
      r = row - 1;
      newPos.set(c, r);
      if (r == 0 &&  // row 0 for black promote
          board[newPos].getType() == PieceType::SPACE)  // In front of pawn has to be space.
         possible.insert(createNewPromoteMove(newPos, board));
      c = col - 1;
      newPos.set(c, r);
      if ((c >= 0) &&  // valid col
          (r == 0) &&  // row 0 for black promote
          (board[newPos].isWhite() != fWhite) &&  // Opposite colors
          (board[newPos].getType() != PieceType::SPACE))  // Only capture here
         possible.insert(createNewPromoteMove(newPos, board));
      c = col + 1;
      newPos.set(c, r);
      if ((c < 8) &&  // valid col
          (r == 0) &&  // row 0 for black promote
          (board[newPos].isWhite() != fWhite) &&  // Opposite colors
          (board[newPos].getType() != PieceType::SPACE))  // Only capture here
         possible.insert(createNewPromoteMove(newPos, board));
   }
   if (fWhite)
   {
      c = col;
      r = row + 2;
      newPos.set(c, r);
      if (row == 1 && board[newPos].getType() == PieceType::SPACE)
         possible.insert(createNewMove(newPos, board));  // forward two blank spaces
      r = row + 1;
      newPos.set(c, r);
      if (r < 7 && board[newPos].getType() == PieceType::SPACE)
         possible.insert(createNewMove(newPos, board));  // forward one blank space
      c = col - 1;
      newPos.set(c, r);
      if (c >= 0 && !board[newPos].isWhite() &&
          board[newPos].getType() != PieceType::SPACE &&
          r != 7)
         possible.insert(createNewMove(newPos, board));  // attack left
      c = col + 1;
      newPos.set(c, r);
      if (c < 8 && !board[newPos].isWhite() &&
          board[newPos].getType() != PieceType::SPACE &&
          r != 7)
         possible.insert(createNewMove(newPos, board));  // attack right
      
      // En Passant
      c = col - 1;
      r = row;
      newPos.set(c, r);
      if ((c >= 0) &&  // Valid column
          (r == 4) &&  // Correct row for en passant
          (board[newPos].getType() == PieceType::PAWN) &&  // Pawn to the left
          (board[newPos].isWhite() != fWhite) &&           // Left pawn is opposite color
          (board[newPos].getLastMove() == board.getCurrentMove()))  // Left pawn just moved
         possible.insert(createNewEnPassantMove(Position(c, r + 1), board));
      c = col + 1;
      r = row;
      newPos.set(c, r);
      if ((c <  8) &&  // Valid column
          (r == 4) &&  // Correct row for en passant
          (board[newPos].getType() == PieceType::PAWN) &&  // Pawn to the right
          (board[newPos].isWhite() != fWhite) &&           // Right pawn is opposite color
          (board[newPos].getLastMove() == board.getCurrentMove()))  // Right pawn just moved
         possible.insert(createNewEnPassantMove(Position(c, r + 1), board));

      // White Promote
      c = col;
      r = row + 1;
      newPos.set(c, r);
      if (r == 7 &&  // row 7 for white promote
          board[newPos].getType() == PieceType::SPACE)  // In front of pawn has to be space.
         possible.insert(createNewPromoteMove(newPos, board));
      c = col - 1;
      newPos.set(c, r);
      if ((c >= 0) &&  // valid col
          (r == 7) &&  // row 7 for white promote
          (board[newPos].isWhite() != fWhite) &&  // Opposite colors
          (board[newPos].getType() != PieceType::SPACE))  // Only capture here
         possible.insert(createNewPromoteMove(newPos, board));
      c = col + 1;
      newPos.set(c, r);
      if ((c < 8) &&  // valid col
          (r == 7) &&  // row 7 for white promote
          (board[newPos].isWhite() != fWhite) &&  // Opposite colors
          (board[newPos].getType() != PieceType::SPACE))  // Only capture here
         possible.insert(createNewPromoteMove(newPos, board));
   }
}

/***************************************************
 * PAWN : DRAW
 * Draw the pawn.
 ***************************************************/
void Pawn::display(ogstream* pgout) const
{
   pgout->drawPawn(position, !fWhite);
}

Move Pawn::createNewEnPassantMove(const Position& newPos, const Board& board) const
{
   return Move(position, newPos, PieceType::INVALID, board[newPos].getType(), Move::MoveType::ENPASSANT, fWhite);
}

Move Pawn::createNewPromoteMove(const Position& newPos, const Board& board) const
{
   return Move(position, newPos, PieceType::QUEEN, board[newPos].getType(), Move::MoveType::MOVE, fWhite);
}
