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

auto time_it(auto g, auto paths, std::string algo, int runs)
{
   // Get starting timepoint
   auto start = high_resolution_clock::now();

   // Call the function
   for (int i = 0; i < runs; i++)
   {  
      if (algo == "nodes") {
         std::string result = g.check_two_queries_by_nodes(&paths[0], &paths[1], &std::cout);
      } 
      else if (algo == "nodes_para") {
         std::string result = g.check_two_queries_by_nodes_para(&paths[0], &paths[1], &std::cout);
      }
      else if (algo == "parallel") {
         std::string result = g.check_two_queries_parallel(&paths[0], &paths[1], &std::cout);
      }
      else {
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
   
   std::string dir = "data/solution/";
   
   // Create file
   std::ofstream file;
   file.open("data/benchmark.csv");
   file << "nodes,edges,parallel,nodes_para\n";
   
   // Loop files
   for (int i = 1; i < 11; i++) {
      std::string file_g = dir + "b" + std::to_string(i) + "_g.dat";
      std::string file_q = dir + "b" + std::to_string(i) + "_q.dat";

      read_graph(file_g, &g);
      read_query(file_q, paths);
      

      int node_sum = 0;
      int node_para_sum = 0;
      int para_sum = 0;
      int edge_sum = 0;
      int runs = 0;

      std::cout << "Running: " << file_g << "\n";

      for (int j = 0; j < 5; j++)
      {
         node_sum += time_it(g, paths, "nodes", 5);
         node_para_sum += time_it(g, paths, "nodes_para", 5);
         para_sum += time_it(g, paths, "parallel", 5);
         edge_sum += time_it(g, paths, "edges", 5);
         runs++;
      }

      file << node_sum / runs << "," << edge_sum / runs << "," << para_sum / runs << "," << node_para_sum / runs << "\n";

      std::string result = g.check_two_queries_by_edges(&paths[0], &paths[1], &std::cout);
      std::cout << result << "\n";
      }

   return 0;
}