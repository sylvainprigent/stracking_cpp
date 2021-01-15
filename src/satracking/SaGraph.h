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

public:
    /// \fn unsigned int source();
    /// \brief Getter for the source
    /// \return the id of the source node
    unsigned int source();
    /// \fn unsigned int target();
    /// \brief Getter for the target
    /// \return the id of the target node
    unsigned int target();
    /// \fn int weight();
    /// \brief Getter for the weight
    /// \return the id of the arc weight
    int weight();

private:
    unsigned int m_source; ///< index of the source node (or vertex)
    unsigned int m_target; ///< index of the target node (or vertex)
    int m_weight; ///< weight of the arc

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
    /// \fn void setArcs(std::vector<SaArc*>& graph);
    /// \brief Setter for arcs
    /// \param[in] graph List of arcs
    void setArcs(std::vector<SaArc*>& graph);
    /// \fn void setNodesNumber(unsigned int nodesNumber);
    /// \brief Setter for nodes
    /// The nodes indexes are automatically created from a node number
    /// \param[in] nodesNumber Number of nodes
    void setNodesNumber(unsigned int nodesNumber);
    /// \fn void addArc(SaArc* arc);
    /// \brief Set one arc
    /// \param[in] arc Pointer to the arc
    void addArc(SaArc* arc);
    /// \fn unsigned int addNode();
    /// \brief create a new arc
    /// \return The index of the new node
    unsigned int addNode();

public:
    /// \fn void removeNode(unsigned int node);
    /// \brief Remove a node
    /// \param[in] node index of the node
    void removeNode(unsigned int node);
    /// \fn std::vector<SaArc*> graph();
    /// \brief Get the graph arcs
    /// \return a vector containing the arcs
    std::vector<SaArc*> graph();
    /// \fn std::vector<unsigned int> nodes();
    /// \brief get list of nodes in the graph
    /// \return a vector containing the nodes indexes
    std::vector<unsigned int> nodes();
    /// \fn unsigned int nodesNumber();
    /// \brief Get the number of nodes
    /// \return the number of nodes
    unsigned int nodesNumber();

protected:
    // data
    std::vector<SaArc*> m_graph; ///< List of arcs in the graph
    std::vector<unsigned int > m_nodes; ///< List of nodes indexes in the graph

};

/// \class SaBellmanFord
/// \brief Implement the Bellman Ford shortest path optimization
class SATRACKING_EXPORT SaBellmanFord{

public:
    /// \fn SaBellmanFord(SaGraph* graph);
    /// \brief Constructor
    /// \param[in] graph Pointer to the graph container
    SaBellmanFord(SaGraph* graph);
    /// \fn ~SaBellmanFord();
    /// \brief Destructor
    ~SaBellmanFord();

public:
    /// \fn int run(unsigned int v);
    /// \brief Run the shortest path calculation
    /// \param[in] v Index of the reference node (or vertex)
    /// \return 0 if success or 1 if error
    int run(unsigned int v);

public:
    /// \fn std::map<unsigned int, unsigned int> predecessors(); 
    /// \brief Getter for predecessor
    /// For each node, the predecessor is the index of the predecessor node in the shortest path
    /// \return predecessors map
    std::map<unsigned int, unsigned int> predecessors(); 
    /// \fn std::map<unsigned int, int> distances();
    /// \brief Getter for the distances
    /// The distance map give the distance of each node to the reference node
    /// \return distance map
    std::map<unsigned int, int> distances();
    /// \fn std::vector<unsigned int> path(unsigned int node);
    /// \brief Retrieve the shortest path from the reference node the input node
    /// \param[in] node Index of the node to get the path to
    /// \return the path as a vector of nodes. The first one is the reference node and the last one is the input node
    std::vector<unsigned int> path(unsigned int node);

protected:
    std::map<unsigned int, int> m_distances; ///< distance map
    std::map<unsigned int, unsigned int> m_predecessors;  ///< predecessors map 

private:     
    SaGraph* m_graph; ///< Pointer to the graph container
};