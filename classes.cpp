#include "classes.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

// ========================================================================================================================================
//    HELPER FUNCTIONS
// ========================================================================================================================================
string formatPrice(float num) {
  stringstream stream;
  stream << fixed << setprecision(2) << num;
  return stream.str();
}

// ========================================================================================================================================
//    ORDER
// ========================================================================================================================================
/**
 * @brief Initialize the order from input string.
 *
 * This constructor takes a line of the order input string and initializes the data members.
 *
 * @param orderInputStr order input string e.g. "ord001 B L I 4.25 100"
 * @param arrivalTime Arrival time represented by int. (preferably the counter var from the loop)
 */
Order::Order(string orderInputStr, float aT) {
  stringstream ss(orderInputStr);
  string item;
  int counter = 0;

  // INITIALIZE THE ORDER
  arrivalTime = aT;
  while (getline(ss, item, ' ')) {
    switch (counter) {
      case 0:
        id = item;
        break;
      case 1:
        type = item;
        break;
      case 2:
        marketType = item;
        break;
      case 3:
        isDivisible = (item == "I") ? false : true;
        break;
      case 4:
        if (marketType == "L")
          targetPrice = stof(item);
        else
          quantity = stoi(item);
        break;
      case 5:
        quantity = stoi(item);
    }
    counter++;
  }
}

/**
 * @brief Initialize the order from values.
 *
 * This constructor initializes an order with its values
 */
Order::Order(float aT, string orderID, string t, string mT, bool div, int qty, float price)
    : arrivalTime(aT),
      id(orderID),
      type(t),
      marketType(mT),
      isDivisible(div),
      targetPrice(price),
      quantity(qty) {}

/**
 * @brief Initialize a null order.
 */
Order::Order() : isNull(true) {}

/**
 * @brief Return the pending text string.
 * This function returns a string that matches the pending list string displayed on the console.
 *
 * @return Pending string. e.g. "ord002 4.50     50"
 */
string Order::pendingText() {
  string price = (targetPrice == -1) ? "M" : formatPrice(targetPrice);
  return id + "\t" + price + "\t" + to_string(quantity);
}

/**
 * @brief Return the execution text string.
 * This function returns a string that matches the specified executions.txt text.
 *
 * @param unexecuted if order is unexecuted (return unexecuted text if true e.g. "order ord002 100 shares
 * unexecuted")
 * @return Execution string. e.g. "order ord001 100 shares purchased at price 4.25"
 */
string Order::executionText(float executionPrice, bool unexecuted) {
  string action = type == "B" ? "purchased" : "sold";
  string status = unexecuted ? "unexecuted" : action + " at price " + formatPrice(executionPrice);
  return "order " + id + " " + to_string(quantity) + " shares " + status + "\n";
}

// ========================================================================================================================================
//    TRADE
// ========================================================================================================================================
/**
 * @brief Construct a new Trade object and initialized the order pair
 *
 * @param o1 - First order
 * @param o2 - Second order
 */
Trade::Trade(Order o1, Order o2, float lastTradingPrice) : buyOrder(o1), sellOrder(o2) {
  if (o2.type == "B") {
    buyOrder = o2;
    sellOrder = o1;
  }
  // Set the execution price
  if (buyOrder.marketType == "L" && sellOrder.marketType == "L") {
    float bTime = buyOrder.arrivalTime;
    float sTime = sellOrder.arrivalTime;
    if (bTime < sTime)
      executionPrice = buyOrder.targetPrice;
    else
      executionPrice = sellOrder.targetPrice;
  } else if (buyOrder.marketType == "M" && sellOrder.marketType == "L")
    executionPrice = sellOrder.targetPrice;
  else if (buyOrder.marketType == "L" && sellOrder.marketType == "M")
    executionPrice = buyOrder.targetPrice;
  else
    executionPrice = lastTradingPrice;
}

/**
 * @brief Return execution string of the order pair, simply by returning the execution string of the
 * trade pair.
 *
 * @return Execution string of the pair
 */
string Trade::executionText() {
  return buyOrder.executionText(executionPrice) + sellOrder.executionText(executionPrice);
}
