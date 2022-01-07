#include "classes.h"

#include <cmath>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// ========================================================================================================================================
//    ORDER
// ========================================================================================================================================
/**
 * @brief Initialize the order.
 * This constructor takes a line of the order input string and initializes the data members.
 *
 * @param orderInputStr order input string e.g. "ord001 B L I 4.25 100"
 * @param arrivalTime Arrival time represented by int. (preferably the counter var from the loop)
 */
Order::Order(string orderInputStr, int arrivalTime) {
  // TODO: IMPLEMENT ME
}

/**
 * @brief Return the pending text string.
 * This function returns a string that matches the pending list string displayed on the console.
 *
 * @return Pending string. e.g. "ord002 4.50     50"
 */
string Order::pendingText() const {
  // TODO: IMPLEMENT ME
  return "--";
}

/**
 * @brief Return the execution text string.
 * This function returns a string that matches the specified executions.txt text.
 *
 * @param unexecuted if order is unexecuted (return unexecuted text if true e.g. "order ord002 100 shares
 * unexecuted")
 * @return Execution string. e.g. "order ord001 100 shares purchased at price 4.25"
 */
string Order::executionText(bool unexecuted) const {
  // TODO: IMPLEMENT ME
  return "--";
}

// ========================================================================================================================================
//    TRADE
// ========================================================================================================================================
// /**
//  * @brief Construct a new Trade object and initialized the order pair
//  *
//  * @param bo - Buy order
//  * @param so - Sell order
//  */
// Trade::Trade(const Order& bo, const Order& so) : buyOrder(bo), sellOrder(so) {}

// /**
//  * @brief Return execution string of the order pair, simply by returning the execution string of the
//  * trade pair.
//  *
//  * @return Execution string of the pair
//  */
// string Trade::executionText() { return buyOrder.executionText() + "\n" + sellOrder.executionText(); }