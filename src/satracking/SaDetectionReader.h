/// \file SaDetectionReader.h
/// \brief SaDetectionReader class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <string>

#include "SaDetection.h"

#include "satrackingExport.h"

/// \class SaDetectionReader
/// \brief Read detections from files
class SATRACKING_EXPORT SaDetectionReader{
    
public:
    /// \fn static std::vector<SaDetection*> readDetections(std::string filePath, int t = 0);
    /// \brief Read detections from one txt file
    /// The detections in the file must be from the same time frame
    /// \param[in] filePath String containing the path of the detection file
    /// \param[in] t Index of the time frame 
    /// \return A vector of the readed detections
    static std::vector<SaDetection*> readDetections(std::string filePath, int t = 0);
    /// \fn static std::vector< std::vector<SaDetection*> > readDetectionsList(std::string listFile);
    /// \brief Read detections from multiple frames files
    /// \param[in] listFiles Path to the detections files. One file per frame
    /// \return 2D vector of the readed detections. The first dimension is the frames, and the second detections
    static std::vector< std::vector<SaDetection*> > readDetectionsList(std::string listFile);
};
