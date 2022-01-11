#pragma once

#include <string>
using namespace std;

// ORDER
class Order {
 public:
  // Initialized form input string
  Order(string orderInputStr, float arrivalTime);

  // Initialized from values
  Order(float aT, string orderID, string t, string mT, bool div, int qty, float price);

  // Null object
  Order();

  // Null order (Because C++ doesn't allow NULL objects and std::optional only works for version 17+)
  bool isNull = false;

  // Arrival time (represents ordered ID) (represented with integer (typically the counter variable))
  float arrivalTime;

  // Order ID
  string id;

  // Order Type ("B" (buying) or "S" (selling))
  string type;

  // Market Type ("M" (Market) or "L" (limit))
  string marketType;

  // Divisibility
  bool isDivisible;

  // Target price (For limit orders only. -1 means it is uninitialized)
  float targetPrice = -1;

  // Quantity
  int quantity;

  // Pending Text (for printing to the console) e.g. "ord002 4.50     50"
  string pendingText();

  // Execution Text (for printing to the output file and execution alert)
  string executionText(float executionPrice, bool unexecuted = false);
};

// TRADE/MATCH
class Trade {
 public:
  Trade(Order o1, Order o2, float lastTradingPrice);

  // Order pair
  Order buyOrder;
  Order sellOrder;

  // Execution price
  float executionPrice;

  // Execution text (basically returning the execution text of the pair)
  string executionText();
};

// HELPER FUNCTION
string formatPrice(float num);