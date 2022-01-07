#include <iostream>
#include <map>
#include <vector>

#include "classes.h"
#include "functions.h"
using namespace std;

int main(int argc, char* argv[]) {
  // Initialize state variables
  int counter = 0;
  int newOrdersStartPos;
  int lastTradingPrice;
  map<int, Order> pendingOrders;

  // Import and read files
  for (int i = 0; i < 10; i++) {  // Dummy loop (replace with the read line loop)
    
  }

  /**
   * TODO
   *
   * Loop through the lines of the input file and insert each line in pending orders.
   *  - Update counter
   *  - Create Order and add to pendingOrders
   *  - printPendingOrders()
   *    - Loop through the pending orders list and call cout << order.pendingString() (along with whatever
   *      formatting)
   *  - findMatch(Order order (the newly created order)):
   *    - Write a find_if, max, etc. lambda to return a match for [order] depending on order type
   *      - set the lambda based on the type.
   *        - e.g. if [order] is B.O, lambda = [](x..) {[order].price <= x.price() || x.isMarketOrder... &&
   *          type = opposite}
   *      - Make sure all conditions are met
   *    - If order is found ([found order])
   *      - run matchOrder(bO, sO)
   *         - Remove bO and sO from pendingOrders
   *         - If either of them is divisible
   *            - Add new order with the remainder to pendingOrders
   *            - If !newOrderStartPos (first time adding extra orders), set newOrderStartPos to the
   *              arrivalTime of the newly created remainder order.
   *         - Log their executionText and also add the text to the "executions.txt" output file
   *
   * Loop through the newly added sub orders
   *  - Start at pendingList[newOrderStartPos] to pendingList.end()
   *    - Do all of the above
   *      - (But in this loop, constantly update the iterator to it loops through any further created
   *        remainder inputs) (See example below on how to update map while iterating)
   *
   * Print the unexecuted Orders
   *  - Loop through the pendingList (which currently holds the unexecuted orders) and print
   * Order.executionString(unexecuted = true)
   *
   *
   * - https://stackoverflow.com/questions/8234779/how-to-remove-from-a-map-while-iterating-it
   * -
   * https://stackoverflow.com/questions/26766136/how-to-get-min-or-max-element-in-a-vector-of-objects-in-c-based-on-some-field
   *
   */

  // EXAMPLE OF HOW TO MODIFY/RESIZE MAP DURING ITERATION
  // map<int, string> myMap;
  // myMap[1] = "Apple";
  // myMap[2] = "Beach";
  // myMap[3] = "Cat";
  // myMap[4] = "Drink";

  // for (auto it = myMap.cbegin(); it != myMap.cend();) {
  //   if (it->first == 2) {
  //     it = myMap.erase(it);
  //     myMap[5] = "New";
  //   }
  //   cout << it->first << ": " << it->second << endl;
  //   ++it;
  // }

  return 0;
}
