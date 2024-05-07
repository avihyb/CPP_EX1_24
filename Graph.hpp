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
        std::vector<std::vector<int>> adjMat;
        std::vector<std::vector<int>> shortestPaths;
        bool isDirected;
        bool hasCycle;
        bool hasNegativeEdges;
        size_t v;
        int edges;
        std::unordered_set<int> sets[2];

        Graph();
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
        size_t getNumVertices() const;
        
    };
} // namespace ariel

#endif 