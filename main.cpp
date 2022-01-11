#include <iostream>
#include <map>
#include <vector>

#include "classes.h"
#include "functions.h"
using namespace std;

int main(int argc, char* argv[]) {
  // Read input file and initialize the data
  pair<float, map<float, Order>> data = getData(argv[1]);

  float lastTradingPrice = data.first;
  map<float, Order> pendingOrders = data.second;
  int counter = pendingOrders.size() + 1;
  string output;

  // Loop through the list and execute matches
  for (map<float, Order>::iterator it = pendingOrders.begin(); it != pendingOrders.end();) {
    // Print pending orders
    printPendingOrders(pendingOrders, it->first, lastTradingPrice);

    // Find ma newly added order <FoundMatch?, Remainder?>
    pair<Order, Order> match = findMatch(pendingOrders, it->first, lastTradingPrice);

    // If match found
    if (!match.first.isNull) {
      Trade trade(pendingOrders[it->first], match.first, lastTradingPrice);
      printAndWriteExecution(trade, output);

      // Remove pair from list
      pendingOrders.erase(match.first.arrivalTime);
      it = pendingOrders.erase(it);

      // Add remainder (if any)
      if (!match.second.isNull) {
        pendingOrders.insert(make_pair(match.second.arrivalTime, match.second));

        // Update the iterator
        const auto d = distance(pendingOrders.begin(), it);
        it = pendingOrders.begin();
        advance(it, d);
        it++;
      }
    }

    cout << "\n\n==================================================== NEXT ORDER\n\n";
    if (match.first.isNull) it++;
  }

  // Add the unexecuted orders and return result
  printAndWriteNonExecution(pendingOrders, output);
  sendOutput(output);

  return 0;
}
