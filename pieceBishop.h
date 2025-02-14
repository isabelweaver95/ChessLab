/***********************************************************************
 * Header File:
 *    Bishop
 * Author:
*    Nathan Bird, Brock Hoskins, Jared Davey
 * Summary:
 *    The BISHOP class
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
 * Bishop
 * The Bishop
 ***************************************************/
class Bishop : public Piece
{
public:
   Bishop(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
   Bishop(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
   ~Bishop() { }
   PieceType getType() const { return BISHOP; }
   void getMoves(set <Move>& possible, const Board& board) const override;
   void display(ogstream* pgout) const override;
};
