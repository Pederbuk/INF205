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
   if (algo == "nodes") {
      std::string result = g.check_two_queries_by_nodes(&paths[0], &paths[1], &std::cout);
   } 
   if (algo == "edges") {
      std::string result = g.check_two_queries_by_edges(&paths[0], &paths[1], &std::cout);
   }
   if (algo == "nodes_para") {
      std::string result = g.check_two_queries_by_nodes_para(&paths[0], &paths[1], &std::cout);
   }
   if (algo == "edges_para")
   {
      std::string result = g.check_two_queries_by_edges_para(&paths[0], &paths[1], &std::cout);
   }

   // Get ending timepoint
   auto stop = high_resolution_clock::now();

   // Print duration
   auto duration = duration_cast<nanoseconds>(stop - start);

   return duration.count();
}


int main()
{
   // Create graph and queries
   graph::Query paths[2];
   graph::Graph g;
   
   // Directory of the graph and queries
   std::string dir = "data/solution_mix/";
   
   // Create file to store the results
   std::ofstream file;
   file.open("data/benchmark.csv");
   file << "nodes,edges,edges_para,nodes_para\n";
   
   int solutions = 0;   // Number of graphs with solutions
   
   // Loop through all graphs
   for (int i = 1; i <= 1000; i++) {

      // Create file names
      std::string file_g = dir + "b" + std::to_string(i) + "_g.dat";
      std::string file_q = dir + "b" + std::to_string(i) + "_q.dat";

      // Read graph and query from file
      read_graph(file_g, &g);
      read_query(file_q, paths);
      
      // Variables to store the results
      int node_sum = 0;
      int edge_sum = 0;
      int node_para_sum = 0;
      int edges_para_sum = 0;
      int runs = 0;

      std::cout << "Running: " << file_g << "\n";

      // Run the algorithms 5 times
      for (int j = 0; j < 5; j++)
      {
         node_sum += time_it(g, paths, "nodes");
         edge_sum += time_it(g, paths, "edges");
         node_para_sum += time_it(g, paths, "nodes_para");
         edges_para_sum += time_it(g, paths, "edges_para");
         runs++;
      }

      // Append the results to file
      file << node_sum / runs << "," << edge_sum / runs << "," << edges_para_sum / runs << "," << node_para_sum / runs << "\n";

      // Check if the graph has a solution
      std::string result = g.check_two_queries_by_edges(&paths[0], &paths[1], &std::cout);
      if (result != "") {
         solutions++;
      }
      std::cout << "Solutions: " << solutions << "\n";
      }

   return 0;
}