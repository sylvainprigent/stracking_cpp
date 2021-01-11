/// \file SaLinkerGraph.h
/// \brief SaLinkerGraph class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include "SaLinker.h"

#include "satrackingExport.h"

/// \class SaLinkerGraph
/// Track particles by optimizing a global graph of detections. Each track is extracted using
/// the shortest path algorithm in the grap. The graph is build using detections. This means 
/// that the graph does not know the tracks histoty. Thus only Cost colculated between detection
/// pairs can be used with this Linker.
class SATRACKING_EXPORT SaLinkerGraph: public SaLinker{

public:

    /// \fn SaLinkerGraph();
    /// \brief Constructor
    SaLinkerGraph();
    /// \fn SaLinkerGraph(SATCost* costFunction, std::vector<std::string> framesFiles, std::vector< std::vector<SDetection*> > detections);
    /// \brief Constructor
    /// \param[in] costFunction  Pointer to the object that calculate the cost of connecting detections
    /// \param[in] framesFiles List of the files containing the frames
    /// \param[in] detections List of detected objects in each frame object [frame][idx of detection][detection info]
    SaLinkerGraph(SaCost* costFunction, std::vector<std::string>& framesFiles, std::vector< std::vector<SaDetection*> >& detections);

    /// \fn virtual ~SaLinkerGraph();
    /// \brief Destructor
    virtual ~SaLinkerGraph();

public:
    /// \fn run();
    /// \brief Virtual method that do the tracking
    void run();    

public:
    /// \fn void setJump(unsigned int jump);
    /// \brief Setter for the jump link parameter
    /// \param[in] jump Number of forward frames the tracker can look at to track a particle
    void setJump(unsigned int jump); 
    /// \fn void setJumpPenalty(float penalty);
    /// \param[in] penalty Penalisation value applied to the cost
    /// of a connection that connect none consecutive frames
    void setJumpPenalty(float penalty);
    /// \fn void setCoefIntegerConversion(float coef);
    /// \param[in] coef Multiplication coefficient applied
    /// to the cost (in float) to convert it in integer
    void setCoefIntegerConversion(float coef);
    /// void setMaxCost(const float& maxCost);
    /// \param[in] maxCost Maximum possible value of the cost for normalization of arcs weights
    void setMaxCost(const float& maxCost);

protected:
    /// \fn void runShortestPath();
    /// \brief Extract the tracks from the graph using shortest path algorithm iteratively 
    void runShortestPath();
    /// \fn int calculateNodeIdx( int t, int nt);
    /// \brief Calculate a node index from an object position in the 2D detection list
    int calculateNodeIdx( int t, int nt);

protected:
    // extra Settings
    unsigned int m_jump; ///< number of frames to link
    float m_jumpEpsilon; ///< see setJumpPenalty
    float m_coefIntegerConversion; ///< setCoefIntegerConversion
    float m_maxCost; ///< maximum possible value of the cost for normalization

private:
    std::vector<SaDetection*> m_nodesData;
};