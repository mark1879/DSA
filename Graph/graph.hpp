#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <vector>

class Graph
{
public:
   virtual ~Graph() {}
   virtual size_t VetextCount() const = 0;
   virtual size_t EdgeCount() const = 0;
   virtual void BFS(size_t vertex, std::vector<size_t>& order) const = 0;
   virtual void DFS(size_t vertex, std::vector<size_t>& order) const = 0;
   virtual bool AddEdge(size_t vertex1, size_t vertex2) = 0;
   virtual bool RemoveEdge(size_t vertex1, size_t vertex2) = 0;
   virtual bool HasEdge(size_t vertex1, size_t vertex2) const = 0;
};

#endif