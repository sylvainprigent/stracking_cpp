/// \file SaFramesReader.h
/// \brief SaFramesReader class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <string>
#include <vector>

#include "satrackingExport.h"

/// \class readFramesList
/// \brief Read frames from movie txt file
class SATRACKING_EXPORT SaFramesReader{
    
public:
    static std::vector<std::string> readFramesList(std::string filePath);
};
