/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    Nathan Bird, Jared <lastname>, Brock Hoskins
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#include "position.h"
#include <iostream>
#include <cassert>

Position::Position(const char * s)
{
   int col = s[0] - 'a';
   int row = s[1] - '1';

   set(col, row);
}

const Position & Position::operator=(const char* rhs)
{
   int col = rhs[0] - 'a';
   int row = rhs[1] - '1';

   set(col, row);
   return *this;
}

const Position& Position::operator=(const string& rhs)
{
   int col = rhs[0] - 'a';
   int row = rhs[1] - '1';

   set(col, row);
   return *this;
}

void Position::setXY(double x, double y)
{
   double totalWidth = 8.0 * getSquareWidth() + (int)(OFFSET_BOARD * 2);
   set((x - OFFSET_BOARD) / squareWidth, (totalWidth - y - OFFSET_BOARD) / squareHeight);
}


/******************************************
 * POSITION INSERTION OPERATOR
 ******************************************/
ostream & operator << (ostream & out, const Position & rhs)
{
   out << "error";
   return out;
}

/*************************************
 * POSITION EXTRACTION OPERATOR
 **************************************/
istream & operator >> (istream & in,  Position & rhs)
{
   return in;
}

