#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <vector>

class Graph
{
public:
   virtual ~Graph() {}
   virtual size_t VertexCount() const = 0;
   virtual size_t EdgeCount() const = 0;
   virtual bool BFS(size_t start, std::vector<size_t>& order) const = 0;
   virtual bool DFS(size_t start, std::vector<size_t>& order) const = 0;
   virtual bool AddEdge(size_t src, size_t dst) = 0;
   virtual bool RemoveEdge(size_t src, size_t dst) = 0;
   virtual bool HasEdge(size_t src, size_t dst) const = 0;
   virtual bool ShortestPath(size_t start, size_t end, std::vector<size_t>& path) const = 0;
};

#endif