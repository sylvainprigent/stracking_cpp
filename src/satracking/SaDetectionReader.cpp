/// \file SaDetectionReader.cpp
/// \brief SaDetectionReader class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <fstream>
#include <sstream>
#include <vector>

#include <score>

#include "SaDetectionReader.h"

std::vector<std::string> sa_split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

std::vector<SaDetection*> SaDetectionReader::readDetections(std::string filePath, int t)
{
    std::vector<SaDetection*> out;
    std::fstream detectionsFile;
    detectionsFile.open(filePath, std::ios::in);
    if (detectionsFile.is_open()){
        std::string tp;
        while(getline(detectionsFile, tp)){ 
            std::vector<std::string> lineAsList = sa_split(tp, ',');
            if (lineAsList.size() > 1){
                SaDetection* detection = new SaDetection;
                if (lineAsList.size() == 2)
                {
                    detection->setX(SStringOp::string2float(lineAsList[0]));
                    detection->setY(SStringOp::string2float(lineAsList[1]));  
                    detection->setZ(0.0);
                    detection->setT(t);      
                }
                else if (lineAsList.size() == 3)
                {
                    detection->setX(SStringOp::string2float(lineAsList[0]));
                    detection->setY(SStringOp::string2float(lineAsList[1]));  
                    detection->setZ(SStringOp::string2float(lineAsList[2]));
                    detection->setT(t);      
                }
                else if (lineAsList.size() > 3)
                {
                    detection->setX(SStringOp::string2float(lineAsList[0]));
                    detection->setY(SStringOp::string2float(lineAsList[1]));  
                    detection->setZ(SStringOp::string2float(lineAsList[2]));
                    detection->setT(t); 
                    int features_count = lineAsList.size()-3;
                    float *features = new float[features_count];
                    for (int i = 0 ; i < features_count ; i++){
                        features[i] = SStringOp::string2float(lineAsList[i+3]);        
                    }
                    detection->setFeatures(features, features_count);
                }
                out.push_back(detection);
            }
        }
        detectionsFile.close(); 
    }
    else
    {
        throw SException(std::string("The file "+filePath+" does not exists").c_str());
    }
    return out;
}

std::vector< std::vector<SaDetection*> > SaDetectionReader::readDetectionsList(std::string listFile)
{
    std::vector< std::vector<SaDetection*> > out;
    std::fstream lFile;
    lFile.open(listFile, std::ios::in);
    int t = -1;
    if (lFile.is_open()){
        std::string tp;
        while(getline(lFile, tp))
        { 
            t++;
            std::string currentDetectionFile = SPath::relativeToFilename(tp, listFile);
            if (currentDetectionFile == "")
            {
                throw SException(std::string("The file "+tp+" does not exists").c_str());
            }
            out.push_back(SaDetectionReader::readDetections(currentDetectionFile, t));
        }
        lFile.close(); 
    }
    else
    {
        throw SException(std::string("The detection file "+listFile+" does not exists").c_str());
    }
    return out;
}