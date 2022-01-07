#include <string>
using namespace std;

// ORDER
class Order {
 public:
  Order(string orderInputStr, int arrivalTime);

  Order(int arrivalTime, string id, string type, string marketType, bool isDivisible, int quantity, float targetPrice = -1);

  // Arrival time (represents ordered ID) (represented with integer (typically the counter variable))
  int arrivalTime;

  // Order ID
  string id;

  // Order Type ("B" (buying) or "S" (selling))
  string type;

  // Market Type ("M" (Market) or "L" (limit))
  string marketType;

  // Divisibility
  bool isDivisible;

  // Target price (For limit orders only)
  float targetPrice = -1;

  // Quantity
  int quantity;

  // Pending Text (for printing to the console) e.g. "ord002 4.50     50"
  string pendingText();

  // Execution Text (for printing to the output file and execution alert)
  string executionText(float executionPrice, bool unexecuted = false);

  // Either write second cosntructor to create orders from parameters e.g. Order(int arrivalTime, string type,
  // float orice...)
};

// TRADE/MATCH
class Trade {
 public:
  Trade(Order& o1, Order& o2);

  // Order pair
  Order& buyOrder;
  Order& sellOrder;

  // Execution price
  float executionPrice;

  // Execution text (basically returning the execution text of the pair)
  string executionText();
};