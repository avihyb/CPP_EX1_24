#include "Algorithms.hpp"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <string>

/*
Code Explainations:

    (I). visited.find(x) searches for x element, returns a pointer to that element if found.
         If not, returns an iterator pointing to the end of the set (aka visited.end()).
         Thus, "visited.find(x) == visited.end()" is equalivant of checking if the element isn't in the set.

*/
namespace ariel
{

    /*
    
    */
void Algorithms::FloydWarshall(Graph& g){
    if(g.shortestPathsComputed == false){
    int numVertices = static_cast<int>(g.adjMat.size());
            g.shortestPaths = g.adjMat; 

            for (size_t k = 0; k < numVertices; ++k) {
                for (size_t i = 0; i < numVertices; ++i) {
                    for (size_t j = 0; j < numVertices; ++j) {
                        if (g.shortestPaths[i][k] != std::numeric_limits<int>::max() &&
                            g.shortestPaths[k][j] != std::numeric_limits<int>::max() &&
                            g.shortestPaths[i][k] + g.shortestPaths[k][j] < g.shortestPaths[i][j]) {
                            g.shortestPaths[i][j] = g.shortestPaths[i][k] + g.shortestPaths[k][j];
                        }
                    }
                }
            }

             for (size_t i = 0; i < g.shortestPaths.size(); ++i) {
                if (g.shortestPaths[i][i] < 0) {
                g.hasCycle = true;// Detected a negative cycle
        }
    }
    } else {
        return;
    }
}

    /*
        DFS: depth-first search, starting from a given vertex in the graph.
        Visits all reachable vertices recursively, marking each visited vertex in the visited set.
        @return void
    */
void Algorithms::DFS(Graph& g, int v, std::unordered_set<int>& visited) {
    visited.insert(v);
    for (const auto& neighbors : g.adjMat) {
        for (int neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                DFS(g, neighbor, visited);
            }
        }
    }
}

    /*
        isConnected: Using DFS traversal,
        if all vertices are visited => graph is connected. Otherwise, it's not.
        @return 1 if connected, 0 if not.
    */
int Algorithms::isConnected(Graph& g) {
    
    std::unordered_set<int> visited;
    DFS(g, 0, visited);

    for(int i = 0; i < g.adjMat.size(); ++i){
        if(visited.find(i) == visited.end()){ // If vertex 'i' isn't in the visited set. (I)
            return 0;
        }
    }
    return 1;
}

    /*
        shortestPath: Using the All-Pairs ShortestPath matrix (computed upon graph creation)
        the function checks if there's path and tracks the shortest path.
        @return string representing the Shortest Path, or -1 in case there's no path.
    */
std::string Algorithms::shortestPath(Graph& g, int start, int end) {
    // Check if start and end vertices are valid
    if (start < 0 || start >= static_cast<int>(g.adjMat.size()) || end < 0 || end >= static_cast<int>(g.adjMat.size())) {
        return "-1"; 
    }

    // Check if there is a shortest path from start to end
    if (g.shortestPaths[static_cast<size_t>(start)][static_cast<size_t>(end)] == std::numeric_limits<int>::max()) {
        return "-1"; 
    }

    // Reconstruct the shortest path
    std::string shortestPath; // Shortest Path will be stored in this string.
    int current = start;
    shortestPath += std::to_string(current);

    while (current != end) {
            int next = -1;
            for (size_t vertex = 0; vertex < g.adjMat.size(); ++vertex) {
                if (g.shortestPaths[static_cast<size_t>(current)][static_cast<size_t>(vertex)] != std::numeric_limits<int>::max() &&
                    g.shortestPaths[static_cast<size_t>(vertex)][static_cast<size_t>(end)] != std::numeric_limits<int>::max() &&
                    g.shortestPaths[static_cast<size_t>(current)][static_cast<size_t>(end)] == g.shortestPaths[static_cast<size_t>(current)][static_cast<size_t>(vertex)] + g.shortestPaths[static_cast<size_t>(vertex)][static_cast<size_t>(end)]) {
            next = vertex;
            break;
            }

            }
            if (next == -1) {
                return "-1"; // Error in path reconstruction, return "-1"
            }
            shortestPath += "->" + std::to_string(next);
            current = next;
        }

    return shortestPath; // Return the shortest path
}

    /*
        isContainsCycle: Using the ShortestPaths of a graph, this function scans for a 
        cycle. If a cycle is found it returns a string representing the cycle. If none found it returns "0";
        @return any cycle from the graph, -1 if there's none.
    */
bool Algorithms::isContainsCycle(Graph& g) {
    
    negativeCycle(g);
    if(g.hasCycle){
        return true; }

        return false;
        
}

std::string Algorithms::printCycle(Graph& g){
        std::string cycle;
    // Backtrack the cycle and construct the string representation
        cycle = "Cycle found: ";
        int cycleStartVertex;
        for (size_t i = 0; i < g.shortestPaths.size(); ++i) {
            if (g.shortestPaths[i][i] < 0) {
                cycleStartVertex = static_cast<int>(i);
                break;
            }
        }
        int currentVertex = cycleStartVertex;
        std::unordered_set<int> visited;
        while (visited.find(currentVertex) == visited.end()) {
            visited.insert(currentVertex);
            cycle += std::to_string(currentVertex) + " -> ";
            // Move to the next vertex in the cycle
            for (size_t vertex = 0; vertex < g.adjMat.size(); ++vertex) {
                if (g.shortestPaths[static_cast<size_t>(currentVertex)][vertex] != std::numeric_limits<int>::max() &&
                    g.shortestPaths[vertex][static_cast<size_t>(cycleStartVertex)] != std::numeric_limits<int>::max() &&
                    g.shortestPaths[static_cast<size_t>(currentVertex)][vertex] + g.shortestPaths[vertex][static_cast<size_t>(cycleStartVertex)] == g.shortestPaths[static_cast<size_t>(currentVertex)][static_cast<size_t>(cycleStartVertex)]) {
                    currentVertex = static_cast<int>(vertex);
                    break;
                }
            }
        }
        // Remove the last "->" from the cycle string
        cycle.pop_back();
        cycle.pop_back();

        return cycle;
    }

    


    /*
        isBipartite: 
        @return string representing the 2 disticnt vertices sets. 0 if not bipartite. 
    */
    std::string Algorithms::isBipartite(Graph& g) {
        std::vector<int> colors(g.adjMat.size(), -1); // Initialize colors for each vertex (-1 represents uncolored)
        std::queue<size_t> q;

        // Start BFS traversal from every uncolored vertex
        for (size_t i = 0; i < g.adjMat.size(); ++i) {
            if (colors[i] == -1) {
                q.push(i);
                colors[i] = 0; // Color the vertex with 0
            }

            while (!q.empty()) {
                size_t v = q.front();
                q.pop();

                for (int neighbor : g.adjMat[v]) {
                    if (colors[static_cast<size_t>(neighbor)] == -1) {
                        colors[static_cast<size_t>(neighbor)] = 1 - colors[v]; // Assign opposite color to the neighbor
                        q.push(static_cast<size_t>(neighbor));
                    } else if (colors[static_cast<size_t>(neighbor)] == colors[v]) {
                        return "0";
                    }
                }
            }
        }

        // Construct sets of vertices based on colors
        std::vector<int> setA, setB;
        for (size_t i = 0; i < g.adjMat.size(); ++i) {
            if (colors[i] == 0) {
                setA.push_back(i);
            } else {
                setB.push_back(i);
            }
        }

        // Construct the string representation of bipartite sets
        std::string bipartiteSets = "The graph is bipartite: ";
        bipartiteSets += "A={";
        for (size_t i = 0; i < setA.size(); ++i) {
            bipartiteSets += std::to_string(setA[i]);
            if (i < setA.size() - 1) {
                bipartiteSets += ", ";
            }
        }
        bipartiteSets += "}, B={";
        for (size_t i = 0; i < setB.size(); ++i) {
            bipartiteSets += std::to_string(setB[i]);
            if (i < setB.size() - 1) {
                bipartiteSets += ", ";
            }
        }
        bipartiteSets += "}.";

        return bipartiteSets;
    }


    /*
        negativeCycle:
        @return 1 if there's a negative cycle, 0 if there isn't. (Will also print "No negative cycle in this graph").
    */
    int Algorithms::negativeCycle(Graph& g) {
        size_t vertices = g.shortestPaths.size();
        for(size_t i = 0; i < vertices; ++i){
            if(g.shortestPaths[i][i] < 0){
                return 1;
                g.hasCycle = true;
            }
        }
        std::cout << "No negative cycle in this graph";
        return 0;
    }
    

} // namespace ariel
