#include "graph.h"
#include "query.h"


int read_query(std::string file_name, graph::Query paths[2])
{
   // Open file
   std::ifstream inquery(file_name);
   if (!inquery)
   {
      std::cerr << "Error! File " << file_name << " cannot be read.\n";
      return EXIT_FAILURE;
   }

   // Read the first query
   graph::Query q;
   inquery >> q;
   paths[1] = q;

   // Go to the next line
   std::string s = "";
   std::getline(inquery, s);

   // Read the second query
   graph::Query p;
   inquery >> p;
   paths[0] = p;
   inquery.close();

   return 0;
}


int read_graph(std::string file_name, graph::Graph* graph)
{
   // Open file
   std::ifstream indata(file_name);
   if(!indata)
   {
      std::cerr << "Error! File " << file_name << " cannot be read.\n";
      return EXIT_FAILURE;
   }

   // Read the graph
   graph::Graph g;
   indata >> g;
   *graph = g;
   indata.close();
   
   return 0;
}