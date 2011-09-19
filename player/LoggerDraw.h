/*
Copyright (c) 2004 Gregory Kuhlmann, Peter Stone
University of Texas at Austin
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the University of Amsterdam nor the names of its
contributors may be used to endorse or promote products derived from this
software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _LOGGER_DRAW_
#define _LOGGER_DRAW_

#include "SoccerTypes.h"
#include "Geometry.h"

#include <iostream>   // needed for ostream (logging to output stream)
#include <fstream>    // needed for fstream (logging to file)

using namespace std;

#define MAX_LABEL 128
#define MAX_TEXT 1024

enum ColorT
{
  COLOR_ALICE_BLUE,
  COLOR_ANTIQUE_WHITE,
  COLOR_AQUA,
  COLOR_AQUAMARINE,
  COLOR_AZURE,
  COLOR_BEIGE,
  COLOR_BISQUE,
  COLOR_BLACK,
  COLOR_BLANCHED_ALMOND,
  COLOR_BLUE,
  COLOR_BLUE_VIOLET,
  COLOR_BROWN,
  COLOR_BURLYWOOD,
  COLOR_CADET_BLUE,
  COLOR_CHARTREUSE,
  COLOR_CHOCOLATE,
  COLOR_CORAL,
  COLOR_CORNFLOWER_BLUE,
  COLOR_CORNSILK,
  COLOR_CYAN,
  COLOR_DARK_BLUE,
  COLOR_DARK_CYAN,
  COLOR_DARK_GOLDENROD,
  COLOR_DARK_GRAY,
  COLOR_DARK_GREEN,
  COLOR_DARK_KHAKI,
  COLOR_DARK_MAGENTA,
  COLOR_DARK_OLIVE_GREEN,
  COLOR_DARK_ORANGE,
  COLOR_DARK_ORCHID,
  COLOR_DARK_RED,
  COLOR_DARK_SALMON,
  COLOR_DARK_SEA_GREEN,
  COLOR_DARK_SLATE_BLUE,
  COLOR_DARK_SLATE_GRAY,
  COLOR_DARK_TURQUOISE,
  COLOR_DARK_VIOLET,
  COLOR_DEEP_PINK,
  COLOR_DEEP_SKY_BLUE,
  COLOR_DIM_GRAY,
  COLOR_DODGER_BLUE,
  COLOR_FIREBRICK,
  COLOR_FLORAL_WHITE,
  COLOR_FOREST_GREEN,
  COLOR_FUSCHIA,
  COLOR_GAINSBORO,
  COLOR_GHOST_WHITE,
  COLOR_GOLD,
  COLOR_GOLDENROD,
  COLOR_GRAY,
  COLOR_GREEN,
  COLOR_GREEN_YELLOW,
  COLOR_HONEYDEW,
  COLOR_HOT_PINK,
  COLOR_INDIAN_RED,
  COLOR_IVORY,
  COLOR_KHAKI,
  COLOR_LAVENDER,
  COLOR_LAVENDER_BLUSH,
  COLOR_LAWN_GREEN,
  COLOR_LEMON_CHIFFON,
  COLOR_LIGHT_BLUE,
  COLOR_LIGHT_CORAL,
  COLOR_LIGHT_CYAN,
  COLOR_LIGHT_GOLDENROD,
  COLOR_LIGHT_GOLDENROD_YELLOW,
  COLOR_LIGHT_GRAY,
  COLOR_LIGHT_GREEN,
  COLOR_LIGHT_PINK,
  COLOR_LIGHT_SALMON,
  COLOR_LIGHT_SEA_GREEN,
  COLOR_LIGHT_SKY_BLUE,
  COLOR_LIGHT_SLATE_BLUE,
  COLOR_LIGHT_SLATE_GRAY,
  COLOR_LIGHT_STEEL_BLUE,
  COLOR_LIGHT_YELLOW,
  COLOR_LIME,
  COLOR_LIME_GREEN,
  COLOR_LINEN,
  COLOR_MAGENTA,
  COLOR_MAROON,
  COLOR_MEDIUM_AQUAMARINE,
  COLOR_MEDIUM_BLUE,
  COLOR_MEDIUM_ORCHID,
  COLOR_MEDIUM_PURPLE,
  COLOR_MEDIUM_SEA_GREEN,
  COLOR_MEDIUM_SLATE_BLUE,
  COLOR_MEDIUM_SPRING_GREEN,
  COLOR_MEDIUM_TURQUOISE,
  COLOR_MEDIUM_VIOLET_RED,
  COLOR_MIDNIGHT_BLUE,
  COLOR_MINT_CREAM,
  COLOR_MISTY_ROSE,
  COLOR_MOCCASIN,
  COLOR_NAVAJO_WHITE,
  COLOR_NAVY,
  COLOR_OLD_LACE,
  COLOR_OLIVE,
  COLOR_OLIVE_DRAB,
  COLOR_ORANGE,
  COLOR_ORANGE_RED,
  COLOR_ORCHID,
  COLOR_PALE_GOLDENROD,
  COLOR_PALE_GREEN,
  COLOR_PALE_TURQUOISE,
  COLOR_PALE_VIOLET_RED,
  COLOR_PAPAYA_WHIP,
  COLOR_PEACH_PUFF,
  COLOR_PERU,
  COLOR_PINK,
  COLOR_PLUM,
  COLOR_POWDER_BLUE,
  COLOR_PURPLE,
  COLOR_RED,
  COLOR_ROSY_BROWN,
  COLOR_ROYAL_BLUE,
  COLOR_SADDLE_BROWN,
  COLOR_SALMON,
  COLOR_SANDY_BROWN,
  COLOR_SEA_GREEN,
  COLOR_SEASHELL,
  COLOR_SIENNA,
  COLOR_SILVER,
  COLOR_SKY_BLUE,
  COLOR_SLATE_BLUE,
  COLOR_SLATE_GRAY,
  COLOR_SNOW,
  COLOR_SPRING_GREEN,
  COLOR_STEEL_BLUE,
  COLOR_TAN,
  COLOR_TEAL,
  COLOR_THISTLE,
  COLOR_TOMATO,
  COLOR_TURQUOISE,
  COLOR_VIOLET,
  COLOR_VIOLET_RED,
  COLOR_WHEAT,
  COLOR_WHITE,
  COLOR_WHITE_SMOKE,
  COLOR_YELLOW,
  COLOR_YELLOW_GREEN,
  COLOR_ILLEGAL
} ;

/*************** LOG COLOR ***************/

class LogColor
{
  double m_r, m_g, m_b;

 public:
  LogColor( double r, double g, double b, double i=1.0 );

  LogColor operator * ( const double&   d );
  void     operator *=( const double&   d );
  bool     operator ==( const LogColor& l );
  bool     operator !=( const LogColor& l );

  friend ostream& operator <<( ostream &os, LogColor l );

  static LogColor getColor( ColorT c, double i=1.0 );
} ;

/************** LOGGER DRAW *************/

class LoggerDraw
{
  enum LogDrawT
  {
    LOG_DRAW_LINE,
    LOG_DRAW_TEXT,
    LOG_DRAW_CIRCLE,
    LOG_DRAW_CIRCLE_FILLED,
    LOG_DRAW_RECTANGLE,
    LOG_DRAW_RECTANGLE_FILLED,
    LOG_DRAW_ILLEGAL
  } ; 
  
  bool     m_active;
  int      m_cycle;
  int      m_cycle_start;
  int      m_depth;
  int      m_mult;
  LogDrawT m_shape;
  LogColor m_color;
  char     m_label[MAX_LABEL];
  ostream* m_os;

 public:
  LoggerDraw( ostream& os=cout, bool active=false );

  void setSide( SideT side );

  void logLine( char* label, 
		VecPosition start, VecPosition end, int depth=-1,
		ColorT color=COLOR_ILLEGAL, double intensity=1.0 );

  void logText( char* label,
		VecPosition pos, char* text, int depth=-1,
		ColorT color=COLOR_ILLEGAL, double intensity=1.0 );

  void logCircle( char* label,
		  VecPosition center, double radius, 
		  int depth=-1, bool filled=false, 
		  ColorT color=COLOR_ILLEGAL, double intensity=1.0 );
  
  void logRectangle( char* label,
		     VecPosition topLeft, VecPosition bottomRight, 
		     int depth=-1, bool filled=false, 
		     ColorT color=COLOR_ILLEGAL, double intensity=1.0 );

  void setTime( int cycle );

  void setActive( bool active );
  bool isActive();

  void setOutputStream( ostream& os );
  ostream& getOutputStream();

  char* escape( char* str );

} ;

#endif
