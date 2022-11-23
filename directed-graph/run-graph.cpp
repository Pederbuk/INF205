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

int main(int argc, char** argv)
{
   assert(argc >= 3);

   graph::Query paths[2];
   graph::Graph g;
   
   read_graph(argv, &g);
   read_query(argv, paths);

   // Get starting timepoint
   auto start = high_resolution_clock::now();

   // Call the function
   for (int i = 0; i < 1000; i++)
   {
      g.check_two_queries_by_nodes(&paths[0], &paths[1], &std::cout);
   }

   // Get ending timepoint
   auto stop = high_resolution_clock::now();

   // Print duration
   auto duration = duration_cast<milliseconds>(stop - start);
   std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl << "\n";
   
   return 0;
}