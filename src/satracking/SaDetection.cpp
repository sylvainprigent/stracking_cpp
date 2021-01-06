/// \file SaDetection.cpp
/// \brief SaDetection class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SaDetection.h"


SaDetection::SaDetection(){
    m_featuresCount = 0;
    m_features = nullptr;
}

SaDetection::SaDetection(float x, float y, float z, int t){
    m_x = x;
    m_y = y;
    m_z = z;
    m_t = t;
    m_featuresCount = 0;
    m_features = nullptr;
}

SaDetection::SaDetection(float x, float y, float z, int t, float* features, unsigned int featuresCount){
    m_x = x;
    m_y = y;
    m_z = z;
    m_t = t;
    m_features = features;
    m_featuresCount = featuresCount;
}

void SaDetection::setX(float x){
    m_x = x;
}

void SaDetection::setY(float y){
    m_y = y;
}

void SaDetection::setZ(float z){
    m_z = z;
}

void SaDetection::setT(int t){
    m_t = t;
}

void SaDetection::setFeatures(float* features, unsigned int size){
    m_features = features;
    m_featuresCount = size;
}

float SaDetection::x(){
    return m_x;
}

float SaDetection::y(){
    return m_y;
}

float SaDetection::z(){
    return m_z;
}

int SaDetection::t(){
    return m_t;
}

float* SaDetection::features(){
    return m_features;
}

unsigned int SaDetection::featuresCount(){
    return m_featuresCount;
}

float SaDetection::feature(unsigned int idx){
    return m_features[idx];
}
