/// \file SaLinkerNaive.h
/// \brief SaTracker class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#include <iostream>

#include "SaLinkerNaive.h"

SaLinkerNaive::SaLinkerNaive() : SaLinker()
{

}

SaLinkerNaive::SaLinkerNaive(SaCost* costFunction, std::vector<std::string>& framesFiles, std::vector< std::vector<SaDetection*> >& detections)
: SaLinker(costFunction, framesFiles, detections)
{

}

SaLinkerNaive::~SaLinkerNaive()
{

}

void SaLinkerNaive::run()
{
    m_tracks.clear();

    std::cout << "tracker detection frame count = " << m_detections.size() << std::endl;

    // set all the detections as dummies
    std::vector<SaDetection*> dummies = m_detections[0];

    std::vector<SaDetection*> targets;
    for (int t = 1 ; t < m_detections.size() ; t++)
    {
        targets = m_detections[t];
        
        // connect trajectories to targets
        for (int l = 0 ; l < m_tracks.size() ; l++){
            SaDetection* last_detection = m_tracks[l]->last();
            if (last_detection->t() == t-1){
                // search the less cost connection to tagets
                float min_cost = 9999999999999999.9; 
                int min_pos = -1;
                for (int i = 0 ; i < targets.size() ; i++){
                    if (this->isLessMaxMove(last_detection, targets[i])){
                        float cost_i = m_costFunction->calculateCost(last_detection, targets[i], m_tracks[l]);
                        if (cost_i < min_cost){
                            min_cost = cost_i;
                            min_pos = i;
                        }      
                    }
                }
                if (min_pos > -1){
                    m_tracks[l]->append(targets[min_pos]);
                    targets.erase(targets.begin()+min_pos); // remove the target
                }
            }
        }

        // connect dummies to targets
        for (int l = 0 ; l < dummies.size() ; l++){
            // search the less cost connection to tagets
            float min_cost = 99999999999999999.9; 
            int min_pos = -1;
            for (int i = 0 ; i < targets.size() ; i++){
                if (this->isLessMaxMove(dummies[l], targets[i])){
                    float cost_i = m_costFunction->calculateCost(dummies[l], targets[i]);
                    if (cost_i < min_cost){
                        min_cost = cost_i;
                        min_pos = i;
                    }  
                }    
            }
            if (min_pos > -1){
                SaTrack* new_track = new SaTrack;
                new_track->append(dummies[l]);
                new_track->append(targets[min_pos]);
                m_tracks.push_back(new_track);
                targets.erase(targets.begin()+min_pos); // remove the target
            }
        }
        dummies = targets;
    }

}