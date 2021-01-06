/// \file SaCostEuclidean.CPP
/// \brief SaCostEuclidean class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SaCostEuclidean.h"

SaCostEuclidean::SaCostEuclidean() : SaCost()
{

}

SaCostEuclidean::~SaCostEuclidean()
{

}

void SaCostEuclidean::loadDataCurentFrames(int, int)
{
    // no data needed
}

float SaCostEuclidean::calculateCost(SaDetection* detection1, SaDetection* detection2)
{
    float euclX = detection1->x() - detection2->x();
    float euclY = detection1->y() - detection2->y();
    float euclZ = detection1->z() - detection2->z();
    return euclX*euclX + euclY*euclY + euclZ*euclZ;
}

bool SaCostEuclidean::isProbability()
{
    return false;
}