#ifndef ENGINEINPUT_H
#define ENGINEINPUT_H

#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

struct Message;

class EngineInput {
public:
  // Get dealer and command and put data into stringstream:
  std::unique_ptr<Message> parse_message();
  // Add a Post to the Engine
  std::unique_ptr<Message> add_command(std::unique_ptr<Message> message_ptr,
                                       std::stringstream& input_ss);
  // Remove a Post from the Engine
  std::unique_ptr<Message> revoke_command(std::unique_ptr<Message> message_ptr,
                                          std::stringstream& input_ss);
  // Check on the status of an order
  std::unique_ptr<Message> check_command(std::unique_ptr<Message> message_ptr,
                                         std::stringstream& input_ss);
  // List all posts or filter by commodity and dealer 
  std::unique_ptr<Message> list_command(std::unique_ptr<Message> message_ptr,
                                        std::stringstream& input_ss);
  // Aggress on a list of orders
  std::unique_ptr<Message> aggress_command(std::unique_ptr<Message> message_ptr,
                                           std::stringstream& input_ss);
  // Checks if we are done with input
  bool finished() { return end_of_input;}

  // alias for parsing function for each command
  using Parse_func = std::unique_ptr<Message> (EngineInput::*)
                        (std::unique_ptr<Message>, std::stringstream&);

private:
  std::string get_valid_dealer(std::stringstream& input_ss);
  std::string get_valid_side(std::stringstream& input_ss);
  std::string get_valid_commodity(std::stringstream& input_ss);
  double get_valid_price(std::stringstream& input_ss);
  int get_valid_int(std::stringstream& input_ss);
  // Map of valid commands to proper member function:
  static const std::unordered_map<std::string, Parse_func> parse_commands;

  // Boolean used to know if input is finished
  bool end_of_input{false};

};


#endif