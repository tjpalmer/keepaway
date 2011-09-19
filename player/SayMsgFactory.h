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
 * SayMsgFactory.h - Abstract base class that SayMsgDecoder uses  
 *   to get message type subclasses. 
 *
 * Creation Date: 11/18/03
 * Author: John Davin
 *
 * USAGE:  
 *   The user of the SayMsgDecoder library should define a subclass of SayMsgFactory
 *   that (re)defines each of the functions below to return a pointer to their own 
 *   message type objects (eg, for getNewOurPos, the user should return a new MyOurPos, 
 *   where MyOurPos is the name of a user-written subclass of OurPos. 
 *
 *
 *
 */


#ifndef SAY_MSG_FACTORY_H
#define SAY_MSG_FACTORY_H


#include "SayMsgTypes.h"


/*
 * By default, these functions return new pointers to the stardard
 * SayMsgTypes defined in SayMsgTypes.h. Therefore, if the user does 
 * not redefine any of the functions in this class to return their own objects
 * then these objects will be used (with an empty process() method). 
 */
class SayMsgFactory {

 public:
  virtual OurPos *getOurPos(){ return new OurPos(); }

  virtual BallInfo *getBallInfo(){ return new BallInfo(); }

  virtual WeHaveBall *getWeHaveBall(){ return new WeHaveBall(); }

  virtual OppHasBall *getOppHasBall(){ return new OppHasBall(); }

  virtual PassToPlayer *getPassToPlayer(){ return new PassToPlayer(); }

  virtual PassToCoord *getPassToCoord(){ return new PassToCoord(); }

  virtual WantPass *getWantPass(){ return new WantPass(); }

  virtual OppPos *getOppPos(){ return new OppPos(); }

  virtual TeammatePos *getTeammatePos(){ return new TeammatePos(); }


};



#endif

