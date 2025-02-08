/***********************************************************************
 * Source File:
 *    TEST ROOK
 * Author:
 *    Savanna and Isabel
 * Summary:
 *    The unit tests for the rook
 ************************************************************************/

#include <set>
#include "board.h"
#include "move.h"
#include "piece.h"
#include "pieceRook.h"
#include "pieceType.h"
#include "testRook.h"
#include "unitTest.h"


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3       p             3
 * 2     p(r)p           2
 * 1       p             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_blocked()
{
       // SETUP
   BoardEmpty board;
   Rook rook(7, 7, true /*fWhite*/);
   rook.fWhite = false;  // black
   rook.position.set(2, 1);
   board.board[2][1] = &rook;
   Black black1(PAWN);
   board.board[1][1] = &black1;
   Black black2(PAWN);
   board.board[2][2] = &black2;
   Black black3(PAWN);
   board.board[2][0] = &black3;
   Black black4(PAWN);
   board.board[3][1] = &black4;
   set <Move> moves;

   // EXERCISE
   rook.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);  // no possible moves

   // TEARDOWN
   board.board[2][1] = nullptr; // black
   board.board[1][1] = nullptr; // black1
   board.board[2][0] = nullptr; // black2
   board.board[3][1] = nullptr; // black3
   board.board[2][2] = nullptr; // black4
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   . .(r). . . . .   2
 * 1       .             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToEnd()
{
          // SETUP
   BoardEmpty board;
   Rook rook(7, 7, true /*fWhite*/);
   rook.fWhite = false;  // black
   rook.position.set(2, 1);
   board.board[2][1] = &rook;
   set <Move> moves;

   // EXERCISE
   rook.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 14);  // many possible moves
   assertUnit(moves.find(Move("c2c1")) != moves.end());
   assertUnit(moves.find(Move("c2b2")) != moves.end());
   assertUnit(moves.find(Move("c2a2")) != moves.end());
   assertUnit(moves.find(Move("c2d2")) != moves.end());
   assertUnit(moves.find(Move("c2e2")) != moves.end());
   assertUnit(moves.find(Move("c2f2")) != moves.end());
   assertUnit(moves.find(Move("c2g2")) != moves.end());
   assertUnit(moves.find(Move("c2h2")) != moves.end());
   assertUnit(moves.find(Move("c2c3")) != moves.end());
   assertUnit(moves.find(Move("c2c4")) != moves.end());
   assertUnit(moves.find(Move("c2c5")) != moves.end());
   assertUnit(moves.find(Move("c2c6")) != moves.end());
   assertUnit(moves.find(Move("c2c7")) != moves.end());
   assertUnit(moves.find(Move("c2c8")) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // black
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   p .(r). . . . p   2
 * 1       p             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Rook rook(7, 7, true /*fWhite*/);
   rook.fWhite = false;  // black
   rook.position.set(2, 1);
   board.board[2][1] = &rook;
   Black black1(PAWN);
   board.board[2][0] = &black1;
   Black black2(PAWN);
   board.board[0][1] = &black2;
   Black black3(PAWN);
   board.board[7][1] = &black3;
   Black black4(PAWN);
   board.board[2][7] = &black4;
   set <Move> moves;

   // EXERCISE
   rook.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 10);  // many possible moves
   assertUnit(moves.find(Move("c2b2")) != moves.end());
   assertUnit(moves.find(Move("c2d2")) != moves.end());
   assertUnit(moves.find(Move("c2e2")) != moves.end());
   assertUnit(moves.find(Move("c2f2")) != moves.end());
   assertUnit(moves.find(Move("c2g2")) != moves.end());
   assertUnit(moves.find(Move("c2c3")) != moves.end());
   assertUnit(moves.find(Move("c2c4")) != moves.end());
   assertUnit(moves.find(Move("c2c5")) != moves.end());
   assertUnit(moves.find(Move("c2c6")) != moves.end());
   assertUnit(moves.find(Move("c2c7")) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // black
   board.board[0][1] = nullptr;
   board.board[2][0] = nullptr;
   board.board[7][1] = nullptr;
   board.board[2][7] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   P .(r). . . . P   2
 * 1       P             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Rook rook(7, 7, true /*fWhite*/);
   rook.fWhite = true;  // black
   rook.position.set(2, 1);
   board.board[2][1] = &rook;
   Black black1(PAWN);
   board.board[2][0] = &black1;
   Black black2(PAWN);
   board.board[0][1] = &black2;
   Black black3(PAWN);
   board.board[7][1] = &black3;
   Black black4(PAWN);
   board.board[2][7] = &black4;
   set <Move> moves;

   // EXERCISE
   rook.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 14);  // many possible moves
   assertUnit(moves.find(Move("c2b2")) != moves.end());
   assertUnit(moves.find(Move("c2d2")) != moves.end());
   assertUnit(moves.find(Move("c2e2")) != moves.end());
   assertUnit(moves.find(Move("c2f2")) != moves.end());
   assertUnit(moves.find(Move("c2g2")) != moves.end());
   assertUnit(moves.find(Move("c2c3")) != moves.end());
   assertUnit(moves.find(Move("c2c4")) != moves.end());
   assertUnit(moves.find(Move("c2c5")) != moves.end());
   assertUnit(moves.find(Move("c2c6")) != moves.end());
   assertUnit(moves.find(Move("c2c7")) != moves.end());
   assertUnit(moves.find(Move("c2c8p")) != moves.end());
   assertUnit(moves.find(Move("c2h2p")) != moves.end());
   assertUnit(moves.find(Move("c2a2p")) != moves.end());
   assertUnit(moves.find(Move("c2c1p")) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // black
   board.board[0][1] = nullptr;
   board.board[2][0] = nullptr;
   board.board[7][1] = nullptr;
   board.board[2][7] = nullptr;
}


/*************************************
 * GET TYPE : rook
 * Input:
 * Output: ROOK
 **************************************/
void TestRook::getType()
{
   // SETUP
   Rook rook(7, 7, false /*fWhite*/);
   rook.fWhite = true;
   rook.position.set(3, 4);

   // EXERCISE
   PieceType pt = rook.getType();

   // VERIFY
   assertUnit(pt == PieceType::ROOK);
   assertUnit(rook.fWhite == true);
   assertUnit(rook.position.getCol() == 3);
   assertUnit(rook.position.getRow() == 4);
}  // TEARDOWN
