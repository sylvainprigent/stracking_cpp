#include <vector>
#include <iostream>

#include <satracking>

#include "SaTrackingTestConfig.h"

int main(int argc, char* argv[])
{ 
 
    std::string inputFramesFiles(TRACKS1_FRAMES);
    std::string inputDetectionsFiles(TRACKS1_DETECTIONS);

    std::cout << "inputFramesFiles: " << inputFramesFiles << std::endl;
    std::cout << "inputDetectionsFiles: " << inputDetectionsFiles << std::endl;

    // load the frames list
    std::vector< std::string > framesFiles = SaFramesReader::readFramesList(inputFramesFiles);
    // load the detections
    std::vector< std::vector<SaDetection*> > detections = SaDetectionReader::readDetectionsList(inputDetectionsFiles);
    
    // build the pipeline
    SaCost* cost = new SaCostEuclidean;
    SaLinker *linker = new SaLinkerNaive(cost, framesFiles, detections);
    linker->setMaxMove(100);

    // run the tracking
    linker->run();

    // test the outputs
    std::vector<SaTrack*> tracks = linker->getTracks();
    if ( tracks.size() != 3)
    {
        return 1;
    }
    for (int i = 0 ; i < tracks.size() ; i++)
    {    
        if (tracks[i]->size() != 5){
            return 2;
        }
    }
    return 0;
}
