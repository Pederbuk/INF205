#include "graph.h"
#include "query.h"

int read_query(std::string file_name, graph::Query paths[2])
{
   std::ifstream inquery(file_name);
   if (!inquery)
   {
      std::cerr << "Error! File " << file_name << " cannot be read.\n";
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

int read_graph(std::string file_name, graph::Graph* graph)
{
   std::ifstream indata(file_name);
   if(!indata)
   {
      std::cerr << "Error! File " << file_name << " cannot be read.\n";
      return EXIT_FAILURE;
   }
   graph::Graph g;
   indata >> g;
   *graph = g;
   indata.close();
   
   return 0;
}