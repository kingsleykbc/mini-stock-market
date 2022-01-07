#include <string>
using namespace std;

// ORDER
class Order {
 public:
  Order(string orderInputStr, int arrivalTime);

  // Arrival time (represented with integer (typically the counter variable))
  const int arrivalTime;

  // Order ID
  const string id;

  // Order Type ("B" (buying) or "S" (selling))
  const string type;

  // Market Type
  const string marketType;

  // Divisibility
  const bool isDivisible;

  // Target price (For limit orders only)
  const float targetPrice;

  // Quantity
  const int quantity;

  // Pending Text (for printing to the console) e.g. "ord002 4.50     50"
  string pendingText() const;

  // Execution Text (for printing to the output file and execution alert)
  string executionText(bool unexecuted = false) const;
};

// TRADE/MATCH
class Trade {
 public:
  Trade(const Order& bo, const Order& so);

  // Order pair
  const Order& buyOrder;
  const Order& sellOrder;

  // Execution price
  float executionPrice;

  // Execution text (basically returning the execution text of the pair)
  string executionText();
};