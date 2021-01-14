/// \file SaCostEuclidean.h
/// \brief SaCostEuclidean class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <string>
#include <vector>

#include "SaCost.h"
#include "SaDetection.h"

#include "satrackingExport.h"

/// \class SaCostEuclidean
/// \brief Calculate a connection cost as the euclidean distance between the detections
class SATRACKING_EXPORT SaCostEuclidean : public SaCost{

public:
    /// \fn SaCostEuclidean();
    /// \brief Constructor
    SaCostEuclidean();

    /// \fn ~SaCostEuclidean();
    /// \brief Destructor
    virtual ~SaCostEuclidean();

public:
    // --------------------- Virtuals function -----------------
    /// \fn virtual void loadDataCurentFrames(int idxFrame1, int idxFrame2) = 0;
    /// \brief Function to load the data needed for the calculation of the cost between two frames
    /// \param[in] idxFrame1 Index of the first frame
    /// \param[in] idxFrame2 Index of the second frame
    virtual void loadDataCurentFrames(int idxFrame1, int idxFrame2);

    /// \fn virtual float calculateCost(SaDEtection* detection1, SaDetection* detection2) = 0;
    /// \brief Calculate the cost of connecting two detections
    /// \param[in] detection1 First detection
    /// \param[in] detection2 Second detection
    /// \param[in] track1 Track which whom the detection1 belongs to. Not used for euclidean distance
    /// \param[in] track2 Track which whom the detection2 belongs to. Not used for euclidean distance
    virtual float calculateCost(SaDetection* detection1, SaDetection* detection2, SaTrack* track1 = nullptr, SaTrack* tracl2 = nullptr);

};
