/*
ID: 206769986
E-Mail: avihyb@gmail.com
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_set>

namespace ariel {
    class Graph {
    public:
        std::vector<std::vector<int>> adjMat; // Adjantency Matrix 
        bool isDirected; 
        bool hasNegativeCycle;
        bool hasNegativeEdges;
        std::string cycle;
        size_t v; // Number of vertices
        int edges; // Number of edges
        
        // PART I: CONSTRUCTOR AND BASIC FUNCTIONS
        Graph();
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
        inline size_t getNumVertices() const{ return adjMat.size(); };
        inline std::string getCycle(){ return cycle; }
        inline void setCycle(std::string foundcycle) { cycle = foundcycle;}
        inline int getEdges(){ return edges; }
        
        // PART II: OPERATORS
        Graph operator+(const Graph& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
        void operator*=(int scalar);
        void operator/=(int scalar);
        Graph& operator+=(const Graph& other);
        Graph& operator-=(const Graph& other);
        friend Graph operator*(const Graph& g1, const Graph& g2);
        friend Graph& operator++(Graph& graph);
        friend Graph& operator--(Graph& graph);
        friend bool operator==(const Graph& g1, const Graph& g2);
        friend bool operator<=(const Graph& g1, const Graph& g2);
        friend bool operator>=(const Graph& g1, const Graph& g2);
        bool operator<(const Graph& other);
        Graph& operator+();
        Graph& operator-();
        bool operator!=(const Graph& other);
    };
} // namespace ariel

#endif 