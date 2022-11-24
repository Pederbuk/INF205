#include <typeinfo>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

#include "graph.h"
#include "query.h"
#include "read-input.h"
using namespace std::chrono;

auto time_it(auto g, auto paths, std::string algo)
{
   // Get starting timepoint
   auto start = high_resolution_clock::now();

   // Call the function
   for (int i = 0; i < 1000; i++)
   {  
      if (algo == "nodes") {
         std::string result = g.check_two_queries_by_nodes(&paths[0], &paths[1], &std::cout);
      } else {
         std::string result = g.check_two_queries_by_edges(&paths[0], &paths[1], &std::cout);
      }
   }

   // Get ending timepoint
   auto stop = high_resolution_clock::now();

   // Print duration
   auto duration = duration_cast<milliseconds>(stop - start);
   std::cout << algo << ": " << duration.count() << " milliseconds" << std::endl;

   return duration.count();
}


int main(int argc, char** argv)
{
   assert(argc >= 3);

   graph::Query paths[2];
   graph::Graph g;
   
   read_graph(argv, &g);
   read_query(argv, paths);
   
   // Write to file
   std::ofstream file;
   file.open("data/benchmark.csv");
   file << "nodes, edges\n";

   for (int i = 0; i < 10; i++)
   {
      auto n = time_it(g, paths, "nodes");
      auto e = time_it(g, paths, "edges");
      file << n << ", " << e << "\n";
   }

   return 0;
}