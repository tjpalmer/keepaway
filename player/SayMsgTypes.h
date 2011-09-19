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
 * SayMsgTypes.h - Defines message types as described by the coachable agents
 *  communication standard. 
 *
 *
 * Creation Date: 11/18/03
 * Author: John Davin
 *
 * USAGE: 
 *  The user of the say message library must subclass the SayMsgTypes classes
 *  to define the virtual function process(). 
 *
 *
 */

#ifndef SAY_MSG_TYPES_H
#define SAY_MSG_TYPES_H

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


#include "SayMsgIDs.h"
#include "SayMsgDataTypes.h"


/*
 * Abstract base class for Say message units (eg, OurPos, WantPass, etc)
 */
class SayMsgTypes {

 protected:
  int SenderPlayerNum; 
  // holds the playernum of the sender. only needs to be set when decoding msg's



 public:
  virtual ~SayMsgTypes(){}

  /**** Virtual functions defined in the SayMsgTypes subclasses *****
   ****** (OurPos, WantPass, etc) *****/

  /*
   * Return number of characters that this msg unit requires. 
   * Used by SayMsgEncoder::add to determine if we have room for this msg unit in current msg.
   * Also used by SayMsgDecoder to determine how many characters to read for each msg type.
   */
  virtual unsigned int getCost() = 0;
   
  /*    
   * Return name of this msg unit. 
   */
  virtual string getName() = 0;

  /*
   * Return encoded string representation of the msg type. 
   */
  virtual string getEncodedStr() = 0;

  /*
   * Given an encoded string of this msg type's arguments, parse the arguments 
   * to initialize our private variables
   * Return true on success, or false if string could not be parsed (eg, not long enough)
   * This should *only* be called by SayMsgDecoder
   */
  virtual bool parseStringArgs(string str) = 0;



  /**** Virtual function defined by library user in SayMsgUnit subclasses (eg, MyOurPass) ***/
  /*
   * The user should redefine this function when they define subclasses 
   * of the SayMsgUnit classes. If they choose not to 
   */
  virtual void process() {};


  /**** Non-virtual functions (defined for all subclasses): *****/
  void setPlayernum(int pnum){ SenderPlayerNum = pnum; }
  int  getPlayernum() { return SenderPlayerNum; }


};



/****************************
 * Message type subclasses: 
 ****************************/


class OurPos : virtual public SayMsgTypes {
 protected: 
  float X, Y;

 public:
  ~OurPos(){}
  OurPos() : X(0.),Y(0.)
    {}
  OurPos(float x, float y) : X(x), Y(y) 
    {}

  unsigned int getCost() { return 3; }
  string getName(){ return "OurPos"; }

  string getEncodedStr(){
    string encoding("");
    encoding += DataTypes::MsgTypeID::getEncoding(OUR_POS_ID);
    encoding += DataTypes::X::getEncoding(X);
    encoding += DataTypes::Y::getEncoding(Y);

    //    cout << "[OurPos]: encoded as: "<<encoding<<endl;
    return encoding;
  }

   /*
    * Given a string representing this msg type's arguments, parse the arguments 
    * to initialize our private variables
    * Return true on success, or false if string could not be parsed (eg, not long enough)
    */
  bool parseStringArgs(string str){
    if(str.size() != getCost()) // not enough chars
      return false;

    X = DataTypes::X::getDecoding(str[1]);
    Y = DataTypes::Y::getDecoding(str[2]);
    return true;
  }

};


class BallInfo : virtual public SayMsgTypes {
 protected:
  float X, Y, dX, dY;
  unsigned short cycleno;

 public:
  ~BallInfo(){}
  BallInfo() : X(0.),Y(0.),dX(0.),dY(0.),cycleno(0)
    {}
  BallInfo(float x, float y, float dx, float dy, 
	  unsigned short cycle) : X(x), Y(y), dX(dx), dY(dy), cycleno(cycle)
    {}

  unsigned int getCost() { return 6; }
  string getName(){ return "BallInfo"; }

  string getEncodedStr(){
    string encoding("");
    encoding += DataTypes::MsgTypeID::getEncoding(BALL_INFO_ID);
    encoding += DataTypes::X::getEncoding(X);
    encoding += DataTypes::Y::getEncoding(Y);
    encoding += DataTypes::dX::getEncoding(dX);
    encoding += DataTypes::dY::getEncoding(dY);
    encoding += DataTypes::Cycleno::getEncoding(cycleno);

    return encoding;
  }

   /*
    * Given a string representing this msg type's arguments, parse the arguments
    * to initialize our private variables
    * Return true on success, or false if string could not be parsed (eg, not long enough)
    */
  bool parseStringArgs(string str){
    if(str.size() != getCost()) // not enough chars
      return false;

    X = DataTypes::X::getDecoding(str[1]);
    Y = DataTypes::Y::getDecoding(str[2]);
    dX = DataTypes::dX::getDecoding(str[3]);
    dY = DataTypes::dY::getDecoding(str[4]);
    cycleno = DataTypes::Cycleno::getDecoding(str[5]);
    return true;
  }

};


class WeHaveBall : virtual public SayMsgTypes {
 protected: 
  unsigned short playernum;

 public: 
  ~WeHaveBall(){}
  WeHaveBall() : playernum(0)
    {}
  WeHaveBall(unsigned short pnum) : playernum(pnum) 
    {}

  unsigned int getCost() { return 2; }
  string getName(){ return "WeHaveBall"; }

  string getEncodedStr(){
    string encoding("");
    encoding += DataTypes::MsgTypeID::getEncoding(WE_HAVE_BALL_ID);
    encoding += DataTypes::Playernum::getEncoding(playernum);

    return encoding;
  }

  bool parseStringArgs(string str){
    if(str.size() != getCost())
      return false;

    playernum = DataTypes::Playernum::getDecoding(str[1]);
    return true;
  }

};



class OppHasBall : virtual public SayMsgTypes {
 protected: 
  unsigned short playernum;

 public: 
  ~OppHasBall(){}
  OppHasBall() : playernum(0)
    {}  
  OppHasBall(unsigned short pnum) : playernum(pnum) 
    {}

  unsigned int getCost() { return 2; }
  string getName(){ return "OppHasBall"; }

  string getEncodedStr(){
    string encoding("");
    encoding += DataTypes::MsgTypeID::getEncoding(OPP_HAS_BALL_ID);
    encoding += DataTypes::Playernum::getEncoding(playernum);

    return encoding;
  }

  bool parseStringArgs(string str){
    if(str.size() != getCost()) 
      return false;

    playernum = DataTypes::Playernum::getDecoding(str[1]);
    return true;
  }

};


class PassToPlayer  : virtual public SayMsgTypes {
 protected: 
  unsigned short playernum; // the player we're passing to

 public: 
  ~PassToPlayer(){}
  PassToPlayer() : playernum(0)
    {}  
  PassToPlayer(unsigned short pnum) : playernum(pnum) 
    {}

  unsigned int getCost() { return 2; }
  string getName(){ return "PassToPlayer"; }

  string getEncodedStr(){
    string encoding("");
    encoding += DataTypes::MsgTypeID::getEncoding(PASS_TO_PLAYER_ID);
    encoding += DataTypes::Playernum::getEncoding(playernum);

    return encoding;
  }

  bool parseStringArgs(string str){
    if(str.size() != getCost()) 
      return false;

    playernum = DataTypes::Playernum::getDecoding(str[1]);
    return true;
  }

};

class PassToCoord : virtual public SayMsgTypes {
 protected: 
  float X, Y;

 public:
  ~PassToCoord(){}
  PassToCoord() : X(0.),Y(0.)
    {}
  PassToCoord(float x, float y) : X(x), Y(y) 
    {}

  unsigned int getCost() { return 3; }
  string getName(){ return "PassToCoord"; }

  string getEncodedStr(){
    string encoding("");
    encoding += DataTypes::MsgTypeID::getEncoding(PASS_TO_COORD_ID);
    encoding += DataTypes::X::getEncoding(X);
    encoding += DataTypes::Y::getEncoding(Y);

    return encoding;
  }

   /*
    * Given a string representing this msg type's arguments, parse the arguments 
    * to initialize our private variables
    * Return true on success, or false if string could not be parsed (eg, not long enough)
    */
  bool parseStringArgs(string str){
    if(str.size() != getCost()) // not enough chars
      return false;

    X = DataTypes::X::getDecoding(str[1]);
    Y = DataTypes::Y::getDecoding(str[2]);
    return true;
  }

};


class WantPass : virtual public SayMsgTypes {
 protected: 
  // none

 public: 
  ~WantPass(){}
  WantPass() {}

  unsigned int getCost() { return 1; }
  string getName(){ return "WantPass"; }

  string getEncodedStr(){
    string encoding("");
    encoding += DataTypes::MsgTypeID::getEncoding(WANT_PASS_ID);

    return encoding;
  }

  bool parseStringArgs(string str){
    if(str.size() != getCost()) // str should always be 0 chars
      return false;

    /* we don't have any arguments, so do nothing */
    return true;
  }

};


class OppPos : virtual public SayMsgTypes {
 protected: 
  float X, Y;
  unsigned short playernum;
  unsigned short cycleno;

 public:
  ~OppPos(){}
  OppPos() 
    : X(0.),Y(0.),playernum(0),cycleno(0)  { }
  OppPos(unsigned short pnum, float x, float y, unsigned short cyclen) 
     : X(x),Y(y),playernum(pnum),cycleno(cyclen)   
    {}


  unsigned int getCost() { return 4; }
  string getName(){ return "OppPos"; } 

  string getEncodedStr(){
    if(playernum < 1 || playernum > 11)
      cerr <<"TeammatePos: ERROR: playernum "<<playernum<<" invalid"<<endl;

    string encoding("");
    encoding += DataTypes::MsgTypeID::getEncoding(OPP_POS_ID+playernum-1);
    encoding += DataTypes::X::getEncoding(X);
    encoding += DataTypes::Y::getEncoding(Y);
    encoding += DataTypes::Cycleno::getEncoding(cycleno);

    return encoding;
  }

   /*
    * Given a string representing this msg type's arguments, parse the arguments 
    * to initialize our private variables
    * Return true on success, or false if string could not be parsed (eg, not long enough)
    */
  bool parseStringArgs(string str){
    if(str.size() != getCost()) // not enough chars
      return false;

    playernum = DataTypes::MsgTypeID::getDecoding(str[0])-OPP_POS_ID+1;
    X = DataTypes::X::getDecoding(str[1]);
    Y = DataTypes::Y::getDecoding(str[2]);
    cycleno = DataTypes::Cycleno::getDecoding(str[3]);
    return true;
  }

};


class TeammatePos : virtual public SayMsgTypes {
 protected: 
  float X, Y;
  unsigned short playernum;
  unsigned short cycleno;

 public:
  ~TeammatePos(){}
  TeammatePos() 
    : X(0.),Y(0.),playernum(0),cycleno(0)  { }
  TeammatePos(unsigned short pnum, float x, float y, unsigned short cyclen) 
     : X(x),Y(y),playernum(pnum),cycleno(cyclen)   
    {}


  unsigned int getCost() { return 4; }
  string getName(){ return "TeammatePos"; } 

  string getEncodedStr(){
    if(playernum < 1 || playernum > 11)
      cerr <<"TeammatePos: ERROR: playernum "<<playernum<<" invalid"<<endl;

    string encoding("");
    encoding += DataTypes::MsgTypeID::getEncoding(TEAMMATE_POS_ID+playernum-1);
    encoding += DataTypes::X::getEncoding(X);
    encoding += DataTypes::Y::getEncoding(Y);
    encoding += DataTypes::Cycleno::getEncoding(cycleno);

    return encoding;
  }

   /*
    * Given a string representing this msg type's arguments, parse the arguments 
    * to initialize our private variables
    * Return true on success, or false if string could not be parsed (eg, not long enough)
    */
  bool parseStringArgs(string str){
    if(str.size() != getCost()) // not enough chars
      return false;

    playernum = DataTypes::MsgTypeID::getDecoding(str[0])-TEAMMATE_POS_ID+1;
    X = DataTypes::X::getDecoding(str[1]);
    Y = DataTypes::Y::getDecoding(str[2]);
    cycleno = DataTypes::Cycleno::getDecoding(str[3]);
    return true;
  }

};





#endif

