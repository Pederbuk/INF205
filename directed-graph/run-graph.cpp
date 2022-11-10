#include <typeinfo>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "graph.h"
#include "query.h"

int find_instances(char* file, graph::Graph g)
{
   std::ifstream inquery(file);
   if (!inquery)
   {
      std::cerr << "Error! File " << file << " cannot be read.\n";
      return EXIT_FAILURE;
   }
   graph::Query q;
   inquery >> q;
   inquery.close();

   g.query(&q, &std::cout); // apply query q to graph g
   return 0;
}

int main(int argc, char** argv)
{
   assert(argc >= 3);
   
   std::ifstream indata(argv[1]);
   if(!indata)
   {
      std::cerr << "Error! File " << argv[1] << " cannot be read.\n";
      return EXIT_FAILURE;
   }
   graph::Graph g;
   indata >> g;
   indata.close();
   // std::cout << "\nContent of graph g:\n" << g << "\n";

   std::cout << "\n Query 1: \n";
   find_instances(argv[2], g);

   std::cout << "\n Query 2: \n";
   find_instances(argv[3], g);
}
