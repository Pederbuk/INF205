#include <iostream>
#include "graph.h"
#include "query.h"
#include "read-input.h"
#include <string>



   
void test(std::string sol){

   std::string real_sol = "1 --> 6";
   if (sol == real_sol){
      std::cout<<"Passed";
   } else{
      std::cout<<"Failed";
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



   return 0;





}