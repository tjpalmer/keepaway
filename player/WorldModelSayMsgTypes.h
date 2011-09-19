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

#ifndef _WORLD_MODEL_SAY_MSG_TYPES_
#define _WORLD_MODEL_SAY_MSG_TYPES_

#include "WorldModel.h"
#include "SayMsgTypes.h"

class WMOurPos : public OurPos 
{
 private:
  WorldModel *WM;

 public:   
  WMOurPos( WorldModel *wm );
  void process();
} ;

class WMBallInfo : public BallInfo
{
 private:
  WorldModel *WM;

 public:   
  WMBallInfo( WorldModel *wm );
  void process();
} ;

class WMWeHaveBall : public WeHaveBall 
{
 private:
  WorldModel *WM;

 public:   
  WMWeHaveBall( WorldModel *wm );
  void process();
} ;

class WMOppHasBall : public OppHasBall
{
 private:
  WorldModel *WM;

 public:   
  WMOppHasBall( WorldModel *wm );
  void process();
} ;

class WMPassToPlayer : public PassToPlayer
{
 private:
  WorldModel *WM;

 public:   
  WMPassToPlayer( WorldModel *wm );
  void process();
} ;

class WMPassToCoord : public PassToCoord
{
 private:
  WorldModel *WM;

 public:   
  WMPassToCoord( WorldModel *wm );
  void process();
} ;

class WMWantPass : public WantPass
{
 private:
  WorldModel *WM;

 public:   
  WMWantPass( WorldModel *wm );
  void process();
} ;

class WMOppPos : public OppPos
{
 private:
  WorldModel *WM;

 public:   
  WMOppPos( WorldModel *wm );
  void process();
} ;

class WMTeammatePos : public TeammatePos 
{
 private:
  WorldModel *WM;

 public:   
  WMTeammatePos( WorldModel *wm );
  void process();
} ;

#endif
