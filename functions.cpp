#include "functions.h"

#include <iostream>
#include <map>
#include <optional>
#include <vector>

#include "classes.h"
using namespace std;

// ======================================================================================================= //
//    See 'functions.h' file (or hover over a function name) to see full descriptions of each function     //
// ======================================================================================================= //

// GET DATA

pair<float, map<int, Order>> getData(string filename) {
  float lastTradingPrice;
  map<int, Order> pendingOrders;
  int counter;

  // IMPLEMENT ME

  // The code below is just a guide, you can replace with anything else

  // Dummy input list (here, the names represent the IDs)
  string inputStrings[] = {
      "1100.00",       "alice B L D 1099.00 10", "carol S L I 1101.00 5", "dave B L D 1099.75 20",
      "bob B M D 100", "fred B L I 900.00 1",    "eve B L D 1099.75 100", "musk S M D 1000"};

  for (int i = 0; i < 8; i++) {  // Dummy loop (replace with the read line loop)

    // Initialize the last trading price
    if (i == 0) {
      lastTradingPrice = stoi(inputStrings[0]);
      continue;
    }
    counter++;
    Order newOrder(inputStrings[0], counter);
    pendingOrders[counter] = newOrder;
  }

  return make_pair(lastTradingPrice, pendingOrders);
}

// PRINT PENDING ORDERS

void printPendingOrders(map<int, Order> pendingOrders, map<int, Order>::iterator orderIterator) {
  // IMPLEMENT ME
}

// FIND MATCH FOR TARGET ORDER

pair<optional<Order>, optional<Order>> findMatch(map<int, Order> pendingOrders,
                                                 map<int, Order>::iterator orderIterator, int& counter) {
  optional<Order> matchedOrder = {};    // The found order
  optional<Order> remainderOrder = {};  // A new remainder order (if it matched with a divisible order)

  // IMPLEMEMT ME
  /**
   * use find_if to filter out all the invalid orders
   *  - remove all orders of the same type (where order.type == secondOrder.type)
   *  - For limit orders
   *    - If type is "S"
   *      - Remove all orders less than target price (except market orders (and if lastTransactionPrice >
   * limit price))
   *    - For buy orders
   *      - Remove all orders higher than target price
   *  - For market orders
   *    - If type is "S"
   *      - remove all orders with target price less than lastTransactionPrice
   *    - If type is "B"
   *      - remove all orders with target price higher than mlastTransactionPrice
   *
   *  - For divisible orders
   *      - remove all indivisible orders higher the quantity
   *  - For indivisible orders
   *      - remove all orders less than the quantity (divisible or not)
   *
   *  - (If they are both divisible they can trade (just remove the lower from the higher))
   *
   *  use min or max
   *  - If is buy order
   *    - return order wit lowest price
   *  - If is sell order
   *    - return order with highest price
   */
  // auto max = std::max_element( MySuperVector.begin(), MySuperVector.end(),
  //      []( const MyOwnClass &a, const MyOwnClass &b )
  //      {
  //     aPrice = (a.targetPrice != -1) ? a.targetPrice : lastTransactionPrice;
  //     bPrice = (b.targetPrice != -1) ? b.targetPrice : lastTransactionPrice;
  //          return aPrice < bPrice;
  //      } );
  // For minimum, just use ">"
  /**
   * Check worksheet for other prioties besides mix/min pricing e.g. if 2 items have the same price pick the
   * one with the lower arrivalTime
   *
   *
   * Once the min/max has been gotten
   *
   * Check for remainder
   *  - If o1.quantity < o2.quantity {
   *       counter++;
   *       remainder = new Order(... all the same data as the higher one except the quantity (original
   * quantity - order2 quantity) and arrivalTime (which is counter))
   *    }
   *    else if (o2.quantity > o1.quantity) {
   *       counter++;
   *       remainder = new Order(... all the same data as the higher one except the quantity (original
   * quantity - order2 quantity) and arrivalTime (which is counter))
   *    }
   *
   */

  /**
   * Don't use more than 2 loops/iterators (just for filtering and one for finding)
   */

  //
  // - Worksheet:
  // https://blackboard.le.ac.uk/bbcswebdav/pid-3216843-dt-content-rid-14924561_2/courses/CO3105_2021-22_SEM1/Asg/cw2b/cw2b.html
  // - Searching STL containers:
  // https://stackoverflow.com/questions/26766136/how-to-get-min-or-max-element-in-a-vector-of-objects-in-c-based-on-some-field
  //

  return make_pair(matchedOrder, remainderOrder);
}

// HANDLE MATCHING

Trade handleMatch(map<int, Order>& pendingOrders, map<int, Order>::iterator& targetOrderIterator,
                  Order foundOrder, float lastTradingPrice, optional<Order> remainder = {}) {
  // IMPLEMENT ME
}

// PRINT AND ADD THE EXECUTION MESSAGE

void printAndWriteExecution(Trade trade, string& output) {
  // IMPLEMENT ME

  // String can be gotten by calling trade.executionText()
}

// PRINT AND ADD THE NON EXECUTED MESSAGE

void printAndWriteNonExecution(map<int, Order> pendingOrders, string& output) {
  // IMPLEMENT ME

  // String can be gotten by calling Order.executionText(0.0, true)
}

// SEND OUTPUT

void sendOutput(string output) {
  // IMPLEMENT ME
}