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

#include <string.h>
#include <stdlib.h>
#include "HandCodedAgent.h"

HandCodedAgent::HandCodedAgent( int numFeatures, int numActions,
				char *strPolicy, WorldModel *wm ):
  SMDPAgent( numFeatures, numActions )
{
  strcpy( policy, strPolicy );
  WM = wm;
}


int HandCodedAgent::startEpisode( double state[] )
{
  return step( 0, state );
}

int HandCodedAgent::step( double reward, double state[] )
{
  if ( policy[0] == 'r' ) {      // (r)andom
    return random();
  }
  else if ( policy[1] == 'o' ) { // h(o)ld
    return alwaysHold();
  }
  else {                         // h(a)nd
    return handCoded( state );
  }
}

void HandCodedAgent::endEpisode( double reward )
{
  // Do nothing
}

/************ POLICIES **************/

int HandCodedAgent::alwaysHold()
{
  return 0;
}

int HandCodedAgent::random()
{
  return ( rand() % getNumActions() );
}

/**
 * Handcoded policy from Adaptive Behavior '05 article
 * Stone, Sutton, and Kuhlmann
 */
int HandCodedAgent::handCoded( double state[] )
{
  int numK = WM->getNumKeepers();
  int numT = WM->getNumTakers();

  double WB_dist_to_C;
  double WB_dist_to_K[ numK ];
  double WB_dist_to_T[ numT ];
  double dist_to_C_K[ numK ];
  double dist_to_C_T[ numT ];
  double nearest_Opp_dist_K[ numK ];
  double nearest_Opp_ang_K[ numK ];

  int j = 0;
  WB_dist_to_C = state[ j++ ];
  for ( int i = 1; i < numK; i++ )
    WB_dist_to_K[ i ] = state[ j++ ];
  for ( int i = 0; i < numT; i++ )
    WB_dist_to_T[ i ] = state[ j++ ];
  for ( int i = 1; i < numK; i++ )
    dist_to_C_K[ i ] = state[ j++ ];
  for ( int i = 0; i < numT; i++ )
    dist_to_C_T[ i ] = state[ j++ ];
  for ( int i = 1; i < numK; i++ )
    nearest_Opp_dist_K[ i ] = state[ j++ ];
  for ( int i = 1; i < numK; i++ )
    nearest_Opp_ang_K[ i ] = state[ j++ ];

  // If there are no opponents within 5m, then hold
  if ( WB_dist_to_T[ 0 ] > 5 )
    return 0;

  float scores[ numK ];

  // Hold threshold (alpha)
  scores[0] = 90;
  // Dist/Ang ratio (beta)
  float dist_weight = 4.0;

  for ( int i=1; i<numK; i++ )
    scores[i] = dist_weight * nearest_Opp_dist_K[i] +
      nearest_Opp_ang_K[i];
  
  // Get MAX
  int best = 0;
  for ( int i=1; i<numK; i++ )
    if ( scores[i] > scores[best] )
      best = i;

  return best;
}
