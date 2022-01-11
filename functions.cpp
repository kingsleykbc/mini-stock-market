#include "functions.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "classes.h"

using namespace std;

// =======================================================================================================
//    See 'functions.h' file (or hover over a function name) to see full descriptions of each function
// =======================================================================================================

// GET DATA

pair<float, map<float, Order>> getData(string filename) {
  ifstream file(filename);
  string line;

  float lastTradingPrice;
  map<float, Order> pendingOrders;
  int counter = 0;

  // Iterate through file
  while (getline(file, line)) {
    // Initialize the last trading price
    if (counter == 0) {
      lastTradingPrice = stof(line);
      counter++;
      continue;
    }

    // Add orders
    Order newOrder(line, counter);
    pendingOrders[counter] = newOrder;
    counter++;
  }

  return make_pair(lastTradingPrice, pendingOrders);
}

// PRINT PENDING ORDERS

void printPendingOrders(map<float, Order> pendingOrders, float arrivalTime, float lastTradingPrice) {
  // Print top heading
  if (arrivalTime == 1) {
    cout << "\n\n==================================================== START\n\n";
    cout << "Last trading price: " << formatPrice(lastTradingPrice) << "\n\n";
  }

  vector<string> buyOrders;
  vector<string> sellOrders;

  // Print heading
  cout << "Buy\t\t\t\tSell\t\t\n";
  cout << "----------------------------------------------------\n";

  // Print orders
  for (auto it = pendingOrders.begin(); it != ++pendingOrders.find(arrivalTime); ++it) {
    if (it->second.type == "B")
      buyOrders.push_back(it->second.pendingText());
    else
      sellOrders.push_back(it->second.pendingText());
  }
  int size = buyOrders.size() > sellOrders.size() ? buyOrders.size() : sellOrders.size();
  for (size_t i = 0; i < size; i++) {
    string b = i >= buyOrders.size() ? " \t\t" : buyOrders.at(i);
    string s = i >= sellOrders.size() ? "" : sellOrders.at(i);
    cout << b << "\t\t" << s << "\n";
  }
}

// PRINT ALL PENDING ORDERS (DEBUG ONLY)

void printPendingOrdersDebug(map<float, Order> pendingOrders) {
  for (auto& order : pendingOrders) {
    cout << order.first << " : " << order.second.pendingText() << endl;
  }
}

// FIND MATCH FOR TARGET ORDER

pair<Order, Order> findMatch(map<float, Order>& pendingOrders, float arrivalTime, float lastTradingPrice) {
  // Initialize both to null orders
  Order matchedOrder = Order();    // The found order
  Order remainderOrder = Order();  // A new remainder order (if it matched with a divisible order)
  Order target = pendingOrders.at(arrivalTime);

  // Filter out invalid orders
  for (auto it = pendingOrders.begin(); it != ++pendingOrders.find(arrivalTime); ++it) {
    Order o = it->second;

    // Skip orders of the same type
    if (target.type == o.type) continue;

    // Skip orders that are not within quantity range
    if (target.isDivisible) {
      if (!o.isDivisible && o.quantity > target.quantity) continue;
    } else {
      if (o.quantity < target.quantity) continue;
    }

    // Skip orders that are not within price range
    if (target.marketType == "L") {
      // Sellers and Buyers
      if (target.type == "S") {
        // If buyer is a limit order with price below limit
        if (o.marketType == "L" && (o.targetPrice < target.targetPrice)) continue;
      } else {
        // If seller is a limit order with price above limit
        if (o.marketType == "L" && (o.targetPrice > target.targetPrice)) continue;
      }
    }

    if (matchedOrder.isNull) {
      matchedOrder = o;
      continue;
    }

    // Select the best match, based on the orider priorities
    if (o.marketType == "M" && matchedOrder.marketType == "L") matchedOrder = o;

    // If both options have the same market type
    else if (!(o.marketType == "L" && matchedOrder.marketType == "M")) {
      if (o.targetPrice == matchedOrder.targetPrice) {
        if (o.arrivalTime < matchedOrder.arrivalTime) matchedOrder = o;
      } else {
        if ((target.type == "S" && o.targetPrice > matchedOrder.targetPrice) ||
            (target.type == "B" && o.targetPrice < matchedOrder.targetPrice))
          matchedOrder = o;
      }
    }
  }

  // Create remainder order (if any)
  if (!matchedOrder.isNull) {
    if (matchedOrder.quantity > target.quantity) {
      remainderOrder =
          Order(target.arrivalTime + 0.5, matchedOrder.id, matchedOrder.type, matchedOrder.marketType,
                matchedOrder.isDivisible, matchedOrder.quantity - target.quantity, matchedOrder.targetPrice);
      matchedOrder.quantity = target.quantity;
    } else if (target.quantity > matchedOrder.quantity) {
      remainderOrder = Order(target.arrivalTime + 0.5, target.id, target.type, target.marketType,
                             target.isDivisible, target.quantity - matchedOrder.quantity, target.targetPrice);
      target.quantity = matchedOrder.quantity;
    }
  }
  pendingOrders[arrivalTime] = target;
  return make_pair(matchedOrder, remainderOrder);
}

// PRINT AND ADD THE EXECUTION MESSAGE

void printAndWriteExecution(Trade trade, string& output) {
  string executionText = trade.executionText();
  cout << "\nTrade made!\n";
  cout << "----------------------------------------------------\n";
  cout << executionText;
  output += executionText;
}

// PRINT AND ADD THE NON EXECUTED MESSAGE

void printAndWriteNonExecution(map<float, Order> pendingOrders, string& output) {
  cout << "\nUnexecuted trades :(\n";
  cout << "----------------------------------------------------\n";
  string executionText = "";
  for (auto it = pendingOrders.begin(); it != pendingOrders.end(); ++it) {
    executionText = it->second.executionText(-1, true);
    cout << it->second.executionText(-1, true);
    output += executionText;
  }
  if (executionText == "") cout << "None, all orders were traded!...";
}

// SEND OUTPUT

void sendOutput(string output) {
  ofstream file("executions.txt");
  output = output.substr(0, output.size() - 1);
  file << output;
  file.close();

  cout << "\n\n==================================================== END\n\n";
}
