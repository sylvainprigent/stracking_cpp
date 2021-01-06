/// \file SaTracker.h
/// \brief SaTracker class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <string>
#include <vector>

#include "SaCost.h"
#include "SaDetection.h"
#include "SaTrack.h"

#include "satrackingExport.h"

/// \class SaTracker
/// \brief Interface for tracking algorithm. All tracking algorithm must implement this interface
class SATRACKING_EXPORT SaTracker{

public:

    /// \fn SaTracker();
    /// \brief Constructor
    SaTracker();
    /// \fn SaTracker(SATCost* costFunction, std::vector<std::string> framesFiles, std::vector< std::vector<SDetection*> > detections);
    /// \brief Constructor
    /// \param[in] costFunction  Pointer to the object that calculate the cost of connecting detections
    /// \param[in] framesFiles List of the files containing the frames
    /// \param[in] detections List of detected objects in each frame object [frame][idx of detection][detection info]
    SaTracker(SaCost* costFunction, std::vector<std::string>& framesFiles, std::vector< std::vector<SaDetection*> >& detections);

    /// \fn virtual ~SaTracker();
    /// \brief Destructor
    virtual ~SaTracker();

public:
    // ------------------------- Setters ---------------------------
    /// \fn void setCost(SaCost* costFunction);
    /// \brief Input setter
    /// \param[in] costFunction  Pointer to the object that calculate the cost of connecting detections  
    void setCost(SaCost* costFunction);
    /// \fn void setFramesFiles(std::vector<std::string>& framesFiles);
    /// \brief Input setter
    /// \param[in] framesFiles List of the files containing the frames
    void setFramesFiles(std::vector<std::string>& framesFiles);
    /// \fn void setDetections(std::vector< std::vector<SaDetection*> >& detections);
    /// \brief Input setter
    /// \param[in] detections List of detected objects in each frame object [frame][idx of detection][detection info]
    void setDetections(std::vector< std::vector<SaDetection*> >& detections);

public:
    // ------------------- Algorithm parameters --------------------
    /// \fn void setMaxMove(float maxMove);
    ///  \param[in] maxMove Maximum spatial distance for two detections
    ///  to be considered too far for being connected
    void setMaxMove(float maxMove);

public:
    /// \fn void run() = 0;
    /// \brief Virtual method that do the tracking
    virtual void run() = 0;    

public:
    // ------------------------- outputs ----------------------------   
    /// \fn std::vector<SaTrack* > getTracks();
    /// \return the tracks list
    std::vector<SaTrack*> getTracks();
    /// \fn void saveTracksToTxt(std::string fileName);
    /// \brief Save the trjectories in a txt file
    /// \param[in] fileName Name (full path) of the file where the tracks are saved
    void saveTracksToTxt(std::string fileName);
    /// \fn void saveTracksMoviePlot(std::string rootFileName);
    /// \param[in] rootFileName Name of the file where the result is save
    void saveTracksMoviePlot(std::string rootFileName);

protected:
    /// \fn bool isLessMaxMove(SaDetection* detection1, SaDetection* detection2);
    /// \brief Check is two detections are clother than the maxMove parameter
    /// \param[in] detection1 First detection to check
    /// \param[in] detection2 Second detection to check
    bool isLessMaxMove(SaDetection* detection1, SaDetection* detection2);

protected:
    // inputs
    SaCost* m_costFunction; ///< Pointer to the cost function
    std::vector<std::string> m_framesFiles; ///< List of the files containing the frames
    std::vector< std::vector<SaDetection*> > m_detections; ///< List of detected objects in each frame object [frame][idx of detection][detection info]

protected:
    // extra Settings
    float m_maxMove; ///< maximum move of an object between two consecutive frames

protected:
    // outputs
    std::vector<SaTrack*> m_tracks;
};