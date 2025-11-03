#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utility.hpp"

class UserAccount {

// WRITE YOUR CODE HERE
  // Suggestions:
 public:
  UserAccount() = default;
  UserAccount(std::string name);
  void Deposit(std::string asset, int amount);
  bool Withdrawal(std::string asset, int amount);
  bool AddOrder(Order order);
  void PerformBuy(Order buy_order, Trade trade);
  void PerformSell(Order sell_order, Trade trade);
  std::map<std::string, int> GetPortfolio() const;
  std::vector<Order> GetOpenOrders();
  void PrintOrders(std::ostream &os);

  private:
  std::string username_;
  std::map<std::string, int> portfolio_;
  std::vector<Order> open_orders_;
};