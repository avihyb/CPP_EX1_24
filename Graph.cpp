/*
ID: 206769986
E-Mail: avihyb@gmail.com
*/

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <vector>
#include <limits>


namespace ariel
    {
    
        Graph::Graph() {
            
        }

        void Graph::loadGraph(const std::vector<std::vector<int>>& matrix){

            int n = matrix.size();
            bool isSymmetric = true;
            
            // Check if the matrix is square
            for (size_t i = 0; i < n; ++i) {
                if (matrix[i].size() != n) {
                    std::cerr << "Error: Matrix is not square!" << std::endl;
                    return;
                }
            }

            // Check if the matrix is symmetric
            for (size_t i = 0; i < n && isSymmetric; ++i) {
                for (size_t j = 0; j < n && isSymmetric; ++j) {
                    if (matrix[i][j] != matrix[j][i]) {
                        isSymmetric = false;
                    }
                }
            }

            for(size_t i = 0; i < n; ++i){
                for (size_t j = 0; i < matrix[0].size(); i++)
                {
                    if(matrix[i][j] < 0){
                        hasNegativeEdges = true;
                        break;
                    }
                }
                
            }
            if(!isSymmetric){
                isDirected = true;
            }
        
            adjMat = matrix;

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

            if(!isDirected){
                edges = edges / 2;
            }

            std::cout << "Graph with " << vertices << " vertices and " << edges << " edges." << std::endl;
        }

   
    
} // namespace ariel
