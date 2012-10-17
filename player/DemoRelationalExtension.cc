#include "SMDPAgent.h"
#include <iostream>


namespace keepaway_demo {

class DemoRelationalAgent: public virtual SMDPAgent {
public:

  DemoRelationalAgent(int numFeatures, int numActions);

  virtual bool isRelational();
  virtual int startEpisode(WorldModel& world);
  virtual int step(double reward, WorldModel& world);
  virtual void endEpisode(double reward);
  virtual void setParams(int iCutoffEpisodes, int iStopLearningEpisodes);
};

}


using namespace keepaway_demo;
using namespace std;


extern "C" {

SMDPAgent* createAgent(
  int numFeatures, int numActions, bool learning,
  char* inputFile, char* outputFile
) {
  DemoRelationalAgent* agent = new DemoRelationalAgent(numFeatures, numActions);
  return agent;
}

}


namespace keepaway_demo {


DemoRelationalAgent::DemoRelationalAgent(int numFeatures, int numActions):
  SMDPAgent(numFeatures, numActions)
{
  cout
    << "DemoRelationalAgent(" << numFeatures << ", " << numActions << ")"
    << endl;
}


bool DemoRelationalAgent::isRelational() {
  return true;
}


int DemoRelationalAgent::startEpisode(WorldModel& world) {
  // TODO Print state!
  cout << "startEpisode(world)" << endl;
  // Always a hold action here.
  return 0;
}


int DemoRelationalAgent::step(double reward, WorldModel& world) {
  // TODO Print state!
  cout << "step(" << reward << ", world)" << endl;
  // Always a hold action here.
  return 0;
}


void DemoRelationalAgent::endEpisode(double reward) {
  cout << "endEpisode(" << reward << ")" << endl;
}


void DemoRelationalAgent::setParams(
  int iCutoffEpisodes, int iStopLearningEpisodes
) {
  // This function is unused in the published Keepaway code.
  // HandCodedAgent actually exits with error if this function is called.
}


}
