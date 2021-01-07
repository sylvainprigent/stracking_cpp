/// \file SaTrack.cpp
/// \brief SaTrack class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SaTrack.h"

SaTrack::SaTrack(){

}

void SaTrack::append(SaDetection* detection){
    m_detections.push_back(detection);
}


unsigned int SaTrack::size()
{
    return m_detections.size();
}

SaDetection* SaTrack::get(unsigned int idx)
{
    return m_detections[idx];
}

SaDetection* SaTrack::last()
{
    return m_detections[m_detections.size()-1];
}

SaDetection* SaTrack::first()
{
    return m_detections[0];
}