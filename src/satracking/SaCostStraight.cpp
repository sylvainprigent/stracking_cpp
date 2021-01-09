/// \file SaCostStraight.CPP
/// \brief SaCostStraight class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "math.h"
#include <iostream>

#include "SaCostStraight.h"

SaCostStraight::SaCostStraight() : SaCost()
{
    m_lambda = 1.0;
}

SaCostStraight::~SaCostStraight()
{

}

void SaCostStraight::loadDataCurentFrames(int, int)
{
    // no data needed
}

float SaCostStraight::calculateCost(SaDetection* detection1, SaDetection* detection2, SaTrack* track1, SaTrack*)
{
    //std::cout << "SaCostStraight connecting (" << detection1->x() << ", " << detection1->y() << ", " << detection1->t()
    //          << ") to (" 
    //          << detection2->x() << ", " << detection2->y() << ", " << detection2->t() << ")" << std::endl;; 
    float euclX = detection1->x() - detection2->x();
    float euclY = detection1->y() - detection2->y();
    float euclZ = detection1->z() - detection2->z();
    float eculidean_cost = euclX*euclX + euclY*euclY + euclZ*euclZ;

    float angle_cost = 0;
    if (track1){
        SaDetection* detection0 = track1->get(track1->size()-2);
        float ab_x = detection1->x() - detection0->x();
        float ab_y = detection1->y() - detection0->y();
        float cb_x = detection1->x() - detection2->x();
        float cb_y = detection1->y() - detection2->y();
        float dot = ab_x * cb_x + ab_y * cb_y; //dot product
        float cross = ab_x * cb_y - ab_y * cb_x; //cross product
        float alpha = atan2(cross, dot);
        //std::cout << "angle=" << alpha * 180. / 3.14 << std::endl;
        angle_cost = 180 - fabs(alpha * 180. / 3.14);
        angle_cost *= angle_cost;
    }

    std::cout << "eculidean_cost = " << eculidean_cost << std::endl;
    std::cout << "angle_cost=" << angle_cost << std::endl;
    std::cout << "cost=" << eculidean_cost + m_lambda*angle_cost << std::endl;
    return eculidean_cost + m_lambda*angle_cost;
}

void SaCostStraight::setLambda(const float& lambda){
    m_lambda = lambda;
}