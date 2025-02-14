/***********************************************************************
 * Source File:
 *    MOVE
 * Author:
 *    Nathan Bird, Jared Davey, Brock Hoskins
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#include "move.h"
#include "pieceType.h"
#include "position.h"
#include <cctype>
#include <set>
#include <string>

using namespace std;

/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 ***************************************************/
Move::Move() : promote(PieceType::INVALID), capture(PieceType::INVALID), moveType(Move::MoveType::MOVE), isWhite(true)
{
}

Move::Move(const Position& source, const Position& dest, PieceType promote, PieceType capture, MoveType moveType, bool isWhite)
{
   this->source = source;
   this->dest = dest;
   this->promote = promote;
   this->capture = capture;
   this->moveType = moveType;
   this->isWhite = isWhite;
   this->text = getText();
}

Move::Move(const Position& source, const Position& dest, const set<Move>& possible)
{
   bool matched = false;
   for (const Move& move : possible)
   {
      if (move.getSource() == source && move.getDest() == dest)
      {
         this->source = source;
         this->dest = dest;
         this->isWhite = move.getIsWhite();
         this->promote = move.getPromote();
         this->capture = move.getCatpure();
         this->moveType = move.getMoveType();
         this->text = move.getText();
         matched = true;
      }
   }

   if (!matched)
   {
      Move();
   }

}

Move::Move(const char* text, const bool& isWhite)
{
   read(string(text));
   this->isWhite = isWhite;
}

Move::Move(const char* text)
{
   read(string(text));
   this->isWhite = true;
}

Move::Move(const string text, const bool& isWhite)
{
   read(text);
   this->isWhite = isWhite;
}

bool Move::operator==(const Move& rhs) const
{
   return this->source == rhs.source
      && this->dest == rhs.dest
      && this->promote == rhs.promote
      && this->capture == rhs.capture
      && this->moveType == rhs.moveType
      && this->isWhite == rhs.isWhite
      && this->text == rhs.text;
}

bool Move::operator!=(const Move& rhs) const
{
   return this->source != rhs.source
      || this->dest != rhs.dest
      || this->promote != rhs.promote
      || this->capture != rhs.capture
      || this->moveType != rhs.moveType
      || this->isWhite != rhs.isWhite
      || this->text != rhs.text;
}

char Move::letterFromPieceType(PieceType pt) const
{
   switch (pt)
   {
   case PieceType::SPACE:
      return '\0';
   case PieceType::PAWN:
      return 'p';
   case PieceType::BISHOP:
      return 'b';
   case PieceType::KNIGHT:
      return 'n';
   case PieceType::ROOK:
      return 'r';
   case PieceType::QUEEN:
      return 'q';
   case PieceType::KING:
      return 'k';
   }

   return -1;
}

PieceType Move::pieceTypeFromLetter(char letter) const
{
   switch (letter)
   {
   case 'p':
   case 'P':
      return PieceType::PAWN;
   case 'b':
   case 'B':
      return PieceType::BISHOP;
   case 'n':
   case 'N':
      return PieceType::KNIGHT;
   case 'r':
   case 'R':
      return PieceType::ROOK;
   case 'q':
   case 'Q':
      return PieceType::QUEEN;
   case 'k':
   case 'K':
      return PieceType::KING;
   }

   return PieceType::INVALID;
}

void Move::read(const string& text)
{
   this->text = text;
   string firstTwo_s = text.substr(0, 2);
   const char* firstTwo = firstTwo_s.c_str();
   this->source = Position(firstTwo);

   string nextTwo_s = text.substr(2, 4);
   const char* nextTwo = nextTwo_s.c_str();
   this->dest = Position(nextTwo);

   this->moveType = MoveType::MOVE;
   promote = PieceType::INVALID;
   capture = PieceType::SPACE;

   if (this->text.length() < 5)
      return;

   string moveNotes = this->text.substr(4, 7);


   char fifthChar = text[4];
   for (char character : moveNotes)
      if (islower(character))
      {
         if (character != 'c')
            capture = pieceTypeFromLetter(fifthChar);
         else
            moveType = CASTLE_KING;

      }
      else
      {
         if (character == 'Q')
         {
            moveType = MoveType::MOVE;
            promote = PieceType::QUEEN;
         }
           
         if (character == 'E')
            moveType = MoveType::ENPASSANT;
         if (character == 'C')
            moveType = MoveType::CASTLE_QUEEN;
      }
}

string Move::getText() const
{
   // Get PositionFrom
   string returnText;
   returnText += source.getCol() + 'a';
   returnText += source.getRow() + '1';

   // Get PositionTo
   returnText += dest.getCol() + 'a';
   returnText += dest.getRow() + '1';

   // captured a piece?
   if (capture != PieceType::INVALID && capture != PieceType::SPACE && moveType != MoveType::ENPASSANT)
      returnText += letterFromPieceType(capture);

   // Enpassant?
   if (moveType == MoveType::ENPASSANT)
      returnText += 'E';

   // Promoted?
   if (promote != PieceType::INVALID)
      returnText += toupper(letterFromPieceType(promote));

   // Castled?
   if (moveType == MoveType::CASTLE_KING)
      returnText += 'c';
   if (moveType == MoveType::CASTLE_QUEEN)
      returnText += 'C';

   return returnText;
}



