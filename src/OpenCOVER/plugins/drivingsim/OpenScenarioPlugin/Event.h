#ifndef EVENT_H
#define EVENT_H

#include<string>
#include <vector>
#include <list>
#include <osg/Vec3>
#include <OpenScenario/schema/oscEvent.h>
class Action;
class Event : public::OpenScenario::oscEvent
{
public:
    Event();

    std::vector<::Action*> actionVector;
    int finishedEntityActions;
    int activeEntites;
    std::string name;

    //conditions
    bool eventCondition;
    bool eventFinished;
    float startTime;
    std::string startConditionType;
    std::string startAfterManeuver;
    std::string passiveCarName;
    std::string activeCarName;
    float relativeDistance;

    std::string &getName();
    void initialize(int numEntites);
};

#endif // EVENT_H
