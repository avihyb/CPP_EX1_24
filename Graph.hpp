/*
ID: 206769986
E-Mail: avihyb@gmail.com
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <limits>

namespace ariel {
    class Graph {
    public:
        std::vector<std::vector<int>> adjMat;
        std::vector<std::vector<int>> shortestPaths;
        bool isDirected;
        bool hasCycle;
        bool hasNegativeEdges;

        Graph();
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
        
    };
} // namespace ariel

#endif 