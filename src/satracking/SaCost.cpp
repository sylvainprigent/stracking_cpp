/// \file SaCost.h
/// \brief SaCost class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SaCost.h"

SaCost::SaCost()
{

}

SaCost::~SaCost()
{

}

void SaCost::setFramesPath(std::vector<std::string> &framesFiles)
{
    m_framesFiles = framesFiles;
}