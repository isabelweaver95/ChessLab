/***********************************************************************
 * Header File:
 *    King
 * Author:
*    Nathan Bird, Brock Hoskins, Jared Davey
 * Summary:
 *    The King class
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
 * King
 * The King
 ***************************************************/
class King : public Piece
{
public:
   King(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
   King(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
   ~King() { }
   PieceType getType() const { return KING; }
   void getMoves(set <Move>& possible, const Board& board) const override;
   void display(ogstream* pgout) const override;
private:
   Move createCastleMove(const Position& newPos, Move::MoveType castleType) const;
};
