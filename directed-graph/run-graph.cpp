#include <typeinfo>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "graph.h"
#include "query.h"

int find_instances(char* file_q, char* file_p, graph::Graph g)
{
   std::ifstream inquery_q(file_q);
   if (!inquery_q)
   {
      std::cerr << "Error! File " << file_q << " cannot be read.\n";
      return EXIT_FAILURE;
   }
   graph::Query q;
   inquery_q >> q;
   inquery_q.close();
   
   std::ifstream inquery_p(file_p);
   if(!inquery_p){
      std::cerr<<"Error! File" <<file_p <<"cannot be read.\n";
      return EXIT_FAILURE;
   }
   graph::Query p;
   inquery_p >> p;
   inquery_p.close();

   g.check_two_queries(&q, &p, &std::cout);
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

   find_instances(argv[2], argv[3], g);
}
