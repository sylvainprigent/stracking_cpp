/// \file SaFactories.h
/// \brief SaFactories class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <satracking>
#include <sdata>

class SaFactories{

public:
    SaFactories(SObject* parameters);
    ~SaFactories();

public:
    SaCost* cost(std::string name);
    SaTracker* tracker(std::string name);

private:
    SObject* m_parameters;
};