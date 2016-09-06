#include "EngineInput.h"
#include "Utility.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::char_traits;
using std::cin;
using std::string;
using std::stringstream;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;

// constant error messages
const char* const message_error_g = "INVALID_MESSAGE";

// private static variable
const unordered_map<string, EngineInput::Parse_func> EngineInput::parse_commands {
    {"POST_COMMAND", &EngineInput::add_command},
    {"REVOKE_COMMAND", &EngineInput::revoke_command},
    {"CHECK_COMMAND", &EngineInput::check_command},
    {"LIST_COMMAND", &EngineInput::list_command},
    {"AGGRESS_COMMAND", &EngineInput::aggress_command}
  };

// Get dealer and command and put data into stringstream:
unique_ptr<Message> EngineInput::parse_message()
{
  // Messages are separated by the newline character, 
  // and should be no longer than 255 characters long. 
  string input_str{};
  if(!getline(cin, input_str)) {
    end_of_input = true;
    return unique_ptr<Message>{};
  }
  
  if (input_str.size() > 225) {
    throw Error{message_error_g};
  }

  // Read into a string stream for easy parsing
  stringstream input_ss{input_str};
  // Create Message for message data storage
  unique_ptr<Message> message_ptr{new Message{}};
  
  // Determine dealer and throw if invalid
  message_ptr->dealer = get_valid_dealer(input_ss);

  // Determine command and call the proper Engine member function
  input_ss >> message_ptr->command;
  // If the command is not valid, throw
  auto parse_command_iter = parse_commands.find(message_ptr->command);
  if (parse_command_iter == parse_commands.end())
    throw Error{message_error_g};
  
  // Call the parser function for this command
  // Return the Message pointer that it passes back
  return (this->*parse_command_iter->second)(move(message_ptr), input_ss);
}

// Add a Post to the Engine
// POST_COMMAND = “POST” SIDE COMMODITY AMOUNT PRICE
unique_ptr<Message> EngineInput::add_command(unique_ptr<Message> message_ptr,
                                             stringstream& input_ss)
{
  message_ptr->side = get_valid_side(input_ss);
  message_ptr->commodity = get_valid_commodity(input_ss);
  message_ptr->amount = get_valid_int(input_ss);
  message_ptr->price = get_valid_price(input_ss);
  // check that there is no more data in the message
  if (input_ss.peek() != char_traits<char>::eof())
    throw Error{message_error_g};
  return message_ptr;
}

// Remove a Post from the Engine
// REVOKE_COMMAND = “REVOKE” ORDER_ID
unique_ptr<Message> EngineInput::revoke_command(unique_ptr<Message> message_ptr,
                                                stringstream& input_ss)
{
  message_ptr->order_id = get_valid_int(input_ss);
  // check that there is no more data in the message
  if (input_ss.peek() != char_traits<char>::eof())
    throw Error{message_error_g};
  return message_ptr;
}

// Check on the status of an order
// CHECK_COMMAND = “CHECK” ORDER_ID
unique_ptr<Message> EngineInput::check_command(unique_ptr<Message> message_ptr,
                                               stringstream& input_ss)
{
  message_ptr->order_id = get_valid_int(input_ss);
  // check that there is no more data in the message
  if (input_ss.peek() != char_traits<char>::eof())
    throw Error{message_error_g};
  return message_ptr;
}

// List all posts or filter by commodity and dealer
//LIST_COMMAND = “LIST” [ COMMODITY [ DEALER_ID ] ]
unique_ptr<Message> EngineInput::list_command(unique_ptr<Message> message_ptr,
                                              stringstream& input_ss)
{
  // First check for no optional arguments
  if (input_ss.peek() == char_traits<char>::eof())
    return message_ptr;
  // Optional argument 1: Commodity:
  message_ptr->commodity = get_valid_commodity(input_ss);
  if (input_ss.peek() == char_traits<char>::eof())
    return message_ptr;
  // Optional argument 2: Dealer
  message_ptr->dealer = get_valid_dealer(input_ss);
  
  // No there should be no more data in the message
  if (input_ss.peek() != char_traits<char>::eof())
    throw Error{message_error_g};
  
  return message_ptr;
}

// Aggress on a list of orders
// AGGRESS_COMMAND = “AGGRESS” ( ORDER_ID AMOUNT )+
unique_ptr<Message> EngineInput::aggress_command(unique_ptr<Message> message_ptr,
                                                 stringstream& input_ss)
{
  // Since there must be at least one pair of (ORDER_ID, AMOUNT), use a do/while loop
  do {
    // Get order and amount to aggress
    int order_id = get_valid_int(input_ss);
    int amount = get_valid_int(input_ss);
    message_ptr->aggress.push_back({order_id, amount});
    // If there is no more input, end the loop, 
    // otherwise, try to get another order to aggress
  } while (input_ss.peek() != char_traits<char>::eof());
  return message_ptr;
}




const unordered_set<string> dealer_set{"DB", "JPM", "UBS", "RBC", "BARX", 
                                      "MS", "CITI", "BOFA", "RBS", "HSBC"};
const char* const unknown_dealer_error_g = "UNKOWN_DEALER";
string EngineInput::get_valid_dealer(stringstream& input_ss)
{
  string dealer;
  input_ss >> dealer;
  if (dealer_set.count(dealer) == 0)
    throw Error{unknown_dealer_error_g};
  return dealer;
}

const unordered_set<string> side_set{"BUY", "SELL"};
string EngineInput::get_valid_side(stringstream& input_ss)
{
  string side;
  input_ss >> side;
  if (side_set.count(side) == 0)
    throw Error{message_error_g};
  return side;
}

const char* const unknown_commodity_error_g = "UNKNOWN_COMMODITY";
const unordered_set<string> commodity_set{"GOLD", "SILV", "PORK", "OIL", "RICE"};
string EngineInput::get_valid_commodity(stringstream& input_ss)
{
  string commodity;
  input_ss >> commodity;
  if (commodity_set.count(commodity) == 0)
    throw Error{unknown_commodity_error_g};
  return commodity;
}

double EngineInput::get_valid_price(stringstream& input_ss)
{
    double price;
    if (cin >> price)
        return price;
    throw Error{message_error_g};
}

int EngineInput::get_valid_int(stringstream& input_ss)
{
    int amount;
    if (cin >> amount)
        return amount;
    throw Error{message_error_g};
}

