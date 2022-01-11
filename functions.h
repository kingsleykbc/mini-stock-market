#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "classes.h"

using namespace std;

/**
 * @brief Read file and return data.
 *
 * This function retrieves the contents of the input files and parses them to the Order list.
 *
 * @param filename The input file name (gotten from the CMD argument)
 * @return pair<float, map<float, Order>>
 */
pair<float, map<float, Order>> getData(string filename);

/**
 * @brief Print pending orders
 * This function prints the Orders in the pendingList starting from position 0 to the position of the
 * current order. Output string gotten by calling Order.pendingText().
 *
 * @param pendingOrders - List of pending orders
 * @param arrivalTime - The arrival time of the current order
 * @param lastTradingPrice - The last trading price
 */
void printPendingOrders(map<float, Order> pendingOrders, float arrivalTime, float lastTradingPrice);

/**
 * @brief Print all pending orders (Used for debugging only)
 *
 * @param pendingOrders - List of pending orders
 */
void printPendingOrdersDebug(map<float, Order> pendingOrders);

/**
 * @brief Find Match for target order
 *
 * This function searches the map from position 0 to the position of the iterator and tries to match it to
 * orders (based on the worksheet conditions).
 *
 * If a match is found, it is returned in the first part of the pair. If the match would require creating a
 * new order i.e. at least one of the orders is divisible (and they satisfy other conditions), then that Order
 * is created and returned in the second part of the pair.
 *
 * @param pendingOrders - List of pending orders
 * @param arrivalTime - The arrival time of the current order
 * @return pair<Order, Order> Matched order (if any) and remainder order (if any)
 */
pair<Order, Order> findMatch(map<float, Order>& pendingOrders, float arrivalTime, float lastTradingPrice);

/**
 * @brief Print the execution message
 *
 * This function prints the execution message to the console, and also adds the message to the output
 * file "executions.txt"
 *
 * @param trade - Buying and Selling order pair
 * @param output - Reference to output string (to allow updating)
 */
void printAndWriteExecution(Trade trade, string& output);

/**
 * @brief Print the non executed orders
 *
 * This function prints and adds the remaining items in the pendingList as unexecuted.
 *
 * @param pendingOrders - Remaining pending orders
 * @param output - Reference to output string (to allow updating)
 */
void printAndWriteNonExecution(map<float, Order> pendingOrders, string& output);

/**
 * @brief Send output
 *
 * This function writes the output string to the "executions.txt" file and handles any formatting or
 * overwriting issues.
 *
 * @param output - Output string
 */
void sendOutput(string output);
