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
            void FloydWarshall(Graph& g);
            static void DFS(Graph& g, int v, std::unordered_set<int>& visited);
            static int isConnected(Graph& g);
            static std::string shortestPath(Graph& g, int start, int end);
            static bool isContainsCycle(Graph& g);
            static std::string printCycle(Graph& g);
            static std::string isBipartite(Graph& g);
            static int negativeCycle(Graph& g);
            
        };
} // namespace ariel

#endif 
