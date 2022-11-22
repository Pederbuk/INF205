#include <typeinfo>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "graph.h"
#include "query.h"

int find_instances(char* file_query, graph::Graph g)
{
   std::ifstream inquery(file_query);
   if (!inquery)
   {
      std::cerr << "Error! File " << file_query << " cannot be read.\n";
      return EXIT_FAILURE;
   }
   graph::Query q;
   inquery >> q;

   std::string s = "";
   std::getline(inquery, s);

   graph::Query p;
   inquery >> p;
   inquery.close();

   g.check_two_queries_by_edges(&q, &p, &std::cout);

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

   find_instances(argv[2], g);
   return 0;
}
