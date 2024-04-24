#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

namespace ariel {
    class Graph {
    public:
        std::vector<std::vector<int>> adjMat;
        std::vector<std::vector<int>> shortestPaths;
        bool hasCycle;
        bool shortestPathsComputed;
        bool isConnected;

        Graph();
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
        void computeShortestPaths();
    };
} // namespace ariel

#endif 