#ifndef UTILITY_H
#define UTILITY_H

#include <exception>
#include <unordered_set>
#include <string>
#include <vector>


// Exception class for handling user input errors
class Error : public std::exception {
public:
  Error(const char* msg_) : msg(msg_) {}
  const char* what() const noexcept override { return msg; }
private:
  const char* const msg;
};

// Struct to pass message data
using Aggress_Pair = std::pair<int,int>;
struct Message {
  std::vector<Aggress_Pair> aggress;
  std::string dealer;
  std::string command;
  std::string side;
  std::string commodity;
  double price;
  int amount;
  int order_id;
  bool buy;
};

#endif