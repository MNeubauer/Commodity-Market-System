#ifndef ENGINE_H
#define ENGINE_H

#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>


/* Describes a post order */
struct Post {
  std::string commodity;
  std::string dealer;
  double price;
  int order_id;
  int amount;
  bool buy;
  // defined in Engine.cpp
  static int next_order;
  // comparison used for ordering posts in a set
  friend bool operator<(const Post& l, const Post& r); 
};

struct Message;

/*
  The main component of the Commodity Market System
*/
class Engine {
public:
  // Add a Post to the Engine
  void add_command(std::unique_ptr<Message>&& message_ptr);
  // Remove a Post from the Engine
  void revoke_command(std::unique_ptr<Message>&& message_ptr);
  // Check on the status of an order
  void check_command(std::unique_ptr<Message>&& message_ptr);
  // List all posts or filter by commodity and dealer 
  void list_command(std::unique_ptr<Message>&& message_ptr);
  // Aggress on a list of orders
  void aggress_command(std::unique_ptr<Message>&& message_ptr);


private:
  // alias for the iterator stored in 'posts_by_id'
  using Post_Iterator = std::set<Post>::iterator;
  // hashtable to map an order_id to an iterator from the set of Posts below
  std::unordered_map<int,Post_Iterator> posts_by_id;
  // Set of posts, ordered according to commodity, dealer, and price
  std::set<Post> posts;
};


#endif