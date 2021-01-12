#include <vector>
#include <iostream>

#include <satracking/SaGraph.h>

int main(int argc, char* argv[])
{ 
    // create the graph
    std::vector<SaArc*> arcs;
    unsigned int nodesNumber = 5;
    arcs.push_back(new SaArc(0, 1, -1));
    arcs.push_back(new SaArc(0, 5, 4));
    arcs.push_back(new SaArc(1, 5, 3));
    arcs.push_back(new SaArc(12, 5, 5));
    arcs.push_back(new SaArc(12, 1, 1));
    arcs.push_back(new SaArc(1, 12, 2));
    arcs.push_back(new SaArc(1, 24, 2));
    arcs.push_back(new SaArc(24, 12, -3));

    std::vector<unsigned int> nodes;
    nodes.resize(5);
    nodes[0] = 0;
    nodes[1] = 1;
    nodes[2] = 5;
    nodes[3] = 12;
    nodes[4] = 24;

    SaGraph* graph = new SaGraph(arcs, nodes);

    // bellman ford
    SaBellmanFord shortestPath(graph);
    shortestPath.run(0);
    std::map<unsigned int, int> dist = shortestPath.distances();
    
    // distances must be 0, -1, 2, -2, 1
    if (dist[0] != 0){
        return 1;
    } 
    if (dist[1] != -1){
        return 1;
    }   
    if (dist[5] != 2){
        return 1;
    }  
    if (dist[12] != -2){
        return 1;
    } 
    if (dist[24] != 1){
        return 1;
    }     
    /*
    // print for debuging
    std::cout << "distances:" << std::endl;
    std::map<unsigned int, int>::iterator it = dist.begin();
    while (it != dist.end())
    {
        std::cout << "d[" << it->first << "]: " << it->second << std::endl;
        it++;
    }
    */

    // plot the path
    std::vector<unsigned int> path = shortestPath.path(12);
    // path must be 0, 1, 4, 3
    if (path[0] != 0){
        return 2;
    }
    if (path[1] != 1){
        return 2;
    }
    if (path[2] != 24){
        return 2;
    }
    if (path[3] != 12){
        return 2;
    }

    // print for debuging
    /*
    std::cout << "path to node 12: "; 
    for (int i = 0 ; i < path.size() ; i++ )
    {
        std::cout << path[i] << ", ";
    }
    std::cout << std::endl;
    */

    return 0;
}
