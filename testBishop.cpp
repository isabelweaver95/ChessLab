/***********************************************************************
 * Source File:
 *    TEST BISHOP
 * Author:
 *    Nathan Bird, Jared Davey, Brock Hoskins
 * Summary:
 *    The unit tests for a bishop
 ************************************************************************/


#include "testBishop.h"
#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>




/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3     p   p           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_blocked()
{
    // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, true /*fWhite*/);
   bishop.fWhite = false;  // black
   bishop.position.set(2, 1);
   board.board[2][1] = &bishop;
   Black black1(PAWN);
   board.board[1][0] = &black1;
   Black black2(PAWN);
   board.board[1][2] = &black2;
   Black black3(PAWN);
   board.board[3][0] = &black3;
   Black black4(PAWN);
   board.board[3][2] = &black4;
   set <Move> moves;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);  // no possible moves

   // TEARDOWN
   board.board[2][1] = nullptr; // black
   board.board[1][0] = nullptr; // black1
   board.board[1][2] = nullptr; // black2
   board.board[3][0] = nullptr; // black3
   board.board[3][2] = nullptr; // black4
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 .   7
 * 6               .     6
 * 5             .       5
 * 4   .       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     .   .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, true /*fWhite*/);
   bishop.fWhite = false;  // black
   bishop.position.set(2, 1);
   board.board[2][1] = &bishop;
   set <Move> moves;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 9);  // many possible moves
   assertUnit(moves.find(Move("c2b1")) != moves.end());
   assertUnit(moves.find(Move("c2d1")) != moves.end());
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2a4")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   assertUnit(moves.find(Move("c2h7")) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // black
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 p   7
 * 6               .     6
 * 5             .       5
 * 4   p       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, true /*fWhite*/);
   bishop.fWhite = false;  // black
   bishop.position.set(2, 1);
   board.board[2][1] = &bishop;
   Black black1(PAWN);
   board.board[1][0] = &black1;
   Black black2(PAWN);
   board.board[3][0] = &black2;
   Black black3(PAWN);
   board.board[0][3] = &black3;
   Black black4(PAWN);
   board.board[7][6] = &black4;
   set <Move> moves;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 5);  // many possible moves
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // black
   board.board[1][0] = nullptr; // black1
   board.board[0][3] = nullptr; // black3
   board.board[3][0] = nullptr;
   board.board[7][6] = nullptr; // black4
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 P   7
 * 6               .     6
 * 5             .       5
 * 4   P       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     P   P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false /*isWhite*/);
   bishop.fWhite = true;
   bishop.position.set(2, 1);
   board.board[2][1] = &bishop;
   Black black1(PAWN);
   board.board[1][0] = &black1;
   Black black2(PAWN);
   board.board[3][0] = &black2;
   Black black3(PAWN);
   board.board[0][3] = &black3;
   Black black4(PAWN);
   board.board[7][6] = &black4;
   set <Move> moves;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 9);  // many possible moves
   assertUnit(moves.find(Move("c2b1p")) != moves.end());
   assertUnit(moves.find(Move("c2d1p")) != moves.end());
   assertUnit(moves.find(Move("c2a4p")) != moves.end());
   assertUnit(moves.find(Move("c2h7p")) != moves.end());
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // black
   board.board[1][0] = nullptr; // black1
   board.board[0][3] = nullptr; // black3
   board.board[3][0] = nullptr;
   board.board[7][6] = nullptr; // black4
}


/*************************************
 * GET TYPE : bishop
 * Input:
 * Output: BISHOP
 **************************************/
void TestBishop::getType()
{
   // SETUP
   Bishop bishop(7, 7, false /*isWhite*/);
   bishop.fWhite = true;
   bishop.position.set(3, 4);

   // EXERCISE
   PieceType pt = bishop.getType();

   // VERIFY
   assertUnit(pt == PieceType::BISHOP);
   assertUnit(bishop.fWhite == true);
   assertUnit(bishop.position.getCol() == 3);
   assertUnit(bishop.position.getRow() == 4);
}
