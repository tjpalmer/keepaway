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

#ifndef _WORLD_MODEL_SAY_MSG_FACTORY_
#define _WORLD_MODEL_SAY_MSG_FACTORY_

#include "SayMsgFactory.h"
#include "WorldModel.h"
#include "WorldModelSayMsgTypes.h"

extern short char2numMap[];

class WorldModelSayMsgFactory : public SayMsgFactory 
{
 private:
  WorldModel *WM;

 public:
  WorldModelSayMsgFactory( WorldModel *wm ) : SayMsgFactory() { 
    WM = wm; 
    char2numMap[0] = -2;
  }
  
  OurPos *getOurPos(){ return new WMOurPos( WM ); }

  BallInfo *getBallInfo(){ return new WMBallInfo( WM ); }

  WeHaveBall *getWeHaveBall(){ return new WMWeHaveBall( WM ); }

  OppHasBall *getOppHasBall(){ return new WMOppHasBall( WM ); }

  PassToPlayer *getPassToPlayer(){ return new WMPassToPlayer( WM ); }

  PassToCoord *getPassToCoord(){ return new WMPassToCoord( WM ); }

  WantPass *getWantPass(){ return new WMWantPass( WM ); }

  OppPos *getOppPos(){ return new WMOppPos( WM ); }

  TeammatePos *getTeammatePos(){ return new WMTeammatePos( WM ); }

} ;

#endif


