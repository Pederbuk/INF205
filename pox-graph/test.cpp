#include <iostream>
#include <string>
#include <typeinfo>
#include <cassert>
#include <fstream>



#include "graph.h"
#include "query.h"
#include "read-input.h"
  
/*
test function for testing individual functions
*/ 
void test_sol(std::string sol, bool is_soution, int* tests_passed){
   if (is_soution){
      std::string real_sol = "Solution: 1 --> 6";
      if (sol == real_sol){
         std::cout<<"Passed \n";
         tests_passed++;
      } else{
         std::cout<<"Failed \n";
      } 
   }
   if (!is_soution){
      std::string real_sol = "";
      if (sol == real_sol){
         std::cout<<"Passed \n";
         tests_passed ++;
      } else{
         std::cout<<"Failed \n";
      }
   }
   

}
/*
Test function for the graph class
*/

void test(bool is_solution, std::string file_g, std::string file_q, int* tests_passed){
   graph::Query paths[2];
   graph::Graph g;
   read_graph(file_g, &g);
   read_query(file_q, paths);

   std::cout<<"Testing edges: \n";
   std::string sol = g.check_two_queries_by_edges(&paths[0],&paths[1],&std::cout);
   test_sol(sol, is_solution, tests_passed);

   std::cout<<"Testing edges Parallel: \n";
   std::string sol2 = g.check_two_queries_by_edges_para(&paths[0],&paths[1],&std::cout);
   test_sol(sol2, is_solution, tests_passed);

   std::cout<<"Testing nodes: \n";
   std::string sol3 = g.check_two_queries_by_nodes(&paths[0],&paths[1],&std::cout);
   test_sol(sol3, is_solution, tests_passed);

   std::cout<<"Testing nodes parallel\n";
   std::string sol4 = g.check_two_queries_by_nodes_para(&paths[0],&paths[1],&std::cout);
   test_sol(sol4, is_solution,tests_passed);

}

int main(){
   int tests_passed = 0;
  
   bool is_solution = true;
   std::string file_with_solution_g = "data/eks1.dat";
   std::string file_with_solution_q = "data/eks1_q.dat";

   test(is_solution, file_with_solution_g, file_with_solution_q, &tests_passed);

   is_solution = false;
   std::string file_with_no_solution_g = "data/eks3.dat";
   std::string file_with_no_solution_q = "data/eks3_q.dat";
 
   test(is_solution, file_with_no_solution_g, file_with_no_solution_q, &tests_passed);

   std::cout<<"Tests passed: "<<tests_passed<<"/8\n";

   return 0;

}
