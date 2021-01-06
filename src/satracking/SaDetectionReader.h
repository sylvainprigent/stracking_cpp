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
    static std::vector<SaDetection*> readDetections(std::string filePath, int t = 0);
    static std::vector< std::vector<SaDetection*> > readDetectionsList(std::string listFile);
};
