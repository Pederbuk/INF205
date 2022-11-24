#include <typeinfo>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "graph.h"
#include "query.h"
#include "read-input.h"


int main()
{
   graph::Query paths[2];
   graph::Graph g;
   
   std::string file_g = "data/scale_nodes/b5_g.dat";
   std::string file_q = "data/scale_nodes/b5_q.dat";

   read_graph(file_g, &g);
   read_query(file_q, paths);

   std::string result_1 = g.check_two_queries_by_edges(&paths[0], &paths[1], &std::cout);
   std::cout << "Edges: " << result_1 << '\n';

   std::string result_2 = g.check_two_queries_by_nodes(&paths[0], &paths[1], &std::cout);
   std::cout << "Nodes: " << result_2 << '\n';
   return 0;
}