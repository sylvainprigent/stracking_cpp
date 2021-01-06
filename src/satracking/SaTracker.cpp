/// \file SaTracker.cpp
/// \brief SaTracker class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "math.h"
#include <fstream>

#include "SaTracker.h"

SaTracker::SaTracker()
{

}

SaTracker::SaTracker(SaCost* costFunction, std::vector<std::string>& framesFiles, std::vector< std::vector<SaDetection*> >& detections)
{
    m_costFunction = costFunction;
    m_framesFiles = framesFiles;
    m_detections = detections;
}

SaTracker::~SaTracker()
{

}

void SaTracker::setCost(SaCost* costFunction)
{
    m_costFunction = costFunction;
}

void SaTracker::setFramesFiles(std::vector<std::string>& framesFiles)
{
    m_framesFiles = framesFiles;
}

void SaTracker::setDetections(std::vector< std::vector<SaDetection*> >& detections)
{
    m_detections = detections;
}

void SaTracker::setMaxMove(float maxMove)
{
    m_maxMove = maxMove;
}

std::vector<SaTrack* > SaTracker::getTracks()
{
    /// \todo Implement this STracker::getTracks()
    std::vector<SaTrack* > t;
    return t;
}

void SaTracker::saveTracksToTxt(std::string fileName)
{
    std::ofstream file(fileName.c_str(), std::ios::out | std::ios::trunc);
    if(file)
    {
        file << "fileName\tObject #\tFrame #\tX\tY\tZ" << std::endl;
        for (int m = 0 ; m < m_tracks.size() ; m++)
        {
            SaTrack* track = m_tracks[m];
            for (int i = 0 ; i < track->size() ; i++)
            { 
                SaDetection* detection = track->get(i);
                file << "\t" << m+1 << "\t" << detection->t() 
                     << "\t" << detection->x() << "\t" << detection->y() 
                     << "\t" << detection->z() << std::endl;
            }
        }
        file.close();
    }
}

void SaTracker::saveTracksMoviePlot(std::string rootFileName)
{
    /// \todo Implement this STracker::saveTracksMoviePlot()
}

bool SaTracker::isLessMaxMove(SaDetection* detection1, SaDetection* detection2)
{
    if ( fabs(detection1->x() - detection1->x()) <= m_maxMove){
        return true;
    }
    if ( fabs(detection1->y() - detection1->y()) <= m_maxMove){
        return true;
    }
    return false;
}
