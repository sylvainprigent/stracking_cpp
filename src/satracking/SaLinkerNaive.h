/// \file SaLinkerNaive.h
/// \brief SaLinkerNaive class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "SaLinker.h"

#include "satrackingExport.h"

/// \class SaLinkerNaive
/// \brief The more basic and naive tracker. 
/// For each detection it connects to the one with the less cost. when a detection is used,
/// it cannot be used by another track. This means that the obtained trajectories are not 
/// optimal in the general case. Nevertheless, it is very fast vor abvious tracking situations.
class SATRACKING_EXPORT SaLinkerNaive : public SaLinker{

public:

    /// \fn SaLinkerNaive();
    /// \brief Constructor
    SaLinkerNaive();
    /// \fn SaLinkerNaive(SATCost* costFunction, std::vector<std::string> framesFiles, std::vector< std::vector<SDetection*> > detections);
    /// \brief Constructor
    /// \param[in] costFunction  Pointer to the object that calculate the cost of connecting detections
    /// \param[in] framesFiles List of the files containing the frames
    /// \param[in] detections List of detected objects in each frame object [frame][idx of detection][detection info]
    SaLinkerNaive(SaCost* costFunction, std::vector<std::string>& framesFiles, std::vector< std::vector<SaDetection*> >& detections);

    /// \fn virtual ~SaTracker();
    /// \brief Destructor
    ~SaLinkerNaive();

public:
    /// \fn void run() = 0;
    /// \brief Virtual method that do the tracking
    void run();    

};