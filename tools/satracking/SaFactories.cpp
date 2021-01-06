/// \file SaFactories.cpp
/// \brief SaFactories class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SaFactories.h"
#include <score>

SaFactories::SaFactories(SObject* parameters){
    m_parameters = parameters;
}

SaFactories::~SaFactories(){

}

SaCost* SaFactories::cost(std::string name)
{
    if (name == "SaCostEuclidean"){
        SaCostEuclidean* cost = new SaCostEuclidean;
        return cost;
    }

    throw SException(("Cannot find the cost " + name).c_str());
}

SaTracker* SaFactories::tracker(std::string name)
{
    if (name == "SaTrackerLessCost"){
        SaTrackerLessCost* tracker = new SaTrackerLessCost;
        return tracker;
    }

    throw SException(("Cannot find the tracker " + name).c_str());
}
