/*
ID: 206769986
E-Mail: avihyb@gmail.com
*/

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <unordered_set> 
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stack>



/*
Code Explainations:


*/
namespace ariel
{

const int INF = std::numeric_limits<int>::max();

/*
    BFS: 
    Performs Breadth-First Search (BFS) on the given graph starting from a specified vertex.
    @param Graph& g: Reference to the graph object.
    @param int v: The starting vertex for BFS.
    @param std::vector<bool>& visited: Reference to a boolean vector to mark visited vertices.
    @return void
*/
void Algorithms::BFS(Graph& g, int v, std::vector<bool>& visited) {
    std::queue<int> q;
    q.push(v);
    visited[static_cast<size_t>(v)] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (size_t i = 0; i < g.adjMat[static_cast<size_t>(current)].size(); ++i) {
            if (g.adjMat[static_cast<size_t>(current)][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

/*
    isConnected: 
    Checks whether the graph is connected or not. For directed graphs, it uses BFS from each vertex to determine connectivity. For undirected graphs, it performs BFS starting from a single vertex (vertex 0 by default).
    @param Graph& g: Reference to the graph object.
    @return int: 0 for not connected, 1 for connected.
*/
int Algorithms::isConnected(Graph& g) {
     if (g.getNumVertices() <= 1) {
            //std::cerr << "Error: Graph has 1 or less vertices." << std::endl;
            return 0; }
    if (g.isDirected) {
        std::vector<bool> visited(g.adjMat.size(), false);

        // Perform BFS starting from each node
        for (int i = 0; i < g.adjMat.size(); ++i) {
            std::vector<bool> tempVisited(g.adjMat.size(), false);
            BFS(g, i, tempVisited);
            // Merge tempVisited into visited
            for (int j = 0; j < visited.size(); ++j) {
                visited[static_cast<size_t>(j)] = visited[static_cast<size_t>(j)] && tempVisited[static_cast<size_t>(j)];
            }
        }

        // Check if all nodes are visited
        for (bool v : visited) {
            if (!v) return 0; // Not connected
        }
        return 1; // Connected
    } else {
        // Implement logic to check if an undirected graph is connected using BFS
        std::vector<bool> visited(g.adjMat.size(), false);

        // Perform BFS starting from node 0
        BFS(g, 0, visited);

        // Check if all nodes are visited
        for (bool v : visited) {
            if (!v) return 0; // Not connected
        }
        return 1; // Connected
    }
}

/*
    shortestPath:
    Finds the shortest path from a specified start vertex to an end vertex in the graph using the Bellman-Ford algorithm. 
    Handles negative cycles if present.
    @param Graph& g: Reference to the graph object.
    @param size_t start: Index of the starting vertex.
    @param size_t end: Index of the end vertex.
    @return std::string: String representing the shortest path or "-1" if no path exists.
*/
std::string Algorithms::shortestPath(Graph& g, size_t start, size_t end) {

    if (start < 0 || start >= g.getNumVertices() || end < 0 || end >= g.getNumVertices()) {
            // Invalid start or end vertex index
            //std::cerr << "Error: Invalid start or end vertex index for shortestPath." << std::endl;
            return "-1";
        }
    size_t n = g.getNumVertices();
    std::vector<int> prev(n, -1);
    std::vector<int> dist(n, INF);
    BellmanFord(g, start, prev, dist);
      for (size_t u = 0; u < n; ++u) {
        for (size_t v = 0; v < n; ++v) {
            if (g.adjMat[u][v] != 0 && dist[v] > dist[u] + g.adjMat[u][v]) {
                g.hasNegativeCycle = true;
                //std::cout << "Found Negative Cycle" << std::endl;
                std::vector<size_t> negativeCycle;
                size_t current = u;
                while(std::find(negativeCycle.begin(), negativeCycle.end(), current) == negativeCycle.end()){
                    negativeCycle.push_back(current);
                    current = (size_t)prev[current];
                }
                std::reverse(negativeCycle.begin(), negativeCycle.end());
                std::string cycleString = std::to_string(current);
                for(size_t i = 0; i < negativeCycle.size() - 1; ++i){
                    cycleString += "->" + std::to_string(negativeCycle[i]);
                }
                g.setCycle(cycleString);
                return "-1";
            }
        }
        }
    if (dist[end] != INF) {
        return printPath(prev, start, end);
        
    } else {
        return "-1"; // No shortestPath
    }
}

/*
    BellmanFord:
    Applies the Bellman-Ford algorithm to find the shortest paths from a specified start vertex to all other vertices in the graph.
    @param Graph& g: Reference to the graph object.
    @param size_t start: Index of the starting vertex.
    @param std::vector<int>& prev: Reference to a vector to store the previous vertex in the shortest path.
    @param std::vector<int>& dist: Reference to a vector to store the shortest distance from the start vertex.
    @return void
*/
void Algorithms::BellmanFord(Graph& g, size_t start, std::vector<int>& prev, std::vector<int>& dist) {
    size_t V = g.getNumVertices();
    dist[start] = 0;
    // Relax edges repeatedly
    for (size_t i = 0; i < V - 1; ++i) {
        for (size_t u = 0; u < V; ++u) {
            for (size_t v = 0; v < V; ++v) {
                if (g.adjMat[u][v] != 0) {
                    Relax(u, v, g.adjMat[u][v], prev, dist);
                }
            }
        }
    
    }
}

/*
    Relax:
    Updates the distance and previous vertex information if a shorter path is found from vertex u to vertex v.
    @param size_t u: Index of the source vertex.
    @param size_t v: Index of the destination vertex.
    @param int w: Weight of the edge from u to v.
    @param std::vector<int>& prev: Reference to a vector storing previous vertex information.
    @param std::vector<int>& dist: Reference to a vector storing distance information.
    @return void
*/
void Algorithms::Relax(size_t u, size_t v, int w, std::vector<int>& prev, std::vector<int>& dist) {
    if (dist[u] != INF && (dist[v] > dist[u] + w)) {
        dist[v] = dist[u] + w;
        prev[v] = u;
    }
}

/*
    printPath:
    Constructs and returns a string representing the shortest path from the start vertex to the end vertex using the information stored in the previous vertex vector.
    @param std::vector<int>& prev: Reference to a vector storing previous vertex information.
    @param size_t start: Index of the starting vertex.
    @param size_t end: Index of the end vertex.
    @return std::string: String representing the shortest path or "-1" if no path exists.
*/
std::string Algorithms::printPath(std::vector<int>& prev,  size_t start, size_t end) {
    std::string path;
    if (prev[end] == -1) {
        return "-1"; // No path found
    }
    
    std::vector<int> vec;
    size_t i = end;
    while(i != start){
        vec.push_back(i);
        i = static_cast<size_t>(prev[i]);
    }
    vec.push_back(i);

    
    for(size_t j = vec.size() - 1; j > 0; j--){
        path += std::to_string(vec[j]) + "->";
    }
    path += std::to_string(vec[0]); // Add the start vertex at the end

    return path;
}

/*
    isContainsCycle:
    Checks if the graph contains a cycle using Depth-First Search (DFS).
    @param Graph& g: Reference to the graph object.
    @return std::string: String indicating the presence of cycles or absence if none.
*/
std::string Algorithms::isContainsCycle(Graph& g){
    if(g.hasNegativeEdges){
        if(g.hasNegativeCycle){
            return g.getCycle();
        } else {
            negativeCycle(g);
        }
    }
        bool ans = false;
        if (g.getEdges() == 0)
            return "No cycles";
        size_t n = (size_t)g.getNumVertices();
          if (n == 0) {
        std::cerr << "Error: Graph has no vertices." << std::endl;
        return "";
        }
        std::vector<int> color(n, WHITE);
        std::vector<int> path(n, -1);
        for (size_t i = 0; i < n; i++)
        {
            ans = DFSCycle(g, color, path, i);
            if (ans)
                break;
        }
        if (!ans)
            std::cout << "No cycles" << std::endl;
        return g.getCycle();
    }

/*
    DFSCycle:
    Performs Depth-First Search (DFS) to detect cycles in the graph.
    @param Graph& g: Reference to the graph object.
    @param std::vector<int>& color: Reference to a vector to mark the color of vertices during DFS.
    @param std::vector<int>& path: Reference to a vector to store the path information.
    @param size_t v: Index of the current vertex in DFS.
    @return bool: Boolean indicating whether a cycle is found or not.
*/
bool Algorithms::DFSCycle(Graph& g, std::vector<int>& color, std::vector<int>& path, size_t v) {
     for (size_t i = 0; i < g.adjMat[v].size(); i++)
            {
                if (g.adjMat[v][i])
                {
                    if (color[i] == WHITE)
                    {
                        color[i] = GRAY;
                        path[i] = v;
                        return DFSCycle(g, color, path, i);
                    }
                    else if (color[i] == GRAY)
                        g.setCycle(getCycles(path, i, v));
                    return true;
                }
            }
            return false;
}

/*
    getCycle:
    Constructs and returns a string representing the cycle found in the graph using the information stored in the path vector.
    @param std::vector<int>& path: Reference to a vector storing the path information.
    @param size_t start: Index of the starting vertex of the cycle.
    @param size_t end: Index of the ending vertex of the cycle.
    @return std::string: String representing the cycle in the graph.
*/
std::string Algorithms::getCycles(std::vector<int>& path, size_t start, size_t end) {
    std::string ans;
    ans += std::to_string(end) + "->";
    std::vector<int> cyclePath;
    size_t i = end;
    cyclePath.push_back(i);
    while (i != start) {
        i = static_cast<size_t>(path[i]);
        cyclePath.push_back(i);
    }
    for (size_t j = cyclePath.size() - 1; j > 0; --j) {
        ans += std::to_string(cyclePath[j]) + "->";
    }
    ans += std::to_string(cyclePath[0]);
    return ans;
}

/*
    isBipartite:
    Checks if the graph is bipartite using BFS and two sets to assign different colors to vertices.
    @param Graph& g: Reference to the graph object.
    @return std::string: String indicating whether the graph is bipartite or not.
*/
std::string Algorithms::isBipartite(Graph& g) {
    // coverting adjMat to adjList
    size_t n = g.adjMat.size();
      if (n == 0) {
        std::cerr << "Error: Graph has no vertices." << std::endl;
        return "";
    }
    std::vector<std::vector<int>> edges(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (g.adjMat[i][j] != 0) {
                edges[i].push_back(j);
            }
        }
    }

    std::vector<int> visited(g.getNumVertices(), -1); 
    bool res = true;
    std::unordered_set<int> setA, setB; // Sets to store nodes in different colors

    for (size_t i = 0; i < g.getNumVertices(); ++i) {
        if (visited[i] == -1) {
            if (!bipartite(g, edges, i, visited, setA, setB)) {
                res = false;
                break;
            }
        }
    }

    std::string result;
    if (res) {
        result += "The graph is bipartite: A={";
        bool firstA = true;
        for (auto elem : setA) {
            if (!firstA) {
                result += ", ";
            }
            result += std::to_string(elem);
            firstA = false;
        }
        result += "}, B={";
        bool firstB = true;
        for (auto elem : setB) {
            if (!firstB) {
                result += ", ";
            }
            result += std::to_string(elem);
            firstB = false;
        }
        result += "}";
    } else {
        result += "Not bipartite";
    }
    return result;
    
}

/*
    bipartite:
    Implements the bipartite checking logic using BFS and two sets to assign different colors to vertices.
    @param Graph& g: Reference to the graph object.
    @param std::vector<std::vector<int>>& edges: Reference to the adjacency list representation of the graph.
    @param int start: Index of the starting vertex for BFS.
    @param std::vector<int>& visited: Reference to a vector to mark visited vertices.
    @param std::unordered_set<int>& setA: Reference to the set representing vertices with one color.
    @param std::unordered_set<int>& setB: Reference to the set representing vertices with another color.
    @return bool: Boolean indicating whether the graph is bipartite or not.
*/
bool Algorithms::bipartite(Graph& g, std::vector<std::vector<int>>& edges, int start, std::vector<int>& visited, std::unordered_set<int>& setA, std::unordered_set<int>& setB) {
  std::queue<int> q;
  q.push(start);

  visited[(size_t)start] = 1;
  setA.insert(start); // Add starting node to set A

  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    for (int elem : edges[(size_t)curr]) {
      if (visited[(size_t)elem] == visited[(size_t)curr]) {
        return false;
      }
      if (visited[(size_t)elem] == -1) {
        visited[(size_t)elem] = 1 - visited[(size_t)curr];
        if (visited[(size_t)elem] == 1) {
          setA.insert(elem); // Add to set A if assigned color 1
        } else {
          setB.insert(elem); // Add to set B if assigned color 0
        }
        q.push(elem);
      }
    }
  }
  return true;
}

/*
    negativeCycle:
    Checks if the graph contains a negative cycle using the Bellman-Ford algorithm.
    @param Graph& g: Reference to the graph object.
    @return int: 1 if a negative cycle is found, 0 otherwise.
*/
int Algorithms::negativeCycle(Graph& g) {
      if (g.getNumVertices() == 0) {
        std::cerr << "Error: Graph has no vertices." << std::endl;
        return 0;
    }
    if(g.hasNegativeEdges){
        if(g.hasNegativeCycle){
                return 1;
        } else {
            size_t n = g.getNumVertices();
            std::vector<int> prev(n, -1);
            std::vector<int> dist(n, INF);
            BellmanFord(g, 0, prev, dist);
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (g.adjMat[u][v] != 0 && dist[v] > dist[u] + g.adjMat[u][v]) {
                        g.hasNegativeCycle = true;
                        //std::cout << "Found Negative Cycle" << std::endl;
                        std::vector<size_t> negativeCycle;
                        size_t current = u;
                        while(std::find(negativeCycle.begin(), negativeCycle.end(), current) == negativeCycle.end()){
                            negativeCycle.push_back(current);
                            current = (size_t)prev[current];
                        }
                        std::reverse(negativeCycle.begin(), negativeCycle.end());
                        std::string cycleString = std::to_string(current);
                        for(size_t i = 0; i < negativeCycle.size() - 1; ++i){
                            cycleString += "->" + std::to_string(negativeCycle[i]);
                        }
                        g.setCycle(cycleString);
                        return 1;
                        }
                    }
                }
        }
            } else {
                return 0;
    }
    return 0;
    }
} // namespace ariel
