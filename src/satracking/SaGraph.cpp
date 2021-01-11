/// \file SaGraph.cpp
/// \brief SaGraph class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include "SaGraph.h"

#include "math.h"

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
    m_nodesNumber = 0;
}

SaGraph::SaGraph(std::vector<SaArc*>& graph, unsigned int nodesNumber)
{
    m_graph = graph;
    m_nodesNumber = nodesNumber;
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
    m_nodesNumber = nodesNumber;
}

void SaGraph::addArc(SaArc* arc)
{
    m_graph.push_back(arc);
}

unsigned int SaGraph::addNode()
{
    m_nodesNumber++;
    return m_nodesNumber-1;
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
    m_nodesNumber--;
}

std::vector<SaArc*> SaGraph::graph()
{
    return m_graph;
}

unsigned int SaGraph::nodesNumber()
{
    return m_nodesNumber;
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

void SaBellmanFord::run(unsigned int v)
{
    std::vector<SaArc*> e = m_graph->graph();
    unsigned int nodesNumber = m_graph->nodesNumber();

    // initialization
    m_distances.clear();
    m_predecessors.clear();
    m_distances.resize(nodesNumber);
    m_predecessors.resize(nodesNumber);
    for (int n = 0 ; n < nodesNumber ; n++)
    {
        m_distances[n] = INT64_MAX;
        m_predecessors[n] = -1;
    }

    m_distances[v] = 0;

    for (;;)
    {
        bool any = false;
        for (int j = 0; j < e.size(); ++j)
            if (m_distances[e[j]->source()] < INT64_MAX)
                if (m_distances[e[j]->target()] > m_distances[e[j]->source()] + e[j]->weight())
                {
                    m_distances[e[j]->target()] = m_distances[e[j]->source()] + e[j]->weight();
                    m_predecessors[e[j]->target()] = e[j]->source();
                    any = true;
                }
        if (!any)  break;
    }
}

std::vector<unsigned int> SaBellmanFord::predecessors()
{
    return m_predecessors;
} 

std::vector<int> SaBellmanFord::distances()
{
    return m_distances;
}
