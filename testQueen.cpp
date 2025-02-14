/***********************************************************************
 * Source File:
 *    TEST QUEEN
 * Author:
 *    Brock Hoskins, Jared Davey, Nathan Bird
 * Summary:
 *    The unit tests for the queen
 ************************************************************************/

#include "board.h"
#include "move.h"
#include "piece.h"
#include "pieceQueen.h"
#include "pieceType.h"
#include "testQueen.h"
#include "unitTest.h"
#include <set>



/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3     p p p           3
 * 2     p(q)p           2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Queen queen(7, 7, true /*fWhite*/);
   queen.fWhite = false;  // black
   queen.position.set(2, 1);
   board.board[2][1] = &queen;
   Black black1(PAWN);
   board.board[1][0] = &black1;
   Black black2(PAWN);
   board.board[2][0] = &black2;
   Black black3(PAWN);
   board.board[3][0] = &black3;
   Black black4(PAWN);
   board.board[1][1] = &black4;
   Black black5(PAWN);
   board.board[3][1] = &black5;
   Black black6(PAWN);
   board.board[1][2] = &black6;
   Black black7(PAWN);
   board.board[2][2] = &black7;
   Black black8(PAWN);
   board.board[3][2] = &black8;
   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);  // no possible moves

   // TEARDOWN
   board.board[2][1] = nullptr; // queen
   board.board[1][0] = nullptr; // black1
   board.board[2][0] = nullptr; // black2
   board.board[3][0] = nullptr; // black3
   board.board[1][1] = nullptr; // black4
   board.board[3][1] = nullptr; // black5
   board.board[1][2] = nullptr; // black6
   board.board[2][2] = nullptr; // black7
   board.board[3][2] = nullptr; // black8
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .         .   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   .   .   .         4
 * 3     . . .           3
 * 2   . .(q). . . . .   2
 * 1     . . .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Queen queen(7, 7, true /*fWhite*/);
   queen.fWhite = false;  // black
   queen.position.set(2, 1);
   board.board[2][1] = &queen;
   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 23);  // many possible moves
   assertUnit(moves.find(Move("c2b1")) != moves.end());
   assertUnit(moves.find(Move("c2c1")) != moves.end());
   assertUnit(moves.find(Move("c2d1")) != moves.end());
   assertUnit(moves.find(Move("c2a2")) != moves.end());
   assertUnit(moves.find(Move("c2b2")) != moves.end());
   assertUnit(moves.find(Move("c2d2")) != moves.end());
   assertUnit(moves.find(Move("c2e2")) != moves.end());
   assertUnit(moves.find(Move("c2f2")) != moves.end());
   assertUnit(moves.find(Move("c2g2")) != moves.end());
   assertUnit(moves.find(Move("c2h2")) != moves.end());
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2c3")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2a4")) != moves.end());
   assertUnit(moves.find(Move("c2c4")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2c5")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2c6")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   assertUnit(moves.find(Move("c2c7")) != moves.end());
   assertUnit(moves.find(Move("c2h7")) != moves.end());
   assertUnit(moves.find(Move("c2c8")) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // queen
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .         p   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   p   .   .         4
 * 3     . . .           3
 * 2   p .(q). . . . p   2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Queen queen(7, 7, true /*fWhite*/);
   queen.fWhite = false;  // black
   queen.position.set(2, 1);
   board.board[2][1] = &queen;
   Black black1(PAWN);
   board.board[1][0] = &black1;
   Black black2(PAWN);
   board.board[2][0] = &black2;
   Black black3(PAWN);
   board.board[3][0] = &black3;
   Black black4(PAWN);
   board.board[0][1] = &black4;
   Black black5(PAWN);
   board.board[7][1] = &black5;
   Black black6(PAWN);
   board.board[0][3] = &black6;
   Black black7(PAWN);
   board.board[7][6] = &black7;
   Black black8(PAWN);
   board.board[2][7] = &black8;
   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 15);  // many possible moves
   assertUnit(moves.find(Move("c2b2")) != moves.end());
   assertUnit(moves.find(Move("c2d2")) != moves.end());
   assertUnit(moves.find(Move("c2e2")) != moves.end());
   assertUnit(moves.find(Move("c2f2")) != moves.end());
   assertUnit(moves.find(Move("c2g2")) != moves.end());
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2c3")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2c4")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2c5")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2c6")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   assertUnit(moves.find(Move("c2c7")) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // queen
   board.board[1][0] = nullptr; // black1
   board.board[2][0] = nullptr; // black2
   board.board[3][0] = nullptr; // black3
   board.board[0][1] = nullptr; // black4
   board.board[7][1] = nullptr; // black5
   board.board[0][3] = nullptr; // black6
   board.board[7][6] = nullptr; // black7
   board.board[2][7] = nullptr; // black8
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .         P   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   P   .   .         4
 * 3     . . .           3
 * 2   P .(q). . . . P   2
 * 1     P P P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Queen queen(7, 7, true /*fWhite*/);
   queen.fWhite = false;  // black
   queen.position.set(2, 1);
   board.board[2][1] = &queen;
   White white1(PAWN);
   board.board[1][0] = &white1;
   White white2(PAWN);
   board.board[2][0] = &white2;
   White white3(PAWN);
   board.board[3][0] = &white3;
   White white4(PAWN);
   board.board[0][1] = &white4;
   White white5(PAWN);
   board.board[7][1] = &white5;
   White white6(PAWN);
   board.board[0][3] = &white6;
   White white7(PAWN);
   board.board[7][6] = &white7;
   White white8(PAWN);
   board.board[2][7] = &white8;
   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 23);  // many possible moves
   assertUnit(moves.find(Move("c2b1p")) != moves.end());
   assertUnit(moves.find(Move("c2c1p")) != moves.end());
   assertUnit(moves.find(Move("c2d1p")) != moves.end());
   assertUnit(moves.find(Move("c2a2p")) != moves.end());
   assertUnit(moves.find(Move("c2b2")) != moves.end());
   assertUnit(moves.find(Move("c2d2")) != moves.end());
   assertUnit(moves.find(Move("c2e2")) != moves.end());
   assertUnit(moves.find(Move("c2f2")) != moves.end());
   assertUnit(moves.find(Move("c2g2")) != moves.end());
   assertUnit(moves.find(Move("c2h2p")) != moves.end());
   assertUnit(moves.find(Move("c2b3")) != moves.end());
   assertUnit(moves.find(Move("c2c3")) != moves.end());
   assertUnit(moves.find(Move("c2d3")) != moves.end());
   assertUnit(moves.find(Move("c2a4p")) != moves.end());
   assertUnit(moves.find(Move("c2c4")) != moves.end());
   assertUnit(moves.find(Move("c2e4")) != moves.end());
   assertUnit(moves.find(Move("c2c5")) != moves.end());
   assertUnit(moves.find(Move("c2f5")) != moves.end());
   assertUnit(moves.find(Move("c2c6")) != moves.end());
   assertUnit(moves.find(Move("c2g6")) != moves.end());
   assertUnit(moves.find(Move("c2c7")) != moves.end());
   assertUnit(moves.find(Move("c2h7p")) != moves.end());
   assertUnit(moves.find(Move("c2c8p")) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // queen
   board.board[1][0] = nullptr; // white1
   board.board[2][0] = nullptr; // white2
   board.board[3][0] = nullptr; // white3
   board.board[0][1] = nullptr; // white4
   board.board[7][1] = nullptr; // white5
   board.board[0][3] = nullptr; // white6
   board.board[7][6] = nullptr; // white7
   board.board[2][7] = nullptr; // white8
}


/*************************************
 * GET TYPE : queen
 * Input:
 * Output: QUEEN
 **************************************/
void TestQueen::getType()
{
   // SETUP
   Queen queen(7, 7, false /*fWhite*/);
   queen.fWhite = true;
   queen.position.set(3, 4);

   // EXERCISE
   PieceType pt = queen.getType();

   // VERIFY
   assertUnit(pt == PieceType::QUEEN);
   assertUnit(queen.fWhite == true);
   assertUnit(queen.position.getCol() == 3);
   assertUnit(queen.position.getRow() == 4);
}  // TEARDOWN
