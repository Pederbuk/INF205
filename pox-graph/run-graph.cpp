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
   // Create graph and queries
   graph::Query paths[2];
   graph::Graph g;
   
   // Path to the graph and query files
   std::string file_g = "data/eks1.dat";
   std::string file_q = "data/eks1_q.dat";

   // Read graph and query files
   read_graph(file_g, &g);
   read_query(file_q, paths);

   // Run the "edges" algorithm
   std::string result_1 = g.check_two_queries_by_edges(&paths[0], &paths[1], &std::cout);
   std::cout << "Edges: " << result_1 << '\n';

   // Run the "nodes" algorithm
   std::string result_2 = g.check_two_queries_by_nodes(&paths[0], &paths[1], &std::cout);
   std::cout << "Nodes: " << result_2 << '\n';

   // Run the "edges_para" algorithm
   std::string result_3 = g.check_two_queries_by_edges_para(&paths[0], &paths[1], &std::cout);
   std::cout << "Edges para: " << result_3 << '\n';

   // Run the "nodes_para" algorithm
   std::string result_4 = g.check_two_queries_by_nodes_para(&paths[0], &paths[1], &std::cout);
   std::cout << "Nodes para: " << result_4 << '\n';

   return 0;
}