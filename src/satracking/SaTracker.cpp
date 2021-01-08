/// \file SaTracker.cpp
/// \brief SaTracker class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "math.h"
#include <fstream>

#include <score>
#include <sshape>
#include <simage>
#include <simageio>

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
    return m_tracks;
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

    int print_offset = 10;
    // get a random color for each track
    std::vector<SColor*> randColors;
    for (unsigned int l = 0 ; l < m_tracks.size() ; ++l){
        SColor* randColor = SColor::getRandRGB();
        randColors.push_back(randColor);
    }

    // plot tracks on each frame
    for (int t = 0 ; t < m_framesFiles.size() ; t++)
    {
        // load the frame as RGB image
        SImageFloat* frame = dynamic_cast<SImageFloat*>(SImageReader::read(m_framesFiles[t], 32));
        SImageUInt* rgbFrame = SImageColor::toRGB(frame);
        delete frame;

        // draw the track on this frame
        for (unsigned int m = 0 ; m < m_tracks.size() ; m++)
        {
            SaTrack* track = m_tracks[m];
            // get the frame color
            SColor* randColor = randColors[m];

            // plot a point in the first frame of the track
            if (track->first()->t() == t){
                SLine line(track->first()->x(), track->first()->y(), track->first()->x(), track->first()->y());
                line.setColor(randColor);
                line.draw(rgbFrame);
            }
            // Plot the track if it appears in the frame t
            if (track->first()->t() <= t && track->last()->t() >= t)
            {
                // draw the connections
                for(unsigned int i = 0 ; i < track->size()-1 ; i++)
                {
                    SaDetection* d1 = track->get(i);
                    SaDetection* d2 = track->get(i+1);
                    if (d2->t() <= t && d2->t() >= t-print_offset)
                    {
                        SLine line(d1->x(), d1->y(), d2->x(), d2->y());
                        line.setColor(randColor);
                        line.draw(rgbFrame);
                    }
                }
            }
        }
        std::string outFileName = SPath::getFileNameFromPath(m_framesFiles[t]);
        SImageReader::write(rgbFrame, rootFileName + outFileName);
    }
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
