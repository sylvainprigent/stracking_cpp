/// \file SaGraph.cpp
/// \brief SaGraph class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SaGraph.h"

#include "math.h"
#include <algorithm>
#include <iostream>

SaArc::SaArc()
{

}

SaArc::SaArc(unsigned int source, unsigned int target, int weight)
{
    m_source = source;
    m_target = target;
    m_weight = weight;
}

void SaArc::setSource(unsigned int source)
{
    m_source = source;
}

void SaArc::setTarget(unsigned int target)
{
    m_target = target;
}

void SaArc::setWeight(int weight)
{
    m_weight = weight;
}

unsigned int SaArc::source()
{
    return m_source;
}

unsigned int SaArc::target()
{
    return m_target;
}

int SaArc::weight()
{
    return m_weight;
}


SaGraph::SaGraph()
{
    m_graph.clear();
    m_nodes.clear();
}

SaGraph::SaGraph(std::vector<SaArc*>& graph, unsigned int nodesNumber)
{
    m_graph = graph;
    this->setNodesNumber(nodesNumber);
}

SaGraph::SaGraph(std::vector<SaArc*>& graph, std::vector<unsigned int>& nodes)
{
    m_graph = graph;
    m_nodes = nodes;
}

SaGraph::~SaGraph()
{

}

void SaGraph::setArcs(std::vector<SaArc*>& graph)
{
    m_graph = graph;
}

void SaGraph::setNodesNumber(unsigned int nodesNumber)
{
    m_nodes.clear();
    m_nodes.resize(nodesNumber);
    for (int n = 0 ; n < nodesNumber ; ++n){
        m_nodes[n] = n;
    }
}

void SaGraph::addArc(SaArc* arc)
{
    m_graph.push_back(arc);
}

unsigned int SaGraph::addNode()
{
    unsigned int id =  m_nodes.size();
    m_nodes.push_back(id);
    return id;
}

void SaGraph::removeNode(unsigned int node)
{
    for (int i = m_graph.size()-1 ; i >= 0; i--)
    {
        SaArc* arc = m_graph[i];
        if (arc->source() == node || arc->target() == node)
        {
            m_graph.erase(m_graph.begin()+i);
        }
    }
    unsigned int nodeIdx = -1;
    for (int i = 0 ; i < m_nodes.size(); i++)
    {
        if (m_nodes[i] == node){
            nodeIdx = i;
            break;
        }
        
    }
    if (nodeIdx >= 0){
        m_nodes.erase(m_nodes.begin()+nodeIdx);
    }
    
}

std::vector<SaArc*> SaGraph::graph()
{
    return m_graph;
}

std::vector<unsigned int> SaGraph::nodes()
{
    return m_nodes;
}

unsigned int SaGraph::nodesNumber()
{
    return m_nodes.size();
}

// ///////////////////////////////////////////////////////
//                  SaBellmanFord
// ///////////////////////////////////////////////////////
SaBellmanFord::SaBellmanFord(SaGraph* graph)
{
    m_graph = graph;
}

SaBellmanFord::~SaBellmanFord()
{

}

int SaBellmanFord::run(unsigned int v)
{
    std::vector<SaArc*> e = m_graph->graph();
    std::vector<unsigned int> nodes = m_graph->nodes();

    //std::cout << "graph node number = " << nodes.size() << std::endl;
    //std::cout << "graph arcs number = " << e.size() << std::endl;
    //std::cout << "graph print:" << std::endl;
    //for (int i = 0 ; i < e.size() ; i++)
    //{
    //    std::cout << "arc: " << e[i]->source() << ", " << e[i]->target() << ", " << e[i]->weight() << ", " << std::endl;
    //}
    //for (int i = 0 ; i < nodes.size() ; i++){
    //    std::cout << "node[" << i << "]="<< nodes[i]<<std::endl; 
    //}

    if (e.size() < 2){
        return 1;
    }

    int INF = 999999999;
    // initialization
    m_distances.clear();
    m_predecessors.clear();
    for (int n = 0 ; n < nodes.size() ; n++)
    {
        m_distances[nodes[n]] = INF;
        m_predecessors[nodes[n]] = -1;
    }

    m_distances[nodes[v]] = 0;

    /*
    std::map<unsigned int, int>::iterator it = m_distances.begin();
    std::cout << "initial distances:" << std::endl;
    while (it != m_distances.end())
    {
        std::cout << "d[" << it->first << "]: " << it->second << std::endl;
        it++;
    }
    */

    for (;;)
    {
        bool any = false;
        for (int j = 0; j < e.size(); ++j)
            if (m_distances[e[j]->source()] < INF)
                if (m_distances[e[j]->target()] > m_distances[e[j]->source()] + e[j]->weight())
                {
                    m_distances[e[j]->target()] = m_distances[e[j]->source()] + e[j]->weight();
                    m_predecessors[e[j]->target()] = e[j]->source();
                    any = true;
                }
        if (!any)  break;
    }

    return 0;
}

std::vector<unsigned int> SaBellmanFord::path(unsigned int node)
{
    std::vector<unsigned int> path;
    path.push_back(node);
    unsigned int predecessor = node;    
    while (predecessor > 0)
    {
        predecessor = m_predecessors[predecessor];
        path.push_back(predecessor);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::map<unsigned int, unsigned int> SaBellmanFord::predecessors()
{
    return m_predecessors;
} 

std::map<unsigned int, int> SaBellmanFord::distances()
{
    return m_distances;
}
