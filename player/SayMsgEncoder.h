/*
Copyright (c) 2004, Gregory Kuhlmann, Peter Stone
University of Texas at Austin
All right reserved

Based On:

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
 * SayMsgEncoder.h - functional class that is used to encode a coachable agent 
 *   say message to be sent to the server. 
 *
 *
 * Creation Date: 11/18/03
 * Author: John Davin
 *
 *************************************
 * USAGE: 
 *
 * To encode a message you will do something like this: 
 * SayMsgEncoder *myencoder = new SayMsgEncoder();
 * myencoder->add( new OurPos(15.,-15.) ); 
 * myencoder->add( new WantPass() ); // add any other message units that you want.
 * String str = myencoder->getEncodedStr();
 * // now send str to the server using your own player's code to do so
 * 
 * myencoder->clear(); // clears the SayMsgEncoder so you can use it again.
 ***************************************
 *
 * Note: the DataTypes.h file has static convenience functions that you may wish 
 *   to use to make sure your data are within bounds (ie, X,Y position for OurPos).
 * You are not required to check bounds because the SayMsgEncoder will 
 *   automatically cap any values that are out of range, but the printed 
 *   warning does not say what message type or data type was rounded. So you 
 *   may find debugging easier if you check bounds on your data before sending 
 *   it to a message type like OurPos. 
 *
 **************************************
 * Example: 
 *  float X = // get a value from your world model;
 *  float Y = // world model.
 *  bool changed = DataTypes::X::bound(&X); 
 *  changed     |= DataTypes::Y::bound(&Y);
 *   // the bound functions will set X or Y to values that are within bounds if necessary, 
 *   // and return true if the values were changed.
 *  if(changed) cout << "Warning: an X or Y value was out of bounds"<<endl;
 ***************************************
 *
 * Note on memory usage: 
 *   SayMsgEncoder assumes responsibility of the dynamically allocated objects
 *   that you pass in. ie, you allocate with: encoder->add(new OurPos())
 *   and SayMsgEncoder will delete that object when you do encoder->clear().
 *   Therefore, you should never pass in references to locally allocated
 *   objects (eg, BAD: encoder->add( &OurPos()); ) and also should not use
 *   the objects after calling clear (eg, BAD: encoder->add( tmp = new OurPos()),
 *   encoder->clear(); tmp->getName();). 
 *
 */

#ifndef SAY_MSG_ENCODER_H
#define SAY_MSG_ENCODER_H


#include "SayMsgTypes.h"
#include <vector>
using namespace std;


class SayMsgEncoder {

 private:
  vector<SayMsgTypes*> units; // stores the SayMsgTypes for this say message
  unsigned int maxsize;
  unsigned int currentsize; // current size used by msg's in units vector


 public: 
  /*
   * create a SayMsgEncoder class with maxchars as the max message len. 
   * (defaults to 10 so you don't need to specify it). 
   */
  SayMsgEncoder(unsigned int maxchars = 10) 
    :maxsize(maxchars) {
    currentsize = 0;
  }
  ~SayMsgEncoder(){ 
    clear(); // clear storage
  }

  /*
   * Add a SayMsgTypes to storage
   * Enforces msg length restriction. 
   * Returns false if add failed (eg, if SayMsgTypes cost exceeds available space). 
   */
  bool add(SayMsgTypes *u){
    if(u->getCost() + currentsize > maxsize)
      return false;
    
    currentsize += u->getCost();
    units.push_back(u);

    return true;
  }

  /*
   * Return the encoded say string for the SayMsgTypes currently in our storage
   *
   */
  string getEncodedStr(){
    string encoding("");

    for(unsigned int i=0; i<units.size(); i++)
      encoding += units[i]->getEncodedStr();

    return encoding;
  }

  /*
   * Returns the current size
   */
  unsigned int getSize(){
    return currentsize;
  }

  /*
   * Returns the max size
   */
  unsigned int getMaxSize(){
    return maxsize;
  }


  /*
   * clear the storage so that we can start encoding a new message. 
   *
   */
  void clear(){
    /* free the SayMsgTypes objects */
    for(unsigned int i=0; i<units.size(); i++)
      delete units[i];
    
    units.clear();
    currentsize = 0;
  }

};


#endif

