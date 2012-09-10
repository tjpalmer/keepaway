#include "SMDPAgent.h"
#include <iostream>


namespace keepaway_demo {

class DemoAgent: public virtual SMDPAgent {
public:

  DemoAgent(int numFeatures, int numActions);

  virtual int startEpisode(double state[]);
  virtual int step(double reward, double state[]);
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
  DemoAgent* agent = new DemoAgent(numFeatures, numActions);
  return agent;
}

}


namespace keepaway_demo {


DemoAgent::DemoAgent(int numFeatures, int numActions):
  SMDPAgent(numFeatures, numActions)
{
  cout << "DemoAgent(" << numFeatures << ", " << numActions << ")" << endl;
}


int DemoAgent::startEpisode(double state[]) {
  // TODO Print state!
  cout << "startEpisode(...)" << endl;
  // Always a hold action here.
  return 0;
}


int DemoAgent::step(double reward, double state[]) {
  // TODO Print state!
  cout << "step(" << reward << ", ...)" << endl;
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
