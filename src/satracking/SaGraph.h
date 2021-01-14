/// \file SaGraph.h
/// \brief SaGraph class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <string>
#include <vector>
#include <map>


#include "satrackingExport.h"

/// \class SaArc
/// \brief container for a graph arc
class SATRACKING_EXPORT SaArc{

public:
    /// \fn SaArc();
    /// \brief Constructor
    SaArc();
    /// \fn SaArc(unsigned int source, unsigned int target, int weight);
    /// \brief Constructor
    /// \param[in] source Index of the source node
    /// \param[in] target Index of the target node
    /// \param[in] weight Weight of the arc
    SaArc(unsigned int source, unsigned int target, int weight);

public:
    /// \fn void setSource(unsigned int source);
    /// \brief set the index of the source node (or vertex)
    /// \param[in] source Index of the source node
    void setSource(unsigned int source);
    /// \fn void setTarget(unsigned int target);
    /// \brief set the index of the target node (or vertex)
    /// \param[in] target Index of the target node
    void setTarget(unsigned int target);
    /// \fn void setWeight(int weight);
    /// \brief setter for the weight of the arc
    /// \param[in] weight Weight or cost of the arc
    void setWeight(int weight);

    unsigned int source();
    unsigned int target();
    int weight();

private:
    unsigned int m_source;
    unsigned int m_target;
    int m_weight;

};

/// \class SaGraph
/// \brief Class to represent a graph (for path search)
class SATRACKING_EXPORT SaGraph{

public:

    /// \fn SaGraph();
    /// \brief Constructor
    SaGraph();
    /// \fn SaGraph(std::vector<SaArc*>& graph, unsigned int nodesNumber);
    /// \brief Constructor
    /// \param[in] graph Vector containing the graph arcs
    /// \param[in] nodesNumber Number of nodes in the graph
    SaGraph(std::vector<SaArc*>& graph, unsigned int nodesNumber);

    /// \fn SaGraph(std::vector<SaArc*>& graph, unsigned int nodesNumber);
    /// \brief Constructor
    /// \param[in] graph Vector containing the graph arcs
    /// \param[in] nodes List of nodes ids
    SaGraph(std::vector<SaArc*>& graph, std::vector<unsigned int>& nodes);

    /// \fn ~SaGraph();
    /// \brief Destructor
    ~SaGraph();

public:
    void setArcs(std::vector<SaArc*>& graph);
    void setNodesNumber(unsigned int nodesNumber);
    void addArc(SaArc*);
    unsigned int addNode();

public:
    void removeNode(unsigned int node);
    std::vector<SaArc*> graph();
    std::vector<unsigned int> nodes();
    unsigned int nodesNumber();

protected:
    // data
    std::vector<SaArc*> m_graph;
    std::vector<unsigned int > m_nodes;

};

/// \class SaBellmanFord
/// \brief Implement the Bellman Ford shortest path optimization
class SATRACKING_EXPORT SaBellmanFord{

public:
    SaBellmanFord(SaGraph* graph);
    ~SaBellmanFord();

public:
    /// \param[in] v Index of the vertex or node reference
    int run(unsigned int v);

public:
    std::map<unsigned int, unsigned int> predecessors();  
    std::map<unsigned int, int> distances();
    std::vector<unsigned int> path(unsigned int node);

protected:
    std::map<unsigned int, int> m_distances;
    std::map<unsigned int, unsigned int> m_predecessors;  

private:     
    SaGraph* m_graph;
};