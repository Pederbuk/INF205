/* undirected incidence-list graph implementation 
the graph and query code is gotten from a handout by Martin Thomas Horsch, 
the code is released under the CC BY-NC-SA 4.0 license
 */
 

#include <cassert>
#include "graph.h"
#include <thread>
#include <omp.h>
#include <stdio.h>


using namespace graph;

// create a new edge in the graph
void Graph::create_edge(
   std::string source_label, std::string edge_label, std::string target_label
) {
   Node* na = this->find_node(source_label);
   if(!na)
   {
      this->create_node(source_label);
      na = this->find_node(source_label);
   }
   assert(na);
   
   Node* nb = this->find_node(target_label);
   if(!nb)
   {
      this->create_node(target_label);
      nb = this->find_node(target_label);
   }
   assert(nb);
   
   // edge object created, owned by this graph object, handled by manual memory management
   Edge* new_edge = new Edge(na, edge_label, nb);
   
   // now connect the nodes to the new edge
   na->append_outgoing_edge(&(*new_edge));
   nb->append_incoming_edge(&(*new_edge));
   
   // update graph object property
   this->edges.insert(std::move(new_edge));
}

// create a single edge based on information from the stream
// if it fails, return false, otherwise return true
bool Graph::generate_edge_from(std::istream* source)
{
   // read label of the first node
   std::string source_label = "";
   if(!IRI_input(&source_label, source)) return false;
   
   // read edge label
   std::string edge_label = "";
   if(!IRI_input(&edge_label, source)) return false;
   
   // read label of the second node
   std::string target_label = "";
   if(!IRI_input(&target_label, source)) return false;
   
   this->create_edge(source_label, edge_label, target_label);
   return true;
}

// destructor:
// deallocate objects subject to manual memory management that are owned by this object
// in this case, these are all the edges of the graph; pointers to these edges are stored in this->edges
Graph::~Graph()
{
   // debug output
   // std::clog << "\tlog output: calling Graph destructor\n\t\t(this == " << this << ")\n"; 
   
   // deallocate all the edges
   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++) delete *iter;
}
      
// copy constructor:
// needed for "deep copy" of owned properties subject to manual memory management
Graph::Graph(const Graph& original)
{
   /*
   std::clog << "\tlog output: calling Graph copy constructor\n\t\t(this == "
             << this << ", &original = " << &original << ")\n";  // debug output
    */
         
   for(auto iter = original.nodes.begin(); iter != original.nodes.end(); iter++)
      this->create_node(iter->first);
   for(auto iter = original.edges.begin(); iter != original.edges.end(); iter++)
   {
      this->create_edge((*iter)->get_source_label(), (*iter)->get_label(), (*iter)->get_target_label());
   }
}
      
// overloaded copy assignment operator:
// similar to the copy constructor, but used in case where this object is already constructed
// in our case this means that we need to dispose of the pre-existing edges, then deep-copy the new ones
Graph& Graph::operator=(const Graph& right_hand_side)
{
   /*
   std::clog << "\tlog output: calling Graph copy assignment operator\n\t\t(this == "
             << this << ", &right_hand_side = " << &right_hand_side << ")\n";  // debug output
    */

   // deallocate all the edges and clear the sets of edges and nodes
   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++) delete *iter;
   this->edges.clear();
   this->nodes.clear();
   
   // deep copy of right_hand_side content into this
   for(auto iter = right_hand_side.nodes.begin(); iter != right_hand_side.nodes.end(); iter++)
      this->create_node(iter->first);
   for(auto iter = right_hand_side.edges.begin(); iter != right_hand_side.edges.end(); iter++)
   {
      this->create_edge((*iter)->get_source_label(), (*iter)->get_label(), (*iter)->get_target_label());
   }
   return *this;
}

// move constructor:
// "this" is getting constructed while at the same time "old" is deallocated
// we don't need to delete all the old edges, just let "this" take them over
Graph::Graph(Graph&& old)
{
   /*
   std::clog << "\tlog output: calling Graph move constructor\n\t\t(this == "
             << this << ", &old = " << &old << ")\n";  // debug output
    */
             
   for(auto iter = old.nodes.begin(); iter != old.nodes.end(); iter++)
      this->create_node(iter->first);
   this->edges = old.edges;
   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++)
   {
      (*iter)->set_nodes(
         this->find_node((*iter)->get_source_label()),
         this->find_node((*iter)->get_target_label())
      );
   }
   old.edges.clear();
}

// overloaded move assignment operator:
// used for an assignment where "this" already exists and "old" is a rhs term to be deallocated
// compared to the move constructor, we first need to deallocate the pre-existing edges
Graph& Graph::operator=(Graph&& old)
{
   /*
   std::clog << "\tlog output: calling Graph move assignment operator\n\t\t(this == "
             << this << ", &old = " << &old << ")\n";  // debug output
    */

   // deallocate all the edges and clear the sets of edges and nodes
   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++) delete *iter;
   this->edges.clear();
   this->nodes.clear();
   
   for(auto iter = old.nodes.begin(); iter != old.nodes.end(); iter++)
      this->create_node(iter->first);
   this->edges = old.edges;
   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++)
   {
      (*iter)->set_nodes(
         this->find_node((*iter)->get_source_label()),
         this->find_node((*iter)->get_target_label())
      );
   }
   old.edges.clear();
   return *this;
}

/*
 * I/O stream operator overloading for Graph
 */
std::istream& operator>>(std::istream& is, Graph& g) {
   g.in(&is);
   return is;
}
std::ostream& operator<<(std::ostream& os, const Graph& g) {
   g.out(&os);
   return os;
}

/*
 * I/O stream operator overloading for Edge
 */
std::ostream& operator<<(std::ostream& os, const Edge& e) {
   e.out(&os);
   return os;
}

/*
 * erases any existing edges from node labelled source_label to node labelled target_label
 * returns true if such an edge existed, false otherwise
 */
bool Graph::erase_edge(std::string source_label, std::string target_label)
{
   Node* a = this->find_node(source_label);
   if(!a) return false;  // node a does not exist
   
   int edges_found = 0;
   auto a_incidence_list = a->get_outgoing_edges();  // note that this is a *copy* of a's incidence list!
   for(auto iter = a_incidence_list.begin(); iter != a_incidence_list.end(); iter++)
   {
      Edge* e = *iter;
      if(e->get_target_label() == target_label)
      {
         edges_found++;
         this->consistent_edge_deallocation(e);
      }
   }
   return (edges_found > 0);
}
      
/* 
 * erases the node labelled source_label, if it exists
 * returns true if such a node existed, false otherwise
 */
bool Graph::erase_node(std::string node_label)
{
   Node* n = this->find_node(node_label);
   if(!n) return false;  // node does not exist
   
   auto n_incidence_list = n->get_incoming_edges();  // note that this is a *copy* of a's incidence list!
   for(auto iter = n_incidence_list.begin(); iter != n_incidence_list.end(); iter++)
      this->consistent_edge_deallocation(*iter);
   n_incidence_list = n->get_outgoing_edges();  // note that this is a *copy* of a's incidence list!
   for(auto iter = n_incidence_list.begin(); iter != n_incidence_list.end(); iter++)
      this->consistent_edge_deallocation(*iter);
   
   this->nodes.erase(node_label);
   return true;
}

/*
 * helper function for deallocating edges
 */
void Graph::consistent_edge_deallocation(Edge* e)
{
   e->detach_from_nodes();
   this->edges.erase(e);
   delete e;
}

/*
 * remove an edge from the incidence list(s)
 */
void Node::detach_edge(Edge* e)
{
   for(auto iter = this->incoming.begin(); iter != this->incoming.end(); iter++)
      if(*iter == e)
      {
         this->incoming.erase(iter);
         break;
      }
   for(auto iter = this->outgoing.begin(); iter != this->outgoing.end(); iter++)
      if(*iter == e)
      {
         this->incoming.erase(iter);
         return;
      }
}

std::vector<std::string> Graph::query(Query *q, std::ostream *out)
{
   std::vector<std::string>::iterator q_rel_it = q->relations.begin();
   std::vector<std::string> solutions;

   for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++)
   {
      Edge* e = *iter;
      if(e->get_label() == *q_rel_it)
      {
         e->conditional_dfs_edge(q, q_rel_it, &solutions, e->get_source_label(), out);
      }
   }
   return solutions;
} 
// function for conditional dfs on nodes adds the solution just the end node
void Edge::conditional_dfs_node(Query* q, std::vector<std::string>::iterator rel_it, std::vector<std::string>* sol, std::string source_label, std::ostream* out)
{
   rel_it++;
   
   if(rel_it == q->relations.end())
   {
      // solution found!
      std::string solution = this->get_target_label();

      sol->push_back(solution);
     
   } 

   auto connections = this->target->get_outgoing_edges();
   for(auto step = connections.begin(); step != connections.end(); step++)
   {
      Edge* e = *step;
      if(e->get_label() == *rel_it)
      {
         e->conditional_dfs_node(q, rel_it, sol, source_label, out);
      }
   } 
   
}
// function for conditional dfs on edges adds the solution with both start and end node

void Edge::conditional_dfs_edge(Query* q, std::vector<std::string>::iterator rel_it, std::vector<std::string>* sol, std::string source_label, std::ostream* out)
{
   rel_it++;
   
   if(rel_it == q->relations.end())
   {
      // solution found!
      std::string solution = source_label + " --> " + this->get_target_label();

      sol->push_back(solution);
      
   } 
    
   auto connections = this->target->get_outgoing_edges();
   for(auto step = connections.begin(); step != connections.end(); step++)
   {
      Edge* e = *step;
      
      if(e->get_label() == *rel_it)
      {
         e->conditional_dfs_edge(q, rel_it, sol, source_label, out);
      }
   } 
   
}

/* --------------------- Query ---------------------
   Function that checks two queries by iterating through the edges of the graph
*/
std::string Graph::check_two_queries_by_edges(Query *q, Query *p, std::ostream *out)
{
   // Get instances of the two queries in the graph
   std::vector<std::string> q_sol = this->query(q, out);
   std::vector<std::string> p_sol = this->query(p, out);

   // Check if the two queries have the same solutions
   for (int i = 0; i != q_sol.size(); i++)
   {
      for (int j = 0; j != p_sol.size(); j++)
      {
         if (q_sol[i] == p_sol[j]) {
            return "Solution: " + q_sol[i];
         }
      }
   }

   // If no solution was found
   return "";
}


/* --------------------- Query --------------------- 
   Function that checks two queries by iterating through the edges of the graph in parallel
*/
std::string Graph::check_two_queries_by_edges_para(Query *q, Query *p, std::ostream *out)
{
   // Declare variables
   std::vector<std::string> q_sol;
   std::vector<std::string> p_sol;

   // Split the queries into two threads
   #pragma omp parallel sections num_threads(2)
   {
      #pragma omp section
      {
         // Get instances of q-query in the graph
         q_sol = this->query(q, out);
      }
      #pragma omp section
      {
         // Get instances of p-query in the graph
         p_sol = this->query(p, out);
      }
   }

   // Check if the two queries have the same solutions
   for (int i = 0; i != q_sol.size(); i++)
   {
      for (int j = 0; j != p_sol.size(); j++)
      {
         if (q_sol[i] == p_sol[j]) {
            return "Solution: " + q_sol[i];
         }
      }
   }

   // If no solution was found
   return "";
}


/* --------------------- Query --------------------- 
   Function that checks two queries by iterating through the nodes of the graph
*/
std::string Graph::check_two_queries_by_nodes(Query* q, Query* p, std::ostream* out){
   std::vector<std::string>::iterator q_rel_it = q->relations.begin();
   std::vector<std::string>::iterator p_rel_it = p->relations.begin();
   std::string solution = "";

   // Loops though the nodes
   for(auto iter = this->nodes.begin(); iter != this->nodes.end(); iter++){

      Node n = iter->second;
      std::set<Edge*> n_edges = n.get_outgoing_edges();
      std::vector<std::string> q_sol;
      std::vector<std::string> p_sol;

      // Loops though the edges of the node
      for(auto e_iter = n_edges.begin(); e_iter != n_edges.end(); e_iter ++){
         
         Edge* e = *e_iter;
         std::string e_label = e->get_label();
         
         // Checks if the edge is the first edge of the query
         if(e_label == *q_rel_it) {
            e->conditional_dfs_node(q, q_rel_it, &q_sol, n.get_label(), out);
         }else if(e_label == *p_rel_it) {
            e->conditional_dfs_node(p, p_rel_it, &p_sol, n.get_label(), out);  
         }
      }

      // Checks if the two queries have the same solutions
      for (int i = 0; i != q_sol.size(); i++)
      {
         for (int j = 0; j != p_sol.size(); j++){
            if (q_sol[i] == p_sol[j])
            {
               return "Solution: " + n.get_label() + " --> " + q_sol[i];
            }
         }
      }
   }

   return solution;
}


/* --------------------- Query --------------------- 
   Function that checks two queries by iterating through the nodes of the graph in parallel
*/
std::string Graph::check_two_queries_by_nodes_para(Query* q, Query* p, std::ostream* out){
   int sol_from = 0;
   int sol_to = 0;
   bool foundCondition = false;

   // Loops though the nodes in parallel
   #pragma omp parallel for
   for (int i = 0; i < this->nodes.size(); i++)
   {
      // Checks the foundCondition flag if a solution is found 
      if (!foundCondition) 
      {
         auto node_it = this-> nodes.begin();
         Node n = node_it->second;
         std::set<Edge *> n_edges = n.get_outgoing_edges();
         std::vector<std::string>::iterator q_rel_it = q->relations.begin();
         std::vector<std::string>::iterator p_rel_it = p->relations.begin();
         std::vector<std::string> q_sol;
         std::vector<std::string> p_sol;

         // Checks outgoing edges
         for (auto e_iter = n_edges.begin(); e_iter != n_edges.end(); e_iter++)
         {
            Edge *e = *e_iter;

            // Checks if the edge is the first edge of the query
            if (e->get_label() == *q_rel_it) {
               e->conditional_dfs_node(q, q_rel_it, &q_sol, n.get_label(), out);
            }
            else if (e->get_label() == *p_rel_it) {
               e->conditional_dfs_node(p, p_rel_it, &p_sol, n.get_label(), out);
            }
         }

         // Checks if the two queries have the same solutions
         for (int i = 0; i != q_sol.size(); i++)
         {
            for (int j = 0; j != p_sol.size(); j++)
            {
               if (q_sol[i] == p_sol[j])
               {
                  // Ensures that only one thread can write to the solution variables
                  #pragma omp critical
                  {
                     sol_from = stoi(n.get_label());
                     sol_to = stoi(q_sol[i]);
                     foundCondition = true;
                  }
               }
            }
         }

         // Increments the node iterator
         advance(node_it, i);
      }
   }
   if (foundCondition)
   {
      return "Solution: " + std::to_string(sol_from) + " --> " + std::to_string(sol_to);
   } else 
   {
      return "";
   }
   
}