/***********************************************************************
 * Header File:
 *    Rook
 * Author:
*    Nathan Bird, Brock Hoskins, Jared Davey
 * Summary:
 *    The Rook class
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
 * Rook
 * The Rook
 ***************************************************/
class Rook : public Piece
{
public:
   Rook(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
   Rook(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
   ~Rook() { }
   PieceType getType() const { return ROOK; }
   void getMoves(set <Move>& possible, const Board& board) const override;
   void display(ogstream* pgout) const override;
};
