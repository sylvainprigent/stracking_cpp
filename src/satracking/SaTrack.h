/// \file SaTrack.h
/// \brief SaTrack class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <string>
#include <vector>

#include "SaDetection.h"

#include "satrackingExport.h"

/// \class SaTrack
/// \brief class that contains a track. A track is defined as a list of detection
class SATRACKING_EXPORT SaTrack{

public:
    SaTrack();

public:
    // --------------------- setters -------------------------
    /// \fn void append(SaDetection* detection);
    /// \brief Add a detection at the end of the track
    /// \param[in] detection Pointer to the detection to append
    void append(SaDetection* detection);

    // ---------------------- getters ------------------------
    /// \fn unsigned int size();
    /// \return the size (number of detections) in the track
    unsigned int size();
    /// \fn SaDetection* get(unsigned int idx);
    /// \param[in] idx index of the detection to get
    /// \return a pointer to the detection at 'idx'
    SaDetection* get(unsigned int idx);
    /// \fn SaDetection* last();
    /// \return the last detection of the track
    SaDetection* last();
        /// \fn SaDetection* first();
    /// \return the first detection of the track
    SaDetection* first();

protected:
    std::vector<SaDetection*> m_detections;
};
