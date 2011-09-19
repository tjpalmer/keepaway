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

#include "WorldModelSayMsgTypes.h"
#include "SoccerTypes.h"
#include "Geometry.h"

short char2numMap[256]; // We have to put it somewhere

WMOurPos::WMOurPos( WorldModel *wm ) : OurPos()
{
  WM = wm;
}

void WMOurPos::process()
{
  ObjectT obj = SoccerTypes::getTeammateObjectFromIndex( SenderPlayerNum - 1 );
  WM->processPerfectHearInfo( obj, VecPosition( X, Y ), 0.99, 
			      obj == WM->getOwnGoalieType() );
}

WMBallInfo::WMBallInfo( WorldModel *wm ) : BallInfo() 
{
  WM = wm;
}

void WMBallInfo::process()
{
  VecPosition pos( X, Y );
  VecPosition vel( dX, dY );

  for ( int i = 0; i < cycleno ; i++ ) {
    pos += vel;
    vel *= 0.94; //SS->getBallDecay();
  }

  // if ball not seen or felt for three cycles, update ball information
  if ( WM->getTimeLastSeen( OBJECT_BALL ) == -1 ||
       (
	WM->getTimeChangeInformation( OBJECT_BALL ) < WM->getCurrentTime() - 3 &&
	WM->getRelativeDistance( OBJECT_BALL ) > 3.0 //SS->getVisibleDistance()  
         ) ||
        (
          WM->getTimeChangeInformation( OBJECT_BALL ) < WM->getCurrentTime() - cycleno &&
          vel.getDistanceTo( WM->getGlobalVelocity( OBJECT_BALL ) ) > 0.3 &&
          WM->getRelativeDistance( OBJECT_BALL ) > 3.0//SS->getVisibleDistance()
        )
      ) {
    double dConf = Object::getConfidenceFromTimeDiff( cycleno );
    WM->processPerfectHearInfoBall( pos, vel, dConf - 0.01 );
  }
}

WMWeHaveBall::WMWeHaveBall( WorldModel *wm ) : WeHaveBall()
{
  WM = wm;
}

void WMWeHaveBall::process()
{
  //ObjectT obj = SoccerTypes::getTeammateObjectFromIndex( playernum - 1 );
  //WM->setBallOwner( obj );
}

WMOppHasBall::WMOppHasBall( WorldModel *wm ) : OppHasBall()
{
  WM = wm;
}

void WMOppHasBall::process()
{
  //ObjectT obj = SoccerTypes::getOpponentObjectFromIndex( playernum - 1 );
  //WM->setBallOwner( obj );
}

WMPassToPlayer::WMPassToPlayer( WorldModel *wm ) : PassToPlayer()
{
  WM = wm;
}

void WMPassToPlayer::process()
{
  //ObjectT passer = SoccerTypes::getOpponentObjectFromIndex( SenderPlayerNum - 1 );
  //ObjectT receiver = SoccerTypes::getOpponentObjectFromIndex( playernum - 1 );
}

WMPassToCoord::WMPassToCoord( WorldModel *wm ) : PassToCoord()
{
  WM = wm;
}

void WMPassToCoord::process()
{
  //ObjectT passer = SoccerTypes::getOpponentObjectFromIndex( SenderPlayerNum - 1 );
  //VecPosition pos( X, Y );
}

WMWantPass::WMWantPass( WorldModel *wm ) : WantPass()
{
  WM = wm;
}

void WMWantPass::process()
{
  //ObjectT obj = SoccerTypes::getOpponentObjectFromIndex( SenderPlayerNum - 1 );
}

WMOppPos::WMOppPos( WorldModel *wm ) : OppPos()
{
  WM = wm;
}

void WMOppPos::process()
{
  ObjectT obj = SoccerTypes::getOpponentObjectFromIndex( playernum - 1 );
  double dConf = Object::getConfidenceFromTimeDiff( cycleno );
  WM->processPerfectHearInfo( obj, VecPosition( X, Y ), dConf - 0.01, 
			      obj == WM->getOppGoalieType() );
}

WMTeammatePos::WMTeammatePos( WorldModel *wm ) : TeammatePos()
{
  WM = wm;
}

void WMTeammatePos::process()
{
  ObjectT obj = SoccerTypes::getTeammateObjectFromIndex( playernum - 1 );
  double conf = Object::getConfidenceFromTimeDiff( cycleno );
  WM->processPerfectHearInfo( obj, VecPosition( X, Y ), conf, 
			      obj == WM->getOwnGoalieType() );
}
