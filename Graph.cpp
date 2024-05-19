/*
ID: 206769986
E-Mail: avihyb@gmail.com
*/
#include "Graph.hpp"
#include <iostream>

namespace ariel {

    Graph::Graph() {    }

    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix){
        this->adjMat.clear(); // Clear previous data
        this->cycle.erase();
        this->isDirected = false;
        this->hasNegativeEdges = false;
        this->hasNegativeCycle = false;
        int n = matrix.size();
        this->edges = 0;
        
        
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
                    this->hasNegativeEdges = true;
                    break; // Exit the inner loop
                }
            }
            if (this->hasNegativeEdges) {
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

Graph Graph::operator+(const Graph& other) const {
        Graph result;
        if (this->v != other.getNumVertices()) {
            throw std::invalid_argument("Error: Cannot add graphs with different number of vertices!");
        }
        std::vector<std::vector<int>> resultMatrix(this->v, std::vector<int>(this->v, 0));
        for (size_t i = 0; i < this->v; ++i) {
            for (size_t j = 0; j < this->v; ++j) {
                resultMatrix[i][j] = this->adjMat[i][j] + other.adjMat[i][j];
            }
        }
        result.loadGraph(resultMatrix);
        return result;
    }
    void Graph::printGraph() const{
        std::cout << "Graph with " << v << " vertices and " << edges << " edges." << std::endl;
    }

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        // Output the adjacency matrix in the desired format
        
        for (size_t i = 0; i < graph.v; ++i) {
            os << "[";
            for (size_t j = 0; j < graph.v; ++j) {
                os << graph.adjMat[i][j];
                if (j < graph.v - 1) {
                    os << ", ";
                }
            }
            os << "]";
            if (i < graph.v - 1) {
                os << ", ";
            }
        }
        os << std::endl;

        return os;
    }

void Graph::operator*=(int scalar) {
            for (size_t i = 0; i < v; ++i) {
                for (size_t j = 0; j < v; ++j) {
                    if(adjMat[i][j] != 0){
                    adjMat[i][j] *= scalar;
                    }
                }
            }
        }

void Graph::operator/=(int scalar) {
            if (scalar == 0) {
                throw std::invalid_argument("Error: Division by zero!");
            }

            // Divide each element of the adjacency matrix by the scalar
            for (size_t i = 0; i < v; ++i) {
                for (size_t j = 0; j < v; ++j) {
                    adjMat[i][j] /= scalar;
                }
            }
        }

 Graph operator*(const Graph& g1, const Graph& g2) {
        if (g1.getNumVertices() != g2.getNumVertices()) {
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }

    // Create a new graph to store the result
    Graph result;

    // Get the number of vertices
   size_t n = g1.getNumVertices();

    // Initialize the result matrix with zeros
    std::vector<std::vector<int>> resultMatrix(n, std::vector<int>(n, 0));

    // Perform element-wise multiplication
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            resultMatrix[i][j] = g1.adjMat[i][j] * g2.adjMat[i][j];
        }
    }

    // Load the result matrix into the result graph
    result.loadGraph(resultMatrix);

    return result;
    }

Graph& operator++(Graph& graph) {
    
    for (size_t i = 0; i < graph.getNumVertices(); ++i) {
        for (size_t j = 0; j < graph.getNumVertices(); ++j) {
            if(graph.adjMat[i][j] != 0){
                graph.adjMat[i][j]++;
            }
        }
    }
    return graph;
}

Graph& operator--(Graph& graph) {
    
    for (size_t i = 0; i < graph.getNumVertices(); ++i) {
        for (size_t j = 0; j < graph.getNumVertices(); ++j) {
            if(graph.adjMat[i][j] != 0){
                graph.adjMat[i][j]--;
            }
        }
    }
    return graph;
}

bool operator==(const Graph& g1, const Graph& g2) {
    
    if (g1.getNumVertices() != g2.getNumVertices()) {
        return false;
    }

    
    for (size_t i = 0; i < g1.getNumVertices(); ++i) {
        for (size_t j = 0; j < g1.getNumVertices(); ++j) {
            if (g1.adjMat[i][j] != g2.adjMat[i][j]) {
                return false;
            }
        }
    }

    
    return true;
}

bool operator<=(const Graph& g1, const Graph& g2){
    if(g1.edges > g2.edges){
        return false;
    }

    for (size_t i = 0; i < g1.getNumVertices(); ++i) {
        for (size_t j = 0; j < g1.getNumVertices(); ++j) {
            if (g1.adjMat[i][j] != 0 && g2.adjMat[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}

bool operator>=(const Graph& g1, const Graph& g2){
    if(g1.edges < g2.edges){
        return false;
    }

    for (size_t i = 0; i < g1.getNumVertices(); ++i) {
        for (size_t j = 0; j < g1.getNumVertices(); ++j) {
            if (g1.adjMat[i][j] == 0 && g2.adjMat[i][j] != 0) {
                return false;
            }
        }
    }

    return true;
}
}  // namespace ariel
