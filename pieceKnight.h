/***********************************************************************
 * Header File:
 *    KNIGHT
 * Author:
*    Nathan Bird, Brock Hoskins, Jared Davey
 * Summary:
 *    The KNIGHT class
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
  * KNIGHT
  * The knight, aka the "Horse"
  ***************************************************/
class Knight : public Piece
{
public:
   Knight(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
   Knight(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
   ~Knight() { }
   PieceType getType() const { return KNIGHT; }
   void getMoves(set <Move>& possible, const Board& board) const override;
   void display(ogstream* pgout) const override;
};
