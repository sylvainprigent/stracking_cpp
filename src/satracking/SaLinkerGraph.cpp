/// \file SaLinkerGraph.cpp
/// \brief SaLinkerGraph class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <iostream>

#include "SaLinkerGraph.h"
#include "SaGraph.h"
#include <algorithm>

using namespace std;

SaLinkerGraph::SaLinkerGraph() : SaLinker()
{
    m_maxMove = 100;
    m_jump = 1;
    m_jumpEpsilon = 0.01;
    m_coefIntegerConversion = 100;
    m_maxCost = m_maxMove*m_maxMove;
}

SaLinkerGraph::SaLinkerGraph(SaCost* costFunction, std::vector<std::string>& framesFiles, std::vector< std::vector<SaDetection*> >& detections)
: SaLinker(costFunction, framesFiles, detections)
{
    m_maxMove = 100;
    m_jump = 1;
    m_jumpEpsilon = 0.01;
    m_coefIntegerConversion = 100;
    m_maxCost = m_maxMove*m_maxMove;
}


SaLinkerGraph::~SaLinkerGraph()
{

}

void SaLinkerGraph::run()
{
    //std::cout << "SaLinkerGraph::run() starts" << std::endl;
    this->runShortestPath();
    //std::cout << "SaLinkerGraph::run() ends" << std::endl;
}   

void SaLinkerGraph::setJump(unsigned int jump)
{
    m_jump = jump;
}

void SaLinkerGraph::setJumpPenalty(float penalty)
{
    m_jumpEpsilon = penalty;
}

void SaLinkerGraph::setCoefIntegerConversion(float coef)
{
    m_coefIntegerConversion = coef;
}

void SaLinkerGraph::setMaxCost(const float& maxCost)
{
    m_maxCost = maxCost;
}

void SaLinkerGraph::runShortestPath()
{
    //cout << endl << "updateShortestPath -> Begining" << endl;
    // build the graph
     // 1- Create the object list
    vector<SaDetection*> nodesData;
    vector<int> frameBreak;
    int countor = 0;
    for (unsigned int frame = 0 ; frame < m_detections.size() ; ++frame){
        for (unsigned int objIdx = 0 ; objIdx < m_detections[frame].size() ; ++ objIdx){
            countor++;
            nodesData.push_back(m_detections[frame][objIdx]);
        }
        frameBreak.push_back(countor+1);
    }

    // 2- Create the detection nodes
    std::vector<SaArc*> arcs;
    unsigned int nodesNumber = countor+2;
    unsigned int source = 0;
    unsigned int target = 1;

    // 3- create the arcs
    // 3.1- To source and target
    for (unsigned int i = 0 ; i < nodesNumber-2 ; ++i){
        // link to source
        arcs.push_back(new SaArc(source, i+2, 0));
        // link to target
        arcs.push_back(new SaArc(i+2, target, 0));
    }

    // 3.2- Between detections
    float curentCost;
    int cost;
    unsigned int frameNumber = m_framesFiles.size();
    for (unsigned int t=0 ; t<frameNumber-1 ; ++t){
        cout << "ConnectionManager -> connect frame: " << t << endl;

        // Get the number of future frame to scan depending on the remaining number of frames
        int endlength = 1;
        if (t < frameNumber-1-m_jump ){
            endlength = m_jump;
        }
        else{
            endlength = frameNumber-1-t;
        }
        //cout << "endlength = " << endlength << endl;
        // Fill the graph by scanning the connectons
        for (unsigned int p = t+1 ; p <= t+endlength ; ++p)
        {
            cout << "t = " << t << ", p = " << p << endl;
            cout << "t size = " << m_detections[t].size() << ", p size = " << m_detections[p].size() << endl;
            m_costFunction->loadDataCurentFrames(t, p);
            //cout << "blAtTrackerGraph finish load frames" << endl;
            for (unsigned int nt = 0 ; nt< m_detections[t].size() ; ++nt)
            {
                //cout << "\t nt = " << nt << endl;
                for (unsigned int np = 0 ; np<m_detections[p].size(); ++np)
                {
                    if (this->isLessMaxMove(m_detections[t][nt], m_detections[p][np]))
                    {    
                        curentCost = m_costFunction->calculateCost(m_detections[t][nt], m_detections[p][np]);

                        if (curentCost >= m_maxCost){
                            std::cout << "warning cost satturation" << std::endl;;
                            curentCost = m_maxCost;
                        }

                        // add arc to graph
                        int posObject1 = this->calculateNodeIdx(t, nt);
                        int posObject2 = this->calculateNodeIdx(p, np);
                        

                        if (p-t-1 > 0 )
                        {
                            cost = int((curentCost/m_maxCost -1 - (p-t-1) +0.01)*m_coefIntegerConversion);
                        }
                        else
                        {
                            cost = int((curentCost/m_maxCost -1.0)*m_coefIntegerConversion);
                        }
                        arcs.push_back(new SaArc(posObject1+2, posObject2+2, cost));
                    }
                }
            }
        }
    }

    // 4. shortest path optimization
    cout << "node num: " << nodesNumber << endl;
    cout << "arcs num: " << arcs.size() << endl << endl;

    SaGraph* graph = new SaGraph(arcs, nodesNumber);
    SaBellmanFord shortestPath(graph);

    bool stop = false;
    int iter = -1;
    int sp_out;
    while (!stop){
        iter++;
        if (iter%10 == 0){
            cout << "shortest path: Compute track " << iter << endl;
        }
        // shortest path
        sp_out = shortestPath.run(0);

        if (sp_out == 0){
            std::map<unsigned int, unsigned int> predecessors = shortestPath.predecessors();

            /// \todo add here a condition to stop: if track does not exits ?
            SaTrack *new_track = new SaTrack();
            std::vector<SaDetection*> new_track_d;;
            unsigned int predecessor = predecessors[target];
            while (predecessor > 0){
                new_track_d.push_back(nodesData[predecessor-2]);
                graph->removeNode(predecessor);
                predecessor = predecessors[predecessor];
            }
            std::reverse(new_track_d.begin(), new_track_d.end());
            new_track->setDetections(new_track_d);

            //std::cout << "found a track of length: " << new_track->size() << std::endl;

            if (new_track->size() <= 2){
                stop = true;
                delete new_track;
                break;
            }
            if (!stop){
                // create the new track
                m_tracks.push_back(new_track);
            }
        }
        else{
            stop = true;
        }
    }
    delete graph;

    cout << "shortest path: founded " << m_tracks.size() << " tracks" << endl;
}

int SaLinkerGraph::calculateNodeIdx( int t, int nt){
    int posCount = 0;
    //if ( t > 0 ){
    for (int i=0; i < t ; ++i){
        posCount += m_detections[i].size();
    }
    //}
    posCount+= nt;
    return posCount;
}