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
   // std::cout << algo << ": " << duration.count() << " milliseconds" << std::endl;

   return duration.count();
}


int main()
{
   graph::Query paths[2];
   graph::Graph g;
   
   std::string dir = "data/scale_nodes/";
   
   // Create file
   std::ofstream file;
   file.open("data/benchmark.csv");
   file << "nodes, edges\n";
   
   // Loop files
   for (int i = 1; i < 6; i++) {
      std::string file_g = dir + "b" + std::to_string(i) + "_g.dat";
      std::string file_q = dir + "b" + std::to_string(i) + "_q.dat";

      read_graph(file_g, &g);
      read_query(file_q, paths);
      

      int node_sum = 0;
      int edge_sum = 0;
      int runs = 0;

      for (int j = 0; j < 10; j++)
      {
         node_sum += time_it(g, paths, "nodes");
         edge_sum += time_it(g, paths, "edges");
         runs++;
      }

      file << node_sum/runs << ", " << edge_sum/runs << "\n";
      std::cout << node_sum / runs << ", " << edge_sum / runs << "\n";
   }

   return 0;
}