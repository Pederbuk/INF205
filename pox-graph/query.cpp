/*
the graph and query code is gotten from a handout by Martin Thomas Horsch, 
the code is released under the CC BY-NC-SA 4.0 license
 */
 
#include "query.h"

using namespace graph;

std::istream& operator>>(std::istream& is, Query& q) {
   q.in(&is);
   return is;
}

// read an IRI with bracket notation; return false if \0 or empty token was read
bool graph::IRI_input(std::string* token, std::istream* source)
{
   char single_symbol = '\0';
   while(single_symbol != '<')
   {
      *source >> single_symbol;
      if(single_symbol == '\0') return false;  // format: \0 means that we are done
   }
   for(*source >> single_symbol; single_symbol != '>'; *source >> single_symbol)
      *token += single_symbol;
   
   return (*token != "");  // format: empty token means that we are done
}
 