#include <iostream>
#include <string>
#include <typeinfo>
#include <cassert>
#include <fstream>



#include "graph.h"
#include "query.h"
#include "read-input.h"
  
// test funcktion
void test(std::string sol){

   std::string real_sol = "Solution: 1 --> 6";
   if (sol == real_sol){
      std::cout<<"Passed \n";
   } else{
      std::cout<<"Failed \n";
   } 
   

}

int main(){
   graph::Query paths[2];
   graph::Graph g;
   
   std::string i = "1";
   std::string file_g = "data/eks1.dat";
   std::string file_q = "data/eks1_q.dat";
  
   read_graph(file_g, &g);
   read_query(file_q, paths);

   std::cout<<"Testing edges: \n";
   std::string sol = g.check_two_queries_by_edges(&paths[0],&paths[1],&std::cout);
   test(sol);

   std::cout<<"Testing edges Parallel: \n";
   std::string sol2 = g.check_two_queries_by_edges_para(&paths[0],&paths[1],&std::cout);
   test(sol2);

   std::cout<<"Testing nodes: \n";
   std::string sol3 = g.check_two_queries_by_nodes(&paths[0],&paths[1],&std::cout);
   test(sol3);

   std::cout<<"Testing nodes parallel\n";
   std::string sol4 = g.check_two_queries_by_nodes_para(&paths[0],&paths[1],&std::cout);
   test(sol4);



 



   return 0;





}