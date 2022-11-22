#include "graph.h"
#include "query.h"

int read_query(char **argv, graph::Query paths[2])
{
   std::ifstream inquery(argv[2]);
   if (!inquery)
   {
      std::cerr << "Error! File " << argv[2] << " cannot be read.\n";
      return EXIT_FAILURE;
   }
   graph::Query q;
   inquery >> q;
   paths[1] = q;


   std::string s = "";
   std::getline(inquery, s);

   graph::Query p;
   inquery >> p;
   paths[0] = p;
   inquery.close();

   return 0;
}

int read_graph(char **argv, graph::Graph* graph)
{
   std::ifstream indata(argv[1]);
   if(!indata)
   {
      std::cerr << "Error! File " << argv[1] << " cannot be read.\n";
      return EXIT_FAILURE;
   }
   graph::Graph g;
   indata >> g;
   *graph = g;
   indata.close();
   
   return 0;
}