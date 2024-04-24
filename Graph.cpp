#include "Graph.hpp" 

#include <iostream>
#include <vector>
#include <limits>

namespace ariel
    {
    
        Graph::Graph() {
            
        }

        void Graph::loadGraph(const std::vector<std::vector<int>>& matrix){
            adjMat = matrix;
            computeShortestPaths();

        }

        void Graph::printGraph() const{
            int vertices = adjMat.size();
            int edges = 0;

            for(size_t i = 0; i < adjMat.size(); ++i){
                for(size_t j = 0; j < adjMat[i].size(); ++j){
                    if(adjMat[i][j] != 0){
                        edges++;
                    }
                }
            }
            std::cout << "Graph with " << vertices << " vertices and " << edges << " edges.";
        }

   
    
} // namespace ariel
