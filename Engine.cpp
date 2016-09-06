#include "Engine.h"
#include "EngineInput.h"
#include "Utility"

#include <memory>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;
using std::unique_ptr;

// string constants: error messages
const char* const unauthorized_error_g = "UNAUTHORIZED";
const char* const unknown_order_error_g = "UNKNOWN_ORDER";

// Initialize the static variable used for setting order_id's
int Post::next_order = 0;

/* Compare two posts:
     First by commodity
     Next by dealer
     Last by price
*/
bool operator<(const Post& l, const Post& r)
{
  // First order by commodity.
  int comp = l.commodity.compare(r.commodity);
  if (comp < 0) return true;
  if (comp > 0) return false;

  // Same commodity, next order by dealer.
  comp = l.dealer.compare(r.dealer);
  if (comp < 0) return true;
  if (comp > 0) return false;

  // Same commodity and dealer, next order by price.
  if (l.price < r.price) return true;

  // Right hand price is greater or equal to left hand price, so return false.
  return false;
}


// Add a Post to the Engine
// POST_COMMAND = “POST” SIDE COMMODITY AMOUNT PRICE
// Note that the "POST" has already been stripped from the stringstream
void Engine::add_command(unique_ptr<Message>&& message_ptr)
{

}

// Remove a Post from the Engine
void Engine::revoke_command(unique_ptr<Message>&& message_ptr)
{}
// Check on the status of an order
void Engine::check_command(unique_ptr<Message>&& message_ptr)
{}
// List all posts or filter by commodity and dealer 
void Engine::list_command(unique_ptr<Message>&& message_ptr)
{}
// Aggress on a list of orders
void Engine::aggress_command(unique_ptr<Message>&& message_ptr)
{}



