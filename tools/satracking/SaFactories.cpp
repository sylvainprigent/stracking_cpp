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
    if (name == "SaCostStraight"){
        SaCostStraight* cost = new SaCostStraight;
        SFloat* lambda = dynamic_cast<SFloat*>(m_parameters->get("SaCostStraight.Lambda"));
        if (lambda){
            cost->setLambda(lambda->get());
        }
        else{
            throw SException("Connot read the parameter SaCostStraight.Lambda as float");
        }
        return cost;
    }

    throw SException(("Cannot find the cost " + name).c_str());
}

SaLinker* SaFactories::linker(std::string name)
{
    if (name == "SaLinkerNaive"){
        SaLinkerNaive* linker = new SaLinkerNaive;
        SFloat* maxMove = dynamic_cast<SFloat*>(m_parameters->get("SaLinker.MaxMove"));
        if (maxMove){
            linker->setMaxMove(maxMove->get());
        }
        else{
            throw SException("Connot read the parameter SaLinker.MaxMove as float");
        }
        return linker;
    }

    throw SException(("Cannot find the tracker " + name).c_str());
}
