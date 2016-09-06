#include "Engine.h"
#include "EngineInput.h"
#include "Utility.h"

#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

using std::cin;
using std::cout;
using std::exception;
using std::endl;
using std::getline;
using std::move;
using std::string;
using std::stringstream;
using std::unique_ptr;
using std::unordered_map;


// alias for Engine function for each command
using Engine_func = void (Engine::*)(unique_ptr<Message>&&);
// Map of valid commands to proper member function:
const unordered_map<string, Engine_func> commands{
  {"POST_COMMAND", &Engine::add_command},
  {"REVOKE_COMMAND", &Engine::revoke_command},
  {"CHECK_COMMAND", &Engine::check_command},
  {"LIST_COMMAND", &Engine::list_command},
  {"AGGRESS_COMMAND", &Engine::aggress_command}
};
// function for printing errors (in case methodology changes)
void print_error(const char* const error_str);


int main()
{
  // Initialize the Engine
  Engine engine;
  EngineInput parser;

  while (!parser.finished()) {
    try {
      unique_ptr<Message> message_ptr = parser.parse_message();
      // The parser has already checked the input, no need to validate again
      auto command_iter = commands.find(message_ptr->command);
      // Call the proper function for the valid command
      (engine.*command_iter->second)(move(message_ptr));
      
    } catch (Error& error) {
      print_error(error.what());
    }
  }

  return 0;
}


void print_error(const char* const error_str)
{
  cout << error_str << endl;
  return;
}

