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
        bool hasNegativeCycle;
        bool hasNegativeEdges;
        std::string cycle;
        size_t v;
        int edges;
        std::unordered_set<int> sets[2];

        Graph();
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        void printGraph() const;
        inline size_t getNumVertices() const{ return adjMat.size(); };
        inline std::string getCycle(){ return cycle; }
        inline void setCycle(std::string foundcycle) { cycle = foundcycle;}
        
    };
} // namespace ariel

#endif 