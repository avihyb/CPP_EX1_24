#include "Graph.hpp"

namespace ariel {

    Graph::Graph() {    }

    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix){
        // Clear previous data
        adjMat.clear();
        isDirected = false;
        hasNegativeEdges = false;
        int n = matrix.size();
        edges = 0;

        // Check if the matrix is square
        for (size_t i = 0; i < n; ++i) {
            if (matrix[i].size() != n) {
                throw std::invalid_argument("Error: Matrix is not square!");
            }
        }

      // Check if the matrix is symmetric
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (matrix[i][j] != matrix[j][i]) {
                    this->isDirected = true;
                    break; // Exit the inner loop
                }
            }
            if (this->isDirected) {
                break; // Exit the outer loop
            }
        }
       // std::cout << "isDirected: " << isDirected << std::endl;

        // Check if there are negative edges
        for(size_t i = 0; i < n; ++i){
            for (size_t j = 0; j < n; ++j) {
                if(matrix[i][j] < 0){
                    hasNegativeEdges = true;
                    break; // Exit the inner loop
                }
            }
            if (hasNegativeEdges) {
                break; // Exit the outer loop
            }
        }

        
        // Update number of vertices and edges
        v = static_cast<size_t>(n);
        

        // Copy matrix to adjMat
        adjMat = matrix;

        // Count edges
        for(size_t i = 0; i < n; ++i){
            for(size_t j = 0; j < n; ++j){
                if(adjMat[i][j] != 0){
                    edges++;
                }
            }
        }

        // For undirected graph, divide edge count by 2
        if(!isDirected){
            edges = edges / 2;
        }

        
    }

    size_t Graph::getNumVertices() const{
        return v;
    }

    void Graph::printGraph() const{
        std::cout << "Graph with " << v << " vertices and " << edges << " edges." << std::endl;
    }

} // namespace ariel
