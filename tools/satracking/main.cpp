#include <iostream>
#include <fstream>

#include <score>
#include <scli>
#include <sdataio>
#include <satracking>

#include "SaFactories.h"

int main(int argc, char *argv[])
{
    SObserverConsole* observer = new SObserverConsole();
    try
    {
        SCliParser cmdParser(argc, argv);
        cmdParser.addInputData("-i", "txt file with the list of frames images path");
        cmdParser.addInputData("-d", "txt file with the list of frames detection files path");
        cmdParser.addOutputData("-t", "txt file containing the tracks");
        cmdParser.addOutputData("-v", "root filename of the trajectory representation");

        cmdParser.addParameterString("-p", "Parameter file (JSON)", "");
        cmdParser.setMan("Track spots in an image sequence using detections at each frame");
        cmdParser.parse(4);

        std::string inputFramesFiles = cmdParser.getDataURI("-i");
        std::string inputDetectionsFiles = cmdParser.getDataURI("-d");
        std::string outputTrackTxtFile = cmdParser.getDataURI("-t");
        std::string outputRepresentationRootFile = cmdParser.getDataURI("-v");

        const std::string parametersFile = cmdParser.getParameterString("-p");

        if (inputDetectionsFiles == ""){
            observer->message("AssociationTracker: Input detection path is empty");
            return 1;
        }

        bool verbose = true;
        if (verbose){
            observer->message("AssociationTracker: input frames file: " + inputFramesFiles);
            observer->message("AssociationTracker: input detection file: " + inputDetectionsFiles);
            observer->message("AssociationTracker: output tracks txt files: " + outputTrackTxtFile);
            observer->message("AssociationTracker: output representation root path: " + outputRepresentationRootFile);
            observer->message("AssociationTracker: Parameters file: " + parametersFile);
        }

        // load the frames list
        std::vector< std::string > framesFiles;
        if (inputFramesFiles != ""){
            std::fstream framesFile;
            framesFile.open(inputFramesFiles, std::ios::in);
            if (framesFile.is_open()){
                std::string tp;
                while(getline(framesFile, tp)){ 
                    framesFiles.push_back(tp);
                }
                framesFile.close(); 
            }
        }

        std::cout << "Frames:" << std::endl;
        for (int i = 0 ; i < framesFiles.size() ; i++){
            std::cout << "\t" << framesFiles[i] << std::endl;
        }

        // load the detections
        std::vector< std::vector< SaDetection*> > detections;
        if (inputDetectionsFiles != ""){
            detections = SaDetectionReader::readDetectionsList(inputDetectionsFiles);
        }

        std::cout << "Detections:" << std::endl;
        for (int t = 0 ; t < detections.size() ; t++){
            std::cout << "t" << t << std::endl; 
            for (int i = 0 ; i < detections[t].size() ; i++){
                std::cout << "\t" << detections[t][i]->x() << ", " << detections[t][i]->y() << ", " << detections[t][i]->z() << std::endl;
            }
        }

        // load the parameters
        SJSON jsonReader;
        jsonReader.read(parametersFile);
        SObject* parameters = dynamic_cast<SObject*>(jsonReader.get());

        std::cout << "SaCost=" << dynamic_cast<SString*>(parameters->get("SaCost"))->get() << std::endl;
        std::cout << "SaLinker=" << dynamic_cast<SString*>(parameters->get("SaLinker"))->get() << std::endl;

        // get the cost function and linker
        SaFactories factory(parameters);
        SaCost* cost = factory.cost(dynamic_cast<SString*>(parameters->get("SaCost"))->get());
        SaLinker* linker = factory.linker(dynamic_cast<SString*>(parameters->get("SaLinker"))->get());

        // initialize the linker
        linker->setCost(cost);
        linker->setFramesFiles(framesFiles);
        linker->setDetections(detections);

        // run the tracking
        linker->run();

        // save the outputs
        if (outputTrackTxtFile != ""){
            linker->saveTracksToTxt(outputTrackTxtFile);
        }
        if (outputRepresentationRootFile != ""){
            linker->saveTracksMoviePlot(outputRepresentationRootFile);
        }

        delete linker;
        delete cost;
        delete parameters;
    }
    catch (SException &e)
    {
        observer->message(e.what(), SObserver::MessageTypeError);
        return 1;
    }
    catch (std::exception &e)
    {
        observer->message(e.what(), SObserver::MessageTypeError);
        return 1;
    }
    delete observer;
    return 0;
}