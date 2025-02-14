/***********************************************************************
 * Header File:
 *    Queen
 * Author:
 *    Isabel and Savanna
 * Summary:
 *    The Queen class
 ************************************************************************/

#pragma once

#include "board.h"
#include "move.h"
#include "piece.h"
#include "piecePawn.h"
#include "pieceType.h"
#include "position.h"
#include "uiDraw.h"
#include <set>

/***************************************************
 * QUEEN
 * The Queen
 ***************************************************/
class Queen : public Piece
{
public:
   Queen(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
   Queen(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
   Queen(const Pawn& pawn) : Piece(pawn) { }
   ~Queen() { }
   PieceType getType() const { return QUEEN; }
   void getMoves(set <Move>& possible, const Board& board) const override;
   void display(ogstream* pgout) const override;
};
