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
    /// \fn static std::vector<std::string> readFramesList(std::string filePath);
    /// \brief read a movie txt file
    /// \param[in] filePath String containing the txt movie file
    /// \return list of string each containing the path of one frame image
    static std::vector<std::string> readFramesList(std::string filePath);
};
