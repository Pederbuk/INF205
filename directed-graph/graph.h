
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>


#include "query.h"

/*
 * Memory management rule for the classes below: 
 * It is the graph (Graph) object that has ownership over all its nodes and edges.
 * Nodes and edges just access non-owning pointers to each other; they never need to delete each other directly.
 */
namespace graph
{
   class Edge;  // needs to be declared before we can use it in class Node
   
   class Node
   {
   public:
      Node() {}  // default constructor
      Node(std::string in_label) { this->set_label(in_label); }
      
      std::string get_label() const { return this->label; }
      void set_label(std::string in_label) { this->label = in_label; }
      
      std::set<Edge*> get_incoming_edges() const { return this->incoming; }
      std::set<Edge*> get_outgoing_edges() const { return this->outgoing; }
      void append_incoming_edge(Edge* e) { this->incoming.insert(e); }
      void append_outgoing_edge(Edge* e) { this->outgoing.insert(e); }
      
      void detach_edge(Edge* e);  // remove an edge from the incidence list(s)
      
   private:
      std::string label = "";  // in this implementation, nodes have a string label, taken to be their unique name
      std::set<Edge*> incoming = std::set<Edge*>();
      std::set<Edge*> outgoing = std::set<Edge*>();
   };
   
   class Edge
   {
   public:
      Edge() {}  // default constructor
      Edge(Node* na, std::string in_label, Node* nb) {
         this->set_nodes(na, nb);
         this->set_label(in_label);
      }

      std::string get_label() const { return this->label; }
      void set_label(std::string in_label) { this->label = in_label; }
      
      std::string get_source_label() const { return this->source->get_label(); }
      std::string get_target_label() const { return this->target->get_label(); }
      void set_nodes(Node* na, Node* nb) {
         this->source = na;
         this->target = nb;
      }
      void detach_from_nodes() {
         if(source) this->source->detach_edge(this);
         if(target) this->target->detach_edge(this);
      }
      
      // write to *target
      void out(std::ostream* target) const {
         *target << "<" << this->get_source_label() << ">\t"
                 << "<" << this->label << ">\t<" << this->get_target_label() << ">\n";
      }
      
      // querying DFS helper method
      void conditional_dfs(Query* q, std::vector<std::string>::iterator q_rel_it, std::vector<std::string>* sol, std::string source_label, std::ostream* out);

   private:
      std::string label = "";  // the edge label is _not_ a unique identifier! (as opposed to node labels which are unique)
      Node* source = nullptr;  // edge connects *source to *target and vice versa
      Node* target = nullptr;  // if it was a directed graph, we might call them "source" and "target"
   };

   class Graph
   {
   public:
      Graph() {}
      
      // return pointer to the node with given label if it exists, nullptr otherwise
      Node* find_node(std::string node_label) {
         auto iter = this->nodes.find(node_label);
         if(iter == this->nodes.end()) return nullptr;
         else return &(iter->second);
      }

      void create_edge(std::string source_label, std::string edge_label, std::string target_label);
      
      // create new node with given label, if non-existing
      void create_node(std::string node_label) {
         if(!this->find_node(node_label)) this->nodes[node_label] =  Node(node_label);
      }
      
      // erases any existing edges from node labelled source_label to node labelled target_label
      // returns true if such an edge existed, false otherwise
      bool erase_edge(std::string source_label, std::string target_label);
      
      // erases the node labelled source_label, if it exists
      // returns true if such a node existed, false otherwise
      bool erase_node(std::string node_label);
      
      // read from *source
      void in(std::istream* source) {
         while(this->generate_edge_from(source)) {}  // read edge by edge, until generate_edge_from returns false
      }
      // write to *target
      void out(std::ostream* target) const {
         for(auto iter = this->edges.begin(); iter != this->edges.end(); iter++)
            (*iter)->out(target);  // output edge by edge
         *target << "<>\n";  // format: empty label for end of content
      }
      
      // destructor:
      // deallocate objects subject to manual memory management that are owned by this object
      ~Graph();
      
      // copy constructor:
      // needed for "deep copy" of owned properties subject to manual memory management
      Graph(const Graph& original);
      
      // overloaded copy assignment operator:
      // similar to the copy constructor, but used in case where this object is already constructed
      Graph& operator=(const Graph& right_hand_side);
      
      // move constructor:
      // "this" is getting constructed while at the same time "old" is deallocated
      Graph(Graph&& old);
      
      // overloaded move assignment operator:
      // used for an assignment where "this" already exists and "old" is a rhs term to be deallocated
      Graph& operator=(Graph&& old);
      
      // apply query, write to out
      void query(Query* q, std::ostream* out);
      // checks two queries by edges
      void check_two_queries_by_edges(Query* q, Query* p, std::ostream* out);
      
      void check_two_queries_by_nodes(Query* q, Query* p, std::ostream* out);
      
   private:
      // for this implementation, node labels are unique, and we identify nodes through their labels
      // hence it makes sense to use an STL map with the label as the key and the node as the value
      std::map<std::string, Node> nodes = std::map<std::string, Node>();
      
      // one possible solution: edges on the heap, owned by the graph object, accessed through a set of pointers
      std::set<Edge*> edges = std::set<Edge*>();
      
      bool generate_edge_from(std::istream* source);  // create a single edge based on information from the stream
      void consistent_edge_deallocation(Edge* e);  // helper function for deallocating edges
   };
}

/*
 * I/O stream operator overloading for Graph
 */
std::istream& operator>>(std::istream& is, graph::Graph& g);
std::ostream& operator<<(std::ostream& os, const graph::Graph& g);

/*
 * I/O stream operator overloading for Edge
 */
std::ostream& operator<<(std::ostream& os, const graph::Edge& e);

#endif
