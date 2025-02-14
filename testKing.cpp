/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    Savanna and Isabel
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "board.h"
#include "move.h"
#include "piece.h"
#include "pieceKing.h"
#include "pieceType.h"
#include "testKing.h"
#include "unitTest.h"
#include <set>


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       p p p         6
 * 5       p(k)p         5
 * 4       p p p         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, true);
   king.fWhite = false;  // black
   king.position.set(3, 4);
   board.board[3][4] = &king;
   Black black1(PAWN);
   board.board[2][3] = &black1;
   Black black2(PAWN);
   board.board[3][3] = &black2;
   Black black3(PAWN);
   board.board[4][3] = &black3;
   Black black4(PAWN);
   board.board[2][4] = &black4;
   Black black5(PAWN);
   board.board[4][4] = &black5;
   Black black6(PAWN);
   board.board[2][5] = &black6;
   Black black7(PAWN);
   board.board[3][5] = &black7;
   Black black8(PAWN);
   board.board[4][5] = &black8;
   set <Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);  // no possible moves

   // TEARDOWN
   board.board[3][4] = nullptr; // king
   board.board[2][3] = nullptr; // black1
   board.board[3][3] = nullptr; // black2
   board.board[4][3] = nullptr; // black3
   board.board[2][4] = nullptr; // black4
   board.board[4][4] = nullptr; // black5
   board.board[2][5] = nullptr; // black6
   board.board[3][5] = nullptr; // black7
   board.board[4][5] = nullptr; // black8
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       P P P         6
 * 5       P(k)P         5
 * 4       P P P         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_capture()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, true );
   king.fWhite = false;  // black
   king.position.set(3, 4);
   board.board[3][4] = &king;
   White white1(PAWN);
   board.board[2][3] = &white1;
   White white2(PAWN);
   board.board[3][3] = &white2;
   White white3(PAWN);
   board.board[4][3] = &white3;
   White white4(PAWN);
   board.board[2][4] = &white4;
   White white5(PAWN);
   board.board[4][4] = &white5;
   White white6(PAWN);
   board.board[2][5] = &white6;
   White white7(PAWN);
   board.board[3][5] = &white7;
   White white8(PAWN);
   board.board[4][5] = &white8;
   set <Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);  // no possible moves
   assertUnit(moves.find(Move("d5c4p")) != moves.end());
   assertUnit(moves.find(Move("d5d4p")) != moves.end());
   assertUnit(moves.find(Move("d5e4p")) != moves.end());
   assertUnit(moves.find(Move("d5c5p")) != moves.end());
   assertUnit(moves.find(Move("d5e5p")) != moves.end());
   assertUnit(moves.find(Move("d5c6p")) != moves.end());
   assertUnit(moves.find(Move("d5d6p")) != moves.end());
   assertUnit(moves.find(Move("d5e6p")) != moves.end());

   // TEARDOWN
   board.board[3][4] = nullptr; // king
   board.board[2][3] = nullptr; // white1
   board.board[3][3] = nullptr; // white2
   board.board[4][3] = nullptr; // white3
   board.board[2][4] = nullptr; // white4
   board.board[4][4] = nullptr; // white5
   board.board[2][5] = nullptr; // white6
   board.board[3][5] = nullptr; // white7
   board.board[4][5] = nullptr; // white8
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       . . .         6
 * 5       .(k).         5
 * 4       . . .         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_free()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, true );
   king.fWhite = false;  // black
   king.position.set(3, 4);
   board.board[3][4] = &king;
   set <Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);  // no possible moves
   assertUnit(moves.find(Move("d5c4")) != moves.end());
   assertUnit(moves.find(Move("d5d4")) != moves.end());
   assertUnit(moves.find(Move("d5e4")) != moves.end());
   assertUnit(moves.find(Move("d5c5")) != moves.end());
   assertUnit(moves.find(Move("d5e5")) != moves.end());
   assertUnit(moves.find(Move("d5c6")) != moves.end());
   assertUnit(moves.find(Move("d5d6")) != moves.end());
   assertUnit(moves.find(Move("d5e6")) != moves.end());

   // TEARDOWN
   board.board[3][4] = nullptr; // king
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2   . .               2
 * 1  (k).               1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, true );
   king.position.set(0, 0);
   board.board[0][0] = &king;
   set<Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(Move("a1a2")) != moves.end());
   assertUnit(moves.find(Move("a1b2")) != moves.end());
   assertUnit(moves.find(Move("a1b1")) != moves.end());

   // TEARDOWN
   board.board[0][0] = nullptr; // king
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastle()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false );
   king.fWhite = true;
   king.position.set(4, 0);
   board.board[4][0] = &king;
   White pawn1(PAWN);
   White pawn2(PAWN);
   White pawn3(PAWN);
   WhiteNotMoved qsRook(ROOK);
   WhiteNotMoved ksRook(ROOK);
   board.board[3][1] = &pawn1;
   board.board[4][1] = &pawn2;
   board.board[5][1] = &pawn3;
   board.board[0][0] = &qsRook;
   board.board[7][0] = &ksRook;
   set<Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);
   assertUnit(moves.find(Move("e1c1C")) != moves.end());
   assertUnit(moves.find(Move("e1d1")) != moves.end());
   assertUnit(moves.find(Move("e1f1")) != moves.end());
   assertUnit(moves.find(Move("e1g1c")) != moves.end());

   // TEARDOWN
   board.board[4][0] = nullptr;
   board.board[3][1] = nullptr;
   board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
   board.board[0][0] = nullptr;
   board.board[7][0] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 ************************************/
void TestKing::getMoves_blackCastle()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false );
   king.fWhite = false;  // black
   king.position.set(4, 7);
   Black pawn1(PAWN);
   board.board[3][6] = &pawn1;
   Black pawn2(PAWN);
   board.board[4][6] = &pawn2;
   Black pawn3(PAWN);
   board.board[5][6] = &pawn3;
   BlackNotMoved qsRook(ROOK);
   board.board[0][7] = &qsRook;
   BlackNotMoved ksRook(ROOK);
   board.board[7][7] = &ksRook;
   set<Move> moves;
   
   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 4);
   assertUnit(moves.find(Move("e8c8C")) != moves.end());
   assertUnit(moves.find(Move("e8d8")) != moves.end());
   assertUnit(moves.find(Move("e8f8")) != moves.end());
   assertUnit(moves.find(Move("e8g8c")) != moves.end());

   // TEARDOWN
   board.board[4][7] = nullptr; // king
   board.board[3][6] = nullptr; // pawn1
   board.board[4][6] = nullptr; // pawn2
   board.board[5][6] = nullptr; // pawn3
   board.board[0][7] = nullptr; // qkRook
   board.board[7][7] = nullptr; // ksRook
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false );
   king.fWhite = true;
   king.position.set(4, 0);
   king.nMoves = 1;
   board.board[4][0] = &king;
   White pawn1(PAWN);
   White pawn2(PAWN);
   White pawn3(PAWN);
   WhiteNotMoved qsRook(ROOK);
   WhiteNotMoved ksRook(ROOK);
   board.board[3][1] = &pawn1;
   board.board[4][1] = &pawn2;
   board.board[5][1] = &pawn3;
   board.board[0][0] = &qsRook;
   board.board[7][0] = &ksRook;
   set<Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("e1d1")) != moves.end());
   assertUnit(moves.find(Move("e1f1")) != moves.end());

   // TEARDOWN
   board.board[4][0] = nullptr; // king
   board.board[3][1] = nullptr; // pawn1
   board.board[4][1] = nullptr; // pawn2
   board.board[5][1] = nullptr; // pawn3
   board.board[0][0] = nullptr; // qsrook
   board.board[7][0] = nullptr; // ksrook
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false );
   king.fWhite = true;
   king.position.set(4, 0);
   board.board[4][0] = &king;
   White pawn1(PAWN);
   White pawn2(PAWN);
   White pawn3(PAWN);
   WhiteMoved qsRook(ROOK);
   WhiteMoved ksRook(ROOK);
   board.board[3][1] = &pawn1;
   board.board[4][1] = &pawn2;
   board.board[5][1] = &pawn3;
   board.board[0][0] = &qsRook;
   board.board[7][0] = &ksRook;
   set<Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(Move("e1d1")) != moves.end());
   assertUnit(moves.find(Move("e1f1")) != moves.end());

   // TEARDOWN
   board.board[4][0] = nullptr; // king
   board.board[3][1] = nullptr; // pawn1
   board.board[4][1] = nullptr; // pawn2
   board.board[5][1] = nullptr; // pawn3
   board.board[0][0] = nullptr; // qsrook
   board.board[7][0] = nullptr; // ksrook
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{
   // SETUP
   King king(7, 7, true );
   king.fWhite = false;
   king.position.set(0, 0);
   PieceType pt;
   // EXERCISE
   pt = king.getType();
   // VERIFY
   assertUnit(pt == PieceType::KING);
}  // TEARDOWN


