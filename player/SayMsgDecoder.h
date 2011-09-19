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
 * SayMsgDecoder.h - functional class that is used to decode a coachable agent 
 *   say message into message types that can be incorporated into the world model. 
 *
 *
 * Creation Date: 11/18/03
 * Author: John Davin
 *
 * USAGE: 
 *
 * 1) Write subclasses for the msg type classes in SayMsgTypes and define process() functions
 *   that incorporate the information into your world model (or do something else with the data). 
 * 2) Write a subclass of SayMsgFactory (eg, MySayMsgFactory) that defines the SayMsgFactory
 *    functions to return instances of your msg type subclasses that you defined in step 1. 
 * 3) To decode a message: 
 * 
 * string serverSayMsg = // you get this from the server
 * int playernum =  // you also get this with the say msg
 * SayMsgFactory *msgfactory = new MySayMsgFactory();
 * SayMsgDecoder *decoder = new SayMsgDecoder(msgfactory);
 * bool success = decoder->decodeStr(serverSayMsg, playernum);
 * if(!success) return;
 * SayMsgDecoder::DecodedMsgIterator iter = decoder->getMsgIterator();
 * for( ; iter != decoder->getMsgIteratorEnd(); iter++){
 *   SayMsgTypes *curunit = *iter;
 *   curunit->process();
 *   // calls the process function that you defined for the current SayMsgType 
 *   
 * Note: Each time you call decodeStr( ), it will *erase* the previous message units. 
 *   So if you wish, you can use the same SayMsgDecoder instance to decode all messages
 */


#ifndef SAY_MSG_DECODER_H
#define SAY_MSG_DECODER_H


#include <vector>
#include <pthread.h>
using namespace std;
#include "SayMsgFactory.h"
#include "SayMsgDataTypes.h"



class SayMsgDecoder {

 private: 
  vector<SayMsgTypes*> units; // stores the SayMsgTypes for this say message
  SayMsgFactory *msgfactory; // SayMsgFactory used to get new msg type objects


 public: 
  typedef vector<SayMsgTypes*>::const_iterator DecodedMsgIterator;


  /*
   * create a SayMsgDecoder class 
   * using the msgfactory to get the user's subclassed message types
   */
  SayMsgDecoder(SayMsgFactory *msgfact)
    :msgfactory(msgfact) {
  }
  ~SayMsgDecoder(){
    clearStorage();
  }

  /* 
   * Decode the specified string and put its SayMsgTypes into our vector storage. 
   * Clears the storage vector before decoding the specified string. 
   * playernum specifies the player number of the sender
   * Returns true if decoding succeeded; false otherwise. 
   */
  bool decodeStr(string str, int playernum){
    unsigned int id;
    SayMsgTypes *msgunit;

    // clear storage (and free the objects)
    clearStorage();

    while(!str.empty()){

      // get the message id character and convert to int
      id = DataTypes::MsgTypeID::getDecoding(str[0]);
      
      // get a user subclassed SayMsgTypes object from the msgfactory.
      // if the user has not implemented a message type, it will return NULL
      // and we will use a standard SayMsgTypes object (process() function empty)

      if(id == OUR_POS_ID)
	msgunit = msgfactory->getOurPos();
      else if(id == BALL_INFO_ID)
	msgunit = msgfactory->getBallInfo();
      else if(id == WE_HAVE_BALL_ID)
	msgunit = msgfactory->getWeHaveBall();
      else if(id == OPP_HAS_BALL_ID)
	msgunit = msgfactory->getOppHasBall();
      else if(id == PASS_TO_PLAYER_ID)
	msgunit = msgfactory->getPassToPlayer();
      else if(id == PASS_TO_COORD_ID)
	msgunit = msgfactory->getPassToCoord();
      else if(id == WANT_PASS_ID)
	msgunit = msgfactory->getWantPass();
      else if(id >= OPP_POS_ID && id <= OPP_POS_ID+10)
	msgunit = msgfactory->getOppPos();
      else if(id >= TEAMMATE_POS_ID && id <= TEAMMATE_POS_ID+10)
	msgunit = msgfactory->getTeammatePos();
      else{
	cerr << "[SayMsgDecoder]: error: received unknown message type id! "
	     <<id<<" on char "<<str[0]<<endl;
	return false;
      }

      // initialize the msgunit with its parameters from the string
      bool parsed = msgunit->parseStringArgs( str.substr(0,msgunit->getCost()) );
      if(!parsed){ delete msgunit; return false; }
      msgunit->setPlayernum(playernum);

      // add the msgunit to our storage: 
      units.push_back(msgunit);

      // skip ahead by the number of chars this msgunit used
      str = str.substr(msgunit->getCost()); 
    }

    return true;
  }

  /*
   * Returns an iterator to the start of the storage vector
   */
  DecodedMsgIterator getMsgIterator(){
    return units.begin();
  }

  /*
   * Returns iterator pointing to the end of the storage vector
   */
  DecodedMsgIterator getMsgIteratorEnd(){
    return units.end();
  }


 private:
  void clearStorage(){
    for(unsigned int i=0; i<units.size(); i++){
      delete units[i];
    }
    units.clear();
  }

};


#endif

