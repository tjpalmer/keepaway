#include "SMDPAgent.h"
#include "WorldModel.h"
#include <iostream>


namespace keepaway_demo {

class DemoAgent: public virtual SMDPAgent {
public:

  DemoAgent(WorldModel& world, int numFeatures, int numActions);

  virtual int startEpisode(double state[]);
  virtual int step(double reward, double state[]);
  virtual void endEpisode(double reward);
  virtual void setParams(int iCutoffEpisodes, int iStopLearningEpisodes);

  WorldModel& world;
};

}


using namespace keepaway_demo;
using namespace std;


extern "C" {

SMDPAgent* createAgent(
  WorldModel& world,
  int numFeatures, int numActions, bool learning,
  char* inputFile, char* outputFile
) {
  DemoAgent* agent = new DemoAgent(world, numFeatures, numActions);
  return agent;
}

}


namespace keepaway_demo {


DemoAgent::DemoAgent(WorldModel& world_, int numFeatures, int numActions):
  SMDPAgent(numFeatures, numActions), world(world_)
{
  cout
    << "DemoAgent(world, " << numFeatures << ", " << numActions << ")" << endl;
}


int DemoAgent::startEpisode(double state[]) {
  // TODO Print state!
  cout << "startEpisode(...)" << endl;
  // Always a hold action here.
  return 0;
}


int DemoAgent::step(double reward, double state[]) {
  VecPosition position = world.getGlobalPosition(
    SoccerTypes::getTeammateObjectFromIndex(world.getAgentIndex())
  );
  // Just prove we have live info.
  cout << "step(" << reward << ", ...) at " << position << endl;
  // Always a hold action here.
  return 0;
}


void DemoAgent::endEpisode(double reward) {
  cout << "endEpisode(" << reward << ")" << endl;
}


void DemoAgent::setParams(int iCutoffEpisodes, int iStopLearningEpisodes) {
  // This function is unused in the published Keepaway code.
  // HandCodedAgent actually exits with error if this function is called.
}


}
