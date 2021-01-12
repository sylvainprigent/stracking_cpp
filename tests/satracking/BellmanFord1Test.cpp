#include <vector>
#include <iostream>

#include <satracking/SaGraph.h>

int main(int argc, char* argv[])
{ 
    // create the graph
    std::vector<SaArc*> arcs;
    unsigned int nodesNumber = 5;
    arcs.push_back(new SaArc(0, 1, -1));
    arcs.push_back(new SaArc(0, 2, 4));
    arcs.push_back(new SaArc(1, 2, 3));
    arcs.push_back(new SaArc(3, 2, 5));
    arcs.push_back(new SaArc(3, 1, 1));
    arcs.push_back(new SaArc(1, 3, 2));
    arcs.push_back(new SaArc(1, 4, 2));
    arcs.push_back(new SaArc(4, 3, -3));

    std::vector<unsigned int> nodes;
    nodes.resize(5);
    nodes[0] = 0;
    nodes[1] = 1;
    nodes[2] = 2;
    nodes[3] = 3;
    nodes[4] = 4;

    SaGraph* graph = new SaGraph(arcs, nodes);

    // bellman ford
    SaBellmanFord shortestPath(graph);
    shortestPath.run(0);
    std::map<unsigned int, int> dist = shortestPath.distances();
    
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

    // distances must be 0, -1, 2, -2, 1
    if (dist[0] != 0){
        return 1;
    } 
    if (dist[1] != -1){
        return 1;
    }   
    if (dist[2] != 2){
        return 1;
    }  
    if (dist[3] != -2){
        return 1;
    } 
    if (dist[4] != 1){
        return 1;
    }     
    
    // plot the path
    std::vector<unsigned int> path = shortestPath.path(3);
    
    /*
    // print for debuging
    std::cout << "path to node 12: "; 
    for (int i = 0 ; i < path.size() ; i++ )
    {
        std::cout << path[i] << ", ";
    }
    std::cout << std::endl;
    */

    // path must be 0, 1, 4, 3
    if (path[0] != 0){
        return 2;
    }
    if (path[1] != 1){
        return 2;
    }
    if (path[2] != 4){
        return 2;
    }
    if (path[3] != 3){
        return 2;
    }
    
    return 0;
}
