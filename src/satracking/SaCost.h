/// \file SaCost.h
/// \brief SaCost class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <string>
#include <vector>

#include "SaDetection.h"
#include "SaTrack.h"

#include "satrackingExport.h"

/// \class SaCost
/// \brief Interface of a tracking cost function. The cost measures how likely two detections are connected
class SATRACKING_EXPORT SaCost{

public:
    /// \fn SaCost();
    /// \brief Constructor
    SaCost();

    /// \fn ~SaCost();
    /// \brief Destructor
    virtual ~SaCost();

public:
    // --------------------- Virtuals function -----------------
    /// \fn virtual void loadDataCurentFrames(int idxFrame1, int idxFrame2) = 0;
    /// \brief Function to load the data needed for the calculation of the cost between two frames
    /// \param[in] idxFrame1 Index of the first frame
    /// \param[in] idxFrame2 Index of the second frame
    virtual void loadDataCurentFrames(int idxFrame1, int idxFrame2) = 0;

    /// \fn virtual float calculateCost(SaDEtection* detection1, SaDetection* detection2) = 0;
    /// \brief Calculate the cost of connecting two detections
    /// \param[in] detection1 First detection
    /// \param[in] detection2 Second detection
    /// \param[in] track1 Track which whom the detection1 belongs to. Used only for linkers that can link tracks
    /// \param[in] track2 Track which whom the detection2 belongs to. Used only for linkers that can link tracks
    virtual float calculateCost(SaDetection* detection1, SaDetection* detection2, SaTrack* track1 = nullptr, SaTrack* tracl2 = nullptr) = 0;

public:
    // -------------------- Setters -----------------------------
    /// \fn void SetFramesPath(std::vector<std::string> &framesFiles);
    /// \brief Function used to load the frames (called by the optimizer)
    /// \param[in] framesFiles list of the frames names
    void setFramesPath(std::vector<std::string> &framesFiles);

protected:
    std::vector<std::string> m_framesFiles; ///< Frames files (full path)    
};