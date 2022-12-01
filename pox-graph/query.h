/*
most of the code here is from a handout by Martin Thomas Horst, 
the code is released under the CC BY-NC-SA 4.0 license
 */
#ifndef QUERY_H
#define QUERY_H

#include <iostream>
#include <vector>

namespace graph
{
   // read an IRI with bracket notation; return false if \0 or empty token was read
   bool IRI_input(std::string* token, std::istream* source);
   
   struct Query
   {
      // read from *source
      void in(std::istream* source) {
            std::string rel = "";
            while(graph::IRI_input(&rel, source)) {
               this->relations.push_back(rel);
               rel = "";
            }
      }
      
      std::vector<std::string> relations;
   };
}

std::istream& operator>>(std::istream& is, graph::Query& q);

#endif
