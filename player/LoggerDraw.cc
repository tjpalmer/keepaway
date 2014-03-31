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

#include "LoggerDraw.h"
#include <cstring>

#define NORM(x) ( ( x < 0 ) ? 0 : ( x > 1 ) ? 1 : x )

LoggerDraw LogDraw;

/************************ LogColor ***************************/

LogColor::LogColor( double r, double g, double b, double i )
{
  m_r = r;
  m_g = g;
  m_b = b;
  *this *= i;
}

LogColor LogColor::operator *( const double& d )
{
  return LogColor( m_r, m_g, m_b, d );
}
  
void LogColor::operator *=( const double& d )
{
  m_r = NORM( m_r * d );
  m_g = NORM( m_g * d );
  m_b = NORM( m_b * d );
}

bool LogColor::operator ==( const LogColor& l )
{
  return m_r == l.m_r && m_g == l.m_g && m_b == l.m_b;
}

bool LogColor::operator !=( const LogColor& l )
{
  return !( *this == l );
}

LogColor LogColor::getColor( ColorT c, double i )
{
  switch( c ) {
  case COLOR_ALICE_BLUE : return LogColor( 0.941176, 0.972549, 1, i );
  case COLOR_ANTIQUE_WHITE : return LogColor( 0.980392, 0.921569, 0.843137, i );
  case COLOR_AQUA : return LogColor( 0, 1, 1, i );
  case COLOR_AQUAMARINE : return LogColor( 0.498039, 1, 0.831373, i );
  case COLOR_AZURE : return LogColor( 0.941176, 1, 1, i );
  case COLOR_BEIGE : return LogColor( 0.960784, 0.960784, 0.862745, i );
  case COLOR_BISQUE : return LogColor( 1, 0.894118, 0.768627, i );
  case COLOR_BLACK: return LogColor( 0, 0, 0, i );
  case COLOR_BLANCHED_ALMOND : return LogColor( 1, 0.921569, 0.803922, i );
  case COLOR_BLUE : return LogColor( 0, 0, 1, i );
  case COLOR_BLUE_VIOLET : return LogColor( 0.541176, 0.168627, 0.886275, i );
  case COLOR_BROWN : return LogColor( 0.647059, 0.164706, 0.164706, i );
  case COLOR_BURLYWOOD : return LogColor( 0.870588, 0.721569, 0.529412, i );
  case COLOR_CADET_BLUE : return LogColor( 0.372549, 0.619608, 0.627451, i );
  case COLOR_CHARTREUSE : return LogColor( 0.498039, 1, 0, i );
  case COLOR_CHOCOLATE : return LogColor( 0.823529, 0.411765, 0.117647, i );
  case COLOR_CORAL : return LogColor( 1, 0.498039, 0.313725, i );
  case COLOR_CORNFLOWER_BLUE : return LogColor( 0.392157, 0.584314, 0.929412, i );
  case COLOR_CORNSILK : return LogColor( 1, 0.972549, 0.862745, i );
  case COLOR_CYAN : return LogColor( 0, 1, 1, i );
  case COLOR_DARK_BLUE : return LogColor( 0, 0, 0.545098, i );
  case COLOR_DARK_CYAN : return LogColor( 0, 0.545098, 0.545098, i );
  case COLOR_DARK_GOLDENROD : return LogColor( 0.721569, 0.52549, 0.0431373, i );
  case COLOR_DARK_GRAY : return LogColor( 0.662745, 0.662745, 0.662745, i );
  case COLOR_DARK_GREEN : return LogColor( 0, 0.392157, 0, i );
  case COLOR_DARK_KHAKI : return LogColor( 0.741176, 0.717647, 0.419608, i );
  case COLOR_DARK_MAGENTA : return LogColor( 0.545098, 0, 0.545098, i );
  case COLOR_DARK_OLIVE_GREEN : return LogColor( 0.333333, 0.419608, 0.184314, i );
  case COLOR_DARK_ORANGE : return LogColor( 1, 0.54902, 0, i );
  case COLOR_DARK_ORCHID : return LogColor( 0.6, 0.196078, 0.8, i );
  case COLOR_DARK_RED : return LogColor( 0.545098, 0, 0, i );
  case COLOR_DARK_SALMON : return LogColor( 0.913725, 0.588235, 0.478431, i );
  case COLOR_DARK_SEA_GREEN : return LogColor( 0.560784, 0.737255, 0.560784, i );
  case COLOR_DARK_SLATE_BLUE : return LogColor( 0.282353, 0.239216, 0.545098, i );
  case COLOR_DARK_SLATE_GRAY : return LogColor( 0.184314, 0.309804, 0.309804, i );
  case COLOR_DARK_TURQUOISE : return LogColor( 0, 0.807843, 0.819608, i );
  case COLOR_DARK_VIOLET : return LogColor( 0.580392, 0, 0.827451, i );
  case COLOR_DEEP_PINK : return LogColor( 1, 0.0784314, 0.576471, i );
  case COLOR_DEEP_SKY_BLUE : return LogColor( 0, 0.74902, 1, i );
  case COLOR_DIM_GRAY : return LogColor( 0.411765, 0.411765, 0.411765, i );
  case COLOR_DODGER_BLUE : return LogColor( 0.117647, 0.564706, 1, i );
  case COLOR_FIREBRICK : return LogColor( 0.698039, 0.133333, 0.133333, i );
  case COLOR_FLORAL_WHITE : return LogColor( 1, 0.980392, 0.941176, i );
  case COLOR_FOREST_GREEN : return LogColor( 0.133333, 0.545098, 0.133333, i );
  case COLOR_FUSCHIA: return LogColor( 1, 0, 1, i );
  case COLOR_GAINSBORO : return LogColor( 0.862745, 0.862745, 0.862745, i );
  case COLOR_GHOST_WHITE : return LogColor( 1, 0.980392, 0.980392, i );
  case COLOR_GOLD : return LogColor( 1, 0.843137, 0, i );
  case COLOR_GOLDENROD : return LogColor( 0.854902, 0.647059, 0.12549, i );
  case COLOR_GRAY : return LogColor( 0.501961, 0.501961, 0.501961, i );
  case COLOR_GREEN: return LogColor( 0, 0.501961, 0, i );
  case COLOR_GREEN_YELLOW : return LogColor( 0.678431, 1, 0.184314, i );
  case COLOR_HONEYDEW : return LogColor( 0.941176, 1, 0.941176, i );
  case COLOR_HOT_PINK : return LogColor( 1, 0.411765, 0.705882, i );
  case COLOR_INDIAN_RED : return LogColor( 0.803922, 0.360784, 0.360784, i );
  case COLOR_IVORY : return LogColor( 1, 1, 0.941176, i );
  case COLOR_KHAKI : return LogColor( 0.941176, 0.901961, 0.54902, i );
  case COLOR_LAVENDER : return LogColor( 0.901961, 0.901961, 0.980392, i );
  case COLOR_LAVENDER_BLUSH : return LogColor( 1, 0.941176, 0.960784, i );
  case COLOR_LAWN_GREEN : return LogColor( 0.486275, 0.988235, 0, i );
  case COLOR_LEMON_CHIFFON : return LogColor( 1, 0.980392, 0.803922, i );
  case COLOR_LIGHT_BLUE : return LogColor( 0.678431, 0.847059, 0.901961, i );
  case COLOR_LIGHT_CORAL : return LogColor( 0.941176, 0.501961, 0.501961, i );
  case COLOR_LIGHT_CYAN : return LogColor( 0.878431, 1, 1, i );
  case COLOR_LIGHT_GOLDENROD : return LogColor( 0.933333, 0.866667, 0.509804, i );
  case COLOR_LIGHT_GOLDENROD_YELLOW : return LogColor( 0.980392, 0.980392, 0.823529, i );
  case COLOR_LIGHT_GRAY : return LogColor( 0.827451, 0.827451, 0.827451, i );
  case COLOR_LIGHT_GREEN : return LogColor( 0.564706, 0.933333, 0.564706, i );
  case COLOR_LIGHT_PINK : return LogColor( 1, 0.713725, 0.756863, i );
  case COLOR_LIGHT_SALMON : return LogColor( 1, 0.627451, 0.478431, i );
  case COLOR_LIGHT_SEA_GREEN : return LogColor( 0.12549, 0.698039, 0.666667, i );
  case COLOR_LIGHT_SKY_BLUE : return LogColor( 0.529412, 0.807843, 0.980392, i );
  case COLOR_LIGHT_SLATE_BLUE : return LogColor( 0.517647, 0.439216, 1, i );
  case COLOR_LIGHT_SLATE_GRAY : return LogColor( 0.466667, 0.533333, 0.6, i );
  case COLOR_LIGHT_STEEL_BLUE : return LogColor( 0.690196, 0.768627, 0.870588, i );
  case COLOR_LIGHT_YELLOW : return LogColor( 1, 1, 0.878431, i );
  case COLOR_LIME : return LogColor( 0, 1, 0, i );
  case COLOR_LIME_GREEN : return LogColor( 0.196078, 0.803922, 0.196078, i );
  case COLOR_LINEN : return LogColor( 0.980392, 0.941176, 0.901961, i );
  case COLOR_MAGENTA : return LogColor( 1, 0, 1, i );
  case COLOR_MAROON: return LogColor( 0.501961, 0, 0, i );
  case COLOR_MEDIUM_AQUAMARINE : return LogColor( 0.4, 0.803922, 0.666667, i );
  case COLOR_MEDIUM_BLUE : return LogColor( 0, 0, 0.803922, i );
  case COLOR_MEDIUM_ORCHID : return LogColor( 0.729412, 0.333333, 0.827451, i );
  case COLOR_MEDIUM_PURPLE : return LogColor( 0.576471, 0.439216, 0.858824, i );
  case COLOR_MEDIUM_SEA_GREEN : return LogColor( 0.235294, 0.701961, 0.443137, i );
  case COLOR_MEDIUM_SLATE_BLUE : return LogColor( 0.482353, 0.407843, 0.933333, i );
  case COLOR_MEDIUM_SPRING_GREEN : return LogColor( 0, 0.980392, 0.603922, i );
  case COLOR_MEDIUM_TURQUOISE : return LogColor( 0.282353, 0.819608, 0.8, i );
  case COLOR_MEDIUM_VIOLET_RED : return LogColor( 0.780392, 0.0823529, 0.521569, i );
  case COLOR_MIDNIGHT_BLUE : return LogColor( 0.0980392, 0.0980392, 0.439216, i );
  case COLOR_MINT_CREAM : return LogColor( 0.960784, 1, 0.980392, i );
  case COLOR_MISTY_ROSE : return LogColor( 1, 0.894118, 0.882353, i );
  case COLOR_MOCCASIN : return LogColor( 1, 0.894118, 0.709804, i );
  case COLOR_NAVAJO_WHITE : return LogColor( 1, 0.870588, 0.678431, i );
  case COLOR_NAVY : return LogColor( 0, 0, 0.501961, i );
  case COLOR_OLD_LACE : return LogColor( 0.992157, 0.960784, 0.901961, i );
  case COLOR_OLIVE: return LogColor( 0.501961, 0.501961, 0, i );
  case COLOR_OLIVE_DRAB : return LogColor( 0.419608, 0.556863, 0.137255, i );
  case COLOR_ORANGE : return LogColor( 1, 0.647059, 0, i );
  case COLOR_ORANGE_RED : return LogColor( 1, 0.270588, 0, i );
  case COLOR_ORCHID : return LogColor( 0.854902, 0.439216, 0.839216, i );
  case COLOR_PALE_GOLDENROD : return LogColor( 0.933333, 0.909804, 0.666667, i );
  case COLOR_PALE_GREEN : return LogColor( 0.596078, 0.984314, 0.596078, i );
  case COLOR_PALE_TURQUOISE : return LogColor( 0.686275, 0.933333, 0.933333, i );
  case COLOR_PALE_VIOLET_RED : return LogColor( 0.858824, 0.439216, 0.576471, i );
  case COLOR_PAPAYA_WHIP : return LogColor( 1, 0.937255, 0.835294, i );
  case COLOR_PEACH_PUFF : return LogColor( 1, 0.854902, 0.72549, i );
  case COLOR_PERU : return LogColor( 0.803922, 0.521569, 0.247059, i );
  case COLOR_PINK : return LogColor( 1, 0.752941, 0.796078, i );
  case COLOR_PLUM : return LogColor( 0.866667, 0.627451, 0.866667, i );
  case COLOR_POWDER_BLUE : return LogColor( 0.690196, 0.878431, 0.901961, i );
  case COLOR_PURPLE: return LogColor( 0.501961, 0, 0.501961, i );
  case COLOR_RED : return LogColor( 1, 0, 0, i );
  case COLOR_ROSY_BROWN : return LogColor( 0.737255, 0.560784, 0.560784, i );
  case COLOR_ROYAL_BLUE : return LogColor( 0.254902, 0.411765, 0.882353, i );
  case COLOR_SADDLE_BROWN : return LogColor( 0.545098, 0.270588, 0.0745098, i );
  case COLOR_SALMON : return LogColor( 0.980392, 0.501961, 0.447059, i );
  case COLOR_SANDY_BROWN : return LogColor( 0.956863, 0.643137, 0.376471, i );
  case COLOR_SEA_GREEN : return LogColor( 0.180392, 0.545098, 0.341176, i );
  case COLOR_SEASHELL : return LogColor( 1, 0.960784, 0.933333, i );
  case COLOR_SIENNA : return LogColor( 0.627451, 0.321569, 0.176471, i );
  case COLOR_SILVER: return LogColor( 0.752941, 0.752941, 0.752941, i );
  case COLOR_SKY_BLUE : return LogColor( 0.529412, 0.807843, 0.921569, i );
  case COLOR_SLATE_BLUE : return LogColor( 0.415686, 0.352941, 0.803922, i );
  case COLOR_SLATE_GRAY : return LogColor( 0.439216, 0.501961, 0.564706, i );
  case COLOR_SNOW : return LogColor( 1, 0.980392, 0.980392, i );
  case COLOR_SPRING_GREEN : return LogColor( 0, 1, 0.498039, i );
  case COLOR_STEEL_BLUE : return LogColor( 0.27451, 0.509804, 0.705882, i );
  case COLOR_TAN : return LogColor( 0.823529, 0.705882, 0.54902, i );
  case COLOR_TEAL : return LogColor( 0, 0.501961, 0.501961, i );
  case COLOR_THISTLE : return LogColor( 0.847059, 0.74902, 0.847059, i );
  case COLOR_TOMATO : return LogColor( 1, 0.388235, 0.278431, i );
  case COLOR_TURQUOISE : return LogColor( 0.25098, 0.878431, 0.815686, i );
  case COLOR_VIOLET : return LogColor( 0.933333, 0.509804, 0.933333, i );
  case COLOR_VIOLET_RED : return LogColor( 0.815686, 0.12549, 0.564706, i );
  case COLOR_WHEAT : return LogColor( 0.960784, 0.870588, 0.701961, i );
  case COLOR_WHITE: return LogColor( 1, 1, 1, i );
  case COLOR_WHITE_SMOKE : return LogColor( 0.960784, 0.960784, 0.960784, i );
  case COLOR_YELLOW: return LogColor( 1, 1, 0, i );
  case COLOR_YELLOW_GREEN : return LogColor( 0.603922, 0.803922, 0.196078, i );
  default: return LogColor( -1, -1, -1 );
  }
}

ostream& operator <<( ostream &os, LogColor l )
{
  os.precision( 4 );
  os.flags( ios::fixed );
  return ( os << "[" << l.m_r << "," << l.m_g << "," << l.m_b << "]" );
}


/************************ LoggerDraw ***************************/

LoggerDraw::LoggerDraw( ostream& os, bool active ) :
  m_color( LogColor::getColor( COLOR_ILLEGAL ) )
{
  m_cycle = -1;
  m_cycle_start = -2;
  m_depth = -1;
  m_mult = 1;
  m_shape = LOG_DRAW_ILLEGAL;
  strcpy( m_label, "" );
  m_os = &os;
  m_active = active;
}

void LoggerDraw::setSide( SideT side )
{
  if ( side == SIDE_RIGHT )
    m_mult = -1;
  else
    m_mult = 1;
}

void LoggerDraw::logLine( char* label,
			  VecPosition start, VecPosition end, int depth, 
			  ColorT color, double intensity )
{
  if ( isActive() ) {
    LogColor logColor = 
      ( color == COLOR_ILLEGAL ) ? m_color : LogColor::getColor( color, intensity );

    int logDepth = ( depth < 0 ) ? m_depth : depth;

    bool newLine = false;
    if ( m_cycle_start != m_cycle ||
	 strcmp( m_label, label ) ) {
      m_cycle_start = m_cycle;
      strcpy( m_label, label );
      newLine = true;
      *m_os << endl << m_cycle << ": \"" << m_label << "\" ";
    }
    
    m_os->precision( 3 );
    m_os->flags( ios::fixed );

    if ( newLine || m_shape != LOG_DRAW_LINE || m_color != logColor ||
	 m_depth != logDepth ) {
      m_shape = LOG_DRAW_LINE;
      m_depth = logDepth;
      m_color = logColor;
      *m_os << "LINE " << m_depth << " " << m_color << " ";
    }
    
    *m_os << start * m_mult << " " << end * m_mult << "; ";
  }
}

void LoggerDraw::logText( const char* label,
			  VecPosition pos, const char* text, int depth,
			  ColorT color, double intensity )
{
  if ( isActive() ) {
    LogColor logColor = 
      ( color == COLOR_ILLEGAL ) ? m_color : LogColor::getColor( color, intensity );

    int logDepth = ( depth < 0 ) ? m_depth : depth;

    bool newLine = false;
    if ( m_cycle_start != m_cycle ||
	 strcmp( m_label, label ) ) {
      m_cycle_start = m_cycle;
      strcpy( m_label, label );
      newLine = true;
      *m_os << endl << m_cycle << ": \"" << m_label << "\" ";
    }
    
    m_os->precision( 3 );
    m_os->flags( ios::fixed );

    if ( newLine || m_shape != LOG_DRAW_TEXT || m_color != logColor ||
	 m_depth != logDepth ) {
      m_shape = LOG_DRAW_TEXT;
      m_depth = logDepth;
      m_color = logColor;
      *m_os << "TEXT " << m_depth << " " << m_color << " ";
    }
    
    *m_os << pos * m_mult << " \"" << escape( text ) << "\"; ";
  }
}

void LoggerDraw::logCircle( char* label,
			    VecPosition center, double radius,
			    int depth, bool filled, 
			    ColorT color, double intensity )
{
  if ( isActive() ) {
    LogColor logColor = 
      ( color == COLOR_ILLEGAL ) ? m_color : LogColor::getColor( color, intensity );

    int logDepth = ( depth < 0 ) ? m_depth : depth;

    bool newLine = false;
    if ( m_cycle_start != m_cycle ||
	 strcmp( m_label, label ) ) {
      m_cycle_start = m_cycle;
      strcpy( m_label, label );
      newLine = true;
      *m_os << endl << m_cycle << ": \"" << m_label << "\" ";
    }
    
    m_os->precision( 3 );
    m_os->flags( ios::fixed );

    LogDrawT testShape = 
      ( filled ) ? LOG_DRAW_CIRCLE_FILLED : LOG_DRAW_CIRCLE;
    if ( newLine || m_shape != testShape || m_color != logColor ||
	 m_depth != logDepth ) {
      m_shape = testShape;
      m_color = logColor;
      m_depth = logDepth;
      *m_os << "CIRC" 
	    << ( ( filled ) ? " FILL " : " " )
	    << m_depth << " " << m_color << " ";
    }
    
    *m_os << center * m_mult << " " << radius << "; ";
  }  
}
  
void LoggerDraw::logRectangle( char* label, 
			       VecPosition topLeft, VecPosition bottomRight, 
			       int depth, bool filled, 
			       ColorT color, double intensity )
{
  if ( isActive() ) {
    LogColor logColor = 
      ( color == COLOR_ILLEGAL ) ? m_color : LogColor::getColor( color, intensity );

    int logDepth = ( depth < 0 ) ? m_depth : depth;

    bool newLine = false;
    if ( m_cycle_start != m_cycle ||
	 strcmp( m_label, label ) ) {
      m_cycle_start = m_cycle;
      strcpy( m_label, label );
      newLine = true;
      *m_os << endl << m_cycle << ": \"" << m_label << "\" ";
    }
    
    m_os->precision( 3 );
    m_os->flags( ios::fixed );

    LogDrawT testShape = 
      ( filled ) ? LOG_DRAW_RECTANGLE_FILLED : LOG_DRAW_RECTANGLE;
    if ( newLine || m_shape != testShape || m_color != logColor ||
	 m_depth != logDepth ) {
      m_shape = testShape;
      m_color = logColor;
      m_depth = logDepth;
      *m_os << "RECT" 
	    << ( ( filled ) ? " FILL " : " " )
	    << m_depth << " " << m_color << " ";
    }
    
    *m_os << topLeft * m_mult << " " << bottomRight * m_mult << "; ";
  }  
}

void LoggerDraw::setTime( int cycle )
{
  m_cycle = cycle;
}

void LoggerDraw::setActive( bool active )
{
  m_active = active;
}

bool LoggerDraw::isActive()
{
  return m_active;
}

void LoggerDraw::setOutputStream( ostream& os )
{
  m_os = &os;
}
ostream& LoggerDraw::getOutputStream()
{
  return *m_os;
}

char* LoggerDraw::escape( const char* str )
{
  static char str2[ MAX_TEXT ];

  if ( str == NULL )
    return NULL;

  int j = 0;
  for ( int i = 0; i < MAX_TEXT; i++ ) {
    switch ( str[ i ] ) {
    case '\\':
      str2[ j++ ] = '\\';
      str2[ j++ ] = '\\';
      break;
    case '"':
      str2[ j++ ] = '\\';
      str2[ j++ ] = '"';
      break;
    case '\n':
      str2[ j++ ] = '\\';
      str2[ j++ ] = 'n';
      break;      
    default:
      str2[ j++ ] = str[ i ];
      break;
    }
    if ( i >= MAX_TEXT || j >= MAX_TEXT ||
	 str[ i ] == '\0' )
      break;
  }

  return str2;
}


// Testing purposes
// int main()
// {
//   LoggerDraw LogDraw;
//   LogDraw.setActive( true );
//   LogDraw.logCircle( "test", VecPosition( 4, 4 ), 5.0, true, COLOR_RED );
//   LogDraw.logCircle( "test2", VecPosition( -7.66, 5.2 ), 0, true, COLOR_RED );
// }
