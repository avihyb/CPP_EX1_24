/*
ID: 206769986
E-Mail: avihyb@gmail.com
*/

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <vector> // Used to create 2D adjacency matrix.
#include <unordered_set> // Essential in keeping track of visited vertices.
#include <queue>
#include <limits>
#include <iostream>
#include <string>

namespace ariel {
        class Algorithms{
            public:
            static void BFS(Graph& g, int v, std::vector<bool>& visited);
            static int isConnected(Graph& g);
            static std::string shortestPath(Graph& g, size_t start, size_t end);
            static void BellmanFord(Graph& g, size_t start, std::vector<int>& prev, std::vector<int>& dist);
            static void Relax(size_t u, size_t v, int w, std::vector<int>& prev, std::vector<int>& dist);
            static std::string printPath(std::vector<int>& dist, std::vector<int>& prev, size_t start, size_t end);
            static std::string isContainsCycle(Graph& g);
            static std::string constructCycle(Graph& g, std::vector<int>& parent, int start);
            static bool detectCycleDFS(const Graph& graph, size_t v, std::vector<bool>& visited, std::vector<bool>& stack, std::string& cycle);
            static bool bipartite(Graph& g, std::vector<std::vector<int>>& edges, int start, std::vector<bool>& visited);
            static bool isBipartite(Graph& g);
            static int negativeCycle(Graph& g);
            
            };
            
} // namespace ariel

#endif 
