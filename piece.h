/***********************************************************************
 * Header File:
 *    PIECE
 * Author:
*    Nathan Bird, Jared Davey, Brock Hoskins
 * Summary:
 *    The Piece base class and all the derived classes:
 *       SPACE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
 ************************************************************************/

#pragma once

#include "move.h"      // Because we return a set of Move
#include "pieceType.h" // A piece type.
#include "position.h"  // Because Position is a member variable
#include <cassert>
#include <set>         // for SET to return a set of possible moves
using std::set;

// forward declaration because one of the Piece methods takes a Board
// as a parameter, and the Board has an array of Pieces
class ogstream;
class Board;
class MoveType;

class TestPiece;
class TestKing;
class TestPawn;
class TestQueen;
class TestRook;
class TestBishop;
class TestKnight;
class TestBoard;


/***************************************************
 * PIECE
 * The abstract piece type
 ***************************************************/
class Piece
{
public:
   friend TestPiece;
   friend TestKing;
   friend TestQueen;
   friend TestRook;
   friend TestBishop;
   friend TestKnight;
   friend TestPawn;
   friend TestBoard;
   
   // constructors and stuff
   Piece(const Position& pos, bool isWhite = true) : position(pos), fWhite(isWhite), nMoves(0), lastMove(0) {}
   Piece(int c, int r, bool isWhite = true) : position(Position(c, r)), fWhite(isWhite), nMoves(0), lastMove(0) {}
   Piece(const Piece& piece);
   virtual ~Piece() {}
   virtual const Piece& operator = (const Piece& rhs);

   // getters
   virtual bool operator == (PieceType pt) const;
   virtual bool operator != (PieceType pt) const;
   virtual bool isWhite()                  const { return fWhite;       }
   virtual bool isMoved()                  const { return nMoves != 0;  }
   virtual int  getNMoves()                const { return nMoves;       }
   virtual int  getLastMove()              const { return lastMove;     }
   virtual void decrementNMoves()                { nMoves--;            }
   virtual void incrementNMoves()                { nMoves++;            }
   virtual const Position & getPosition()  const { return position;     }
   virtual bool justMoved(int currentMove) const { return lastMove == currentMove - 1; }

   virtual Move createNewMove(const Position& newPos, const Board& board) const;

   // setter
   virtual void setLastMove(int currentMove);
   virtual void setPosition(const Position& newPos) { position.set(newPos.getCol(), newPos.getRow()); }

   // overwritten by the various pieces
   virtual PieceType getType()            const = 0;
   virtual void display(ogstream * pgout) const = 0;
   //virtual void getMovesSlide(set <Move>& moves, const Board& board)   const;
   //virtual void getMovesNoSlide(set <Move>& moves, const Board& board) const;
   virtual void getMoves(set <Move> & moves, const Board & board)      const;

protected:

   int  nMoves;                    // how many times have you moved?
   bool fWhite;                    // which team are you on?
   Position position;              // current position of this piece
   int  lastMove;                  // last time this piece moved
};



/***************************************************
 * PIECE DERIVED
 * A simple derived class so we can test Piece. This is a Space
 ***************************************************/
class PieceDerived : public Piece
{
public:
   PieceDerived(const Position& pos, bool isWhite) : Piece(9, 9) { }
   PieceDerived(int c, int r, bool isWhite) : Piece(9, 9)        { }
   ~PieceDerived()                                               { }
   PieceType getType()            const     { return SPACE;        }
   void display(ogstream* pgout)  const     { assert(false);       }
};



/***************************************************
 * PIECE DUMMY
 * The dummy double! - Everything returns FALSE
 ***************************************************/
class PieceDummy : public Piece
{
public:

   // constructors and stuff
   PieceDummy()                                          : Piece(0, 0, true   ) {}
   PieceDummy(const Position & pos, bool isWhite = true) : Piece(pos,  isWhite) {}
   PieceDummy(int c, int r, bool isWhite = true)         : Piece(c, r, isWhite) {}
   PieceDummy(const Piece & piece)                       : Piece(0, 0, true   ) {}
   ~PieceDummy()                                                                {}
   const Piece& operator = (const Piece& rhs)
   {
      assert(false);
      return *this;
   }
   const Piece& operator = (const Position& rhs)
   {
      assert(false);
      return *this;
   }

   // getters
   bool operator == (char letter)  const { assert(false); return true;     }
   bool operator != (char letter)  const { assert(false); return true;     }
   bool isWhite()                  const { assert(false); return true;     }
   bool isMoved()                  const { assert(false); return true;     }
   int  getNMoves()                const { assert(false); return 0;        }
   void decrementNMoves()                { assert(false);                  }
   const Position & getPosition()  const { assert(false); return position; }
   bool justMoved(int currentMove) const { assert(false); return true;     }

   // setter
   void setLastMove(int currentMove)     { assert(false); }

   // overwritten by the various pieces
   PieceType getType()             const { assert(false); return SPACE; }
   void display(ogstream * pgout)  const { assert(false);               }
};

/***************************************************
 * PIECE SPY
 * A piece that is only counted.
 **************************************************/
class PieceSpy : public PieceDummy
{
public:
   PieceSpy(int c, int r, bool f = true, PieceType pt = SPACE)
      : PieceDummy(c, r, f), pt(pt)
   {
      numConstruct++;
   }
   PieceSpy(const PieceSpy& piece) : PieceDummy(piece), pt(SPACE)
   {
      numCopy++;
   }
   ~PieceSpy()
   {
      numDelete++;
   }
   const PieceSpy& operator = (const PieceSpy& rhs)
   {
      numAssign++;
      return *this;
   }
   const Piece& operator = (const Position& rhs)
   {
      numMove++;
      nMoves++;                    // it moved one more time
      position = rhs;              // actually change the position
      return *this;                // return self
   }
   void setLastMove(int currentMove) { lastMove = currentMove; }
   const Position& getPosition()  const { return position; }
   PieceType getType()            const { return pt;       }
   bool isWhite()                 const { return fWhite;   }


   static int numConstruct;
   static int numCopy;
   static int numDelete;
   static int numAssign;
   static int numMove;

   static void reset()
   {
      numConstruct = numCopy = numDelete = numAssign = numMove = 0;
   }
private:
   PieceType pt;
};


/***************************************************
 * WHITE PIECE
 * Generic piece whose only allowable property is the color
 **************************************************/
class White : public PieceDummy
{
   PieceType pt;
public:
   White() : PieceDummy(), pt(ROOK) {}
   White(PieceType pt) : PieceDummy(), pt(pt) {}
   bool isWhite() const { return true; }
   PieceType getType() const { return pt; }
   void getMoves(set <Move>& moves, const Board& board) const { }
};

/***************************************************
 * WHITE PIECE NOT MOVED
 * Generic piece whose only allowable property is the color
 * and the number of moves, which is 0
 **************************************************/
class WhiteNotMoved : public PieceDummy
{
   PieceType pt;
public:
   WhiteNotMoved() : PieceDummy(), pt(ROOK) {}
   WhiteNotMoved(PieceType pt) : PieceDummy(), pt(pt) {}
   bool isWhite() const {
      return true;
   }
   PieceType getType() const {
      return pt;
   }
   int getNMoves() const { return 0; }
   void getMoves(set <Move>& moves, const Board& board) const { }
};

class Black : public PieceDummy
{
   PieceType pt;
   bool fWhite;
public:
   Black() : PieceDummy(), pt(ROOK), fWhite(false) {}
   Black(PieceType pt) : PieceDummy(), pt(pt), fWhite(false) {}
   bool isWhite() const { return false; }
   PieceType getType() const { return pt; }
   void getMoves(set <Move>& moves, const Board& board) const { }
};

class BlackNotMoved : public PieceDummy
{
   PieceType pt;
public:
   BlackNotMoved() : PieceDummy(), pt(ROOK) {}
   BlackNotMoved(PieceType pt) : PieceDummy(), pt(pt) {}
   bool isWhite() const { return false; }
   PieceType getType() const { return pt; }
   int getNMoves() const { return 0; }
   void getMoves(set <Move>& moves, const Board& board) const { }
};

class WhiteMoved : public PieceDummy
{
   PieceType pt;
public:
   WhiteMoved() : PieceDummy(), pt(ROOK) {}
   WhiteMoved(PieceType pt) : PieceDummy(), pt(pt) {}
   bool isWhite() const { return true; }
   PieceType getType() const { return pt; }
   int getNMoves() const { return 1; }
   void getMoves(set <Move>& moves, const Board& board) const { }
};

class BlackMoved : public PieceDummy
{
   PieceType pt;
public:
   BlackMoved() : PieceDummy(), pt(ROOK) {}
   BlackMoved(PieceType pt) : PieceDummy(), pt(pt) {}
   bool isWhite() const { return false; }
   PieceType getType() const { return pt; }
   int getNMoves() const { return 1; }
   void getMoves(set <Move>& moves, const Board& board) const { }
};

struct RelativePos {
   int col;
   int row;
};
