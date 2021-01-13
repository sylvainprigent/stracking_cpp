/// \file SaFramesReader.cpp
/// \brief SaFramesReader class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <fstream>

#include <score/SException.h>
#include <score/SPath.h>

#include <SaFramesReader.h>

std::vector<std::string> SaFramesReader::readFramesList(std::string filePath)
{
    std::vector<std::string> filesList;
    std::fstream framesFile;
    framesFile.open(filePath, std::ios::in);
    if (framesFile.is_open()){
        std::string tp;
        while(getline(framesFile, tp))
        { 
            std::string currentFrameFile = SPath::relativeToFilename(tp, filePath);
            //std::cout << "readed currentFrameFile: " << currentFrameFile << std::endl;
            if (currentFrameFile == "")
            {
                throw SException(std::string("The file "+tp+" does not exists").c_str());
            }
            filesList.push_back(currentFrameFile);
        }
        framesFile.close(); 
        return filesList;
    }
    else
    {
        throw SException(std::string("The frames file "+filePath+" does not exists").c_str());
    }
}
