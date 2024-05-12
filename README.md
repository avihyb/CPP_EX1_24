# CPP EX1 - Graph and Algorithms

## Table of Contents
- [Graph](#graph)
- [Algorithms](#algorithms)
- [How to Use](#how-to-use)
- [More](#more)

## Graph
`Graph.cpp` implements a Graph class designed to handle graph structures. The loadGraph function initializes the graph based on a given matrix representation, stored as adjMat, checking properties like symmetry, directedness, and presence of negative edges. The printGraph function outputs essential details about the graph, such as the number of vertices and edges. Overall, this code provides a foundation for working with graph data structures, offering flexibility and functionality for graph analysis and manipulation.

## Algorithms
`Algorithms.cpp` offers a comprehensive set of graph algorithms and data structures. It includes functionalities for connectivity, shortest path finding, cycle detection, and bipartiteness checking. Each algorithm is thoroughly documented, providing developers with a versatile toolkit for graph analysis and manipulation.

## How to Use
1. **Include Header Files:** 
   ```cpp
   #include "Graph.hpp"
   #include "Algorithms.hpp"
   ```

2. **Namespace Usage:** 
   ```cpp
   using namespace ariel;
   ```

3. **Creating a Graph Object:** 
   ```cpp
   Graph g;
   ```

4. **Loading Graph Data:** 
   ```cpp
   vector<vector<int>> graph = {
       {0, 1, 0},
       {1, 0, 1},
       {0, 1, 0}};
   g.loadGraph(graph);
   ```

5. **Utilize Algorithms:** 
   ```cpp
   isConnected(g);
   shortestPath(g, 0, 2);
   isContainsCycle(g);
   isBipartite(g);
   ```

6. **Access Results:** 
   Use the returned values for further processing in your application.

## More
This project has undergone thorough analysis using Valgrind and Tidy to ensure high code quality and robustness. Valgrind was used for memory management analysis, detecting memory leaks, and identifying potential memory errors. Tidy was employed to enforce code formatting standards, enhancing readability, and maintaining consistency across the codebase. These tools contribute to the reliability and maintainability of the project, ensuring a smooth and efficient development process.




