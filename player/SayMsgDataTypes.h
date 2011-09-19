/*
    Coachable Agent communication encoding and decoding library
    Copyright (C) 2004, John Davin, Carnegie Mellon University

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

/*
 * DataTypes.h - functional class (no storage or variables) that 
 *  provides conversion methods to convert from datatypes to encoded
 *  characters (encoding) and vice versa (decoding)
 *
 * We also have a "bool bound(float|int *Datatype)" method which takes a pointer
 *  to a variable and bounds the value according to the min and max values for that 
 *  datatype. Returns true if the value was changed, false o/w. 
 *
 *
 * Creation Date: 11/18/03
 * Author: John Davin
 *
 *
 */

#ifndef SAY_MSG_DATATYPES_H
#define SAY_MSG_DATATYPES_H

#include <iostream>
#include <assert.h>

#define NUMCHARS 73 // validchars has 73 chars (so max array index is NUMCHARS-1)

using namespace std;

const char validchars[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ().+-*/?<>_";

extern short char2numMap[];

/* 
 * All methods must be static so that functions can be called without 
 * class instantiations. 
 *
 */
class DataTypes {
 public: 

  typedef unsigned short MsgTypeID_t;
  typedef float X_t;
  typedef float Y_t;
  typedef float dX_t;
  typedef float dY_t;
  typedef unsigned short Cycleno_t;
  typedef unsigned short Playernum_t;

  /*
   * returns the index into the validchars array for char c 
   * Returns -1 on error (eg, char c is not in validchars)
   */
  static short get_num_from_char(char c){
    /* if the char2numMap is not computed yet, then we must do so now */
    /* (this part will only be run once) */
    if(char2numMap[0] == -2){
      
      for(int i=0; i<256; i++)
	char2numMap[i] = -1;
      
      for(int i=0; i<NUMCHARS; i++){
	char2numMap[(int)validchars[i]] = i;
      }
    }
    
    return char2numMap[(int)c];
  }
  
  

  /* helper function for SayMsgTypes::getEncodedStr(): 
   * Given i, an index into validchars array, returns the appropriate char. 
   * If i is out of bounds, rounds to nearest bound. 
   */
  static char get_printable_char(float i){
    // cast i to integer using floor (standard C casting) as defined in specification
    int index = (int)i;
    if(index < 0){
      cerr << "[get_printable_char]: warning: "<<index<<" was below bounds"<<endl;
      //#warning Remove assert(0) for non-debug compiles
      //assert(0);
      return validchars[0];
    }
    else if(index >= NUMCHARS){
      cerr << "[get_printable_char]: warning: "<<index<<" was above bounds"<<endl;
      //#warning Remove assert(0) for non-debug compiles
      //assert(0);
      return validchars[NUMCHARS-1];
    }
    else { // index is within bounds
      
      return validchars[index];
    }
    
  }


  /*
   * Range:  [0,29]
   */
  class MsgTypeID {
  public:
    static char getEncoding(MsgTypeID_t id){
      return get_printable_char(id);
    }

    static MsgTypeID_t getDecoding(char encoded){
      return get_num_from_char(encoded);
    }
  };

  /*
   * Range: [-53, 53)
   */
  class X {
  public:
    static char getEncoding(X_t x){
      return get_printable_char((x+53)/106 * NUMCHARS);
    }

    static X_t getDecoding(char encoded){
      return ((float)get_num_from_char(encoded) / NUMCHARS * 106.) - 53.;
    }

    /* 
     * call as: DataTypes::X::bound(&X)
     * Returns: true if X was modified, false o/w. 
     */
    static bool bound(X_t *X){
      if(*X < -53.){
	*X = -53.;
	return true;
      }
      else if(*X >= 53.){
	*X = 52.999;
	return true;
      }
      else return false;
    }
  };

  /*
   * Range: [-34, 34)
   */
  class Y {
  public:
    static char getEncoding(Y_t y){
      return get_printable_char( (y+34)/68 * NUMCHARS );
    }

    static Y_t getDecoding(char encoded){
      return ( (float)get_num_from_char(encoded) / NUMCHARS * 68.) - 34.;
    }

    static bool bound(Y_t *Y){
      if(*Y < -34.){
	*Y = -34.;
	return true;
      }
      else if(*Y >= 34.){
	*Y = 33.999;
	return true;
      }
      else return false;
    }
  };

  /*
   * Range: [-2.7,2.7)
   */
  class dX { // parameter for ball velocity (delta x)
  public:
    static char getEncoding(dX_t dx){
      return get_printable_char((dx+2.7)/5.4 * NUMCHARS);
    }

    static dX_t getDecoding(char encoded){
      return ((float)get_num_from_char(encoded) / NUMCHARS * 5.4) - 2.7;
    }

    static bool bound(dX_t *DX){
      if(*DX < -2.7){
	*DX = -2.7;
	return true;
      }
      else if(*DX >= 2.7){
	*DX = 2.699;
	return true;
      }
      else return false;
    }
  };

  /*
   * Range: [-2.7,2.7)
   */
  class dY {
  public:
    static char getEncoding(dY_t dy){
      return get_printable_char( (dy+2.7)/5.4 * NUMCHARS );
    }

    static dY_t getDecoding(char encoded){
      return ( (float)get_num_from_char(encoded) / NUMCHARS * 5.4) - 2.7;
    }

    static bool bound(dY_t *DX){
      if(*DX < -2.7){
	*DX = -2.7;
	return true;
      }
      else if(*DX >= 2.7){
	*DX = 2.699;
	return true;
      }
      else return false;
    }
  };

  /*
   * Range: [0, 72)
   */
  class Cycleno {
  public:
    static char getEncoding(Cycleno_t cycle){
      return get_printable_char(cycle);
    }

    static Cycleno_t getDecoding(char encoded){
      return get_num_from_char(encoded);
    }

    static bool bound(int *Cycle){
      if(*Cycle < 0){
	*Cycle = 0;
	return true;
      }
      else if(*Cycle >= 72){
	*Cycle = 71;
	return true;
      }
      else return false;
    }
  };

  /*
   * Range: [0,11]
   */
  class Playernum {
  public:
    static char getEncoding(Playernum_t pnum){
      return get_printable_char(pnum);
    }

    static Playernum_t getDecoding(char encoded){
      return get_num_from_char(encoded);
    }

    static bool bound(int *Playernum){
      if(*Playernum < 0){
	*Playernum = 0;
	return true;
      }
      else if(*Playernum > 11){
	*Playernum = 11;
	return true;
      }
      else return false;
    }
  };

};


#endif


