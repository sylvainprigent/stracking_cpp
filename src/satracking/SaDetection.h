/// \file SaDetection.h
/// \brief SaDetection class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <string>

#include "satrackingExport.h"

/// \class SDetection
/// \brief class that contains a detection information
class SATRACKING_EXPORT SaDetection{

public:
    SaDetection();
    SaDetection(float x, float y, float z, int t);
    SaDetection(float x, float y, float z, int t, float* features, unsigned int featuresCount);

public:
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setT(int t);

    void setFeatures(float* features, unsigned int size);

public:
    float x();
    float y();
    float z();
    int t();
    float* features();
    unsigned int featuresCount();
    float feature(unsigned int idx);

protected:
    float m_x;
    float m_y;
    float m_z;
    int m_t;
    float* m_features;
    unsigned int m_featuresCount;
};
