/***********************************************************************
 * Header File:
 *    Pawn
 * Author:
*    Nathan Bird, Brock Hoskins, Jared Davey
 * Summary:
 *    The Pawn class
 ************************************************************************/

#pragma once

#include "board.h"
#include "move.h"
#include "piece.h"
#include "pieceType.h"
#include "position.h"
#include "uiDraw.h"
#include <set>

/***************************************************
 * Pawn
 * The Pawn
 ***************************************************/
class Pawn : public Piece
{
public:
   Pawn(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
   Pawn(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
   ~Pawn() { }
   PieceType getType() const { return PAWN; }
   void getMoves(set <Move>& possible, const Board& board) const override;
   void display(ogstream* pgout) const override;
private:
   Move createNewEnPassantMove(const Position& newPos, const Board& board) const;
   Move createNewPromoteMove(const Position& newPos, const Board& board)   const;
};
