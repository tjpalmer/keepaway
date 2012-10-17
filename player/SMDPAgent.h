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

#ifndef SMDP_AGENT
#define SMDP_AGENT

#define MAX_STATE_VARS         64
#define MAX_ACTIONS            10

#include "WorldModel.h"


class SMDPAgent
{
  int m_numFeatures; /* number of state features <= MAX_STATE_VARS */
  int m_numActions;  /* number of possible actions <= MAX_ACTIONS */

 protected:

  int getNumFeatures() { return m_numFeatures; }
  int getNumActions()  { return m_numActions;  }

 public:
  
  SMDPAgent(int numFeatures, int numActions) {
    m_numFeatures = numFeatures;
    m_numActions = numActions;
  }

  virtual ~SMDPAgent() {}

  // abstract methods to be supplied by implementing class
  virtual int startEpisode(double state[]) {
    // Always choose the first action. Override for other behavior.
    return 0;
  }
  virtual int step(double reward, double state[]) {
    // Always choose the first action. Override for other behavior.
    return 0;
  }
  virtual void endEpisode(double reward) = 0;
  virtual void setParams(int iCutoffEpisodes, int iStopLearningEpisodes) = 0; //*met 8/16/05


  // The following relational forms allow for richer state.
  // Technically, other custom representations other than relational forms could
  // also be used, although I just care about relational.
  // These, however, break the prior purity of SMDPAgent which knew nothing
  // about keepaway, just episode SMDPs with vector state and discrete actions.
  // I could devise a generic schema system to allow abstract purity of
  // relational agents separate from this specific world, but it seems an
  // unlikely need in the keepaway project.
  // If anyone's interested in this, let me know.
  // Otherwise, just stick to the methods above if you want to pretend you have
  // abstract vector purity.
  // I intend to adapt WorldModel behind the scenes to our separate generic code
  // base.
  // - Tom Palmer 20121012

  int startEpisode(WorldModel& world, double state[]) {
    if (isRelational()) {
      return startEpisode(world);
    } else {
      return startEpisode(state);
    }
  }

  int step(double reward, WorldModel& world, double state[]) {
    if (isRelational()) {
      return step(reward, world);
    } else {
      return step(reward, state);
    }
  }

  /**
   * Override to true if you want to use the WorldModel directly.
   */
  virtual bool isRelational() {
    return false;
  }

  /**
   * Override for a relational agent.
   */
  virtual int startEpisode(WorldModel& world) {
    // Always choose the first action. Override for other behavior.
    return 0;
  }

  /**
   * Override for a relational agent.
   */
  virtual int step(double reward, WorldModel& world) {
    // Always choose the first action. Override for other behavior.
    return 0;
  }

};

#endif
