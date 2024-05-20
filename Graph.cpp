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
/*
Operator (+): Adds the adjacency matrices of two graphs, element-wise. 
Throws an error if the graphs have different numbers of vertices.
*/
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

/*
Operator (<<): Outputs the adjacency matrix of the graph in a readable format, row by row.
*/
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

/*
Operator (*=): Multiplies every element of the graph's adjacency matrix by a given scalar, excluding zero elements.
*/
void Graph::operator*=(int scalar) {
            for (size_t i = 0; i < v; ++i) {
                for (size_t j = 0; j < v; ++j) {
                    if(adjMat[i][j] != 0){
                    adjMat[i][j] *= scalar;
                    }
                }
            }
        }

/*
Operator (/=): Divides every element of the graph's adjacency matrix by a given scalar, excluding zero elements. 
Throws an error if the scalar is zero.
*/
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

/*
Operator (*): Performs matrix multiplication on the adjacency matrices of two graphs. 
Throws an error if the graphs have different numbers of vertices.
*/
Graph operator*(const Graph& g1, const Graph& g2) {
    if (g1.getNumVertices() != g2.getNumVertices()) {
        throw std::invalid_argument("The number of vertices in both graphs must be the same.");
    }

    // Create a new graph to store the result
    Graph result;

    // Get the number of vertices
    size_t n = g1.getNumVertices();

    // Initialize the result matrix with zeros
    std::vector<std::vector<int>> resultMatrix(n, std::vector<int>(n, 0));

    // Perform matrix multiplication
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                resultMatrix[i][j] += g1.adjMat[i][k] * g2.adjMat[k][j];
            }
        }
    }

    // Load the result matrix into the result graph
    result.loadGraph(resultMatrix);

    return result;
}

/*
Operator (++): Increments each non-zero element of the adjacency matrix by one.
*/
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

/*
Operator (--): Decrements each non-zero element of the adjacency matrix by one.
*/
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

/*
Operator (==): Checks if the adjacency matrices of two graphs are identical, first by size and then element-wise.
*/
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

/*
Operator (<=): Checks if one graph has fewer or equal edges compared to another and if every edge in the first graph exists in the second graph.
*/
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

/*
Operator (>=): Checks if one graph has more or equal edges compared to another and if every edge in the second graph exists in the first graph.
*/
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
