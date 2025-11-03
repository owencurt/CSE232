#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "useraccount.hpp"
#include "utility.hpp"

class Exchange {
// WRITE YOUR CODE HERE
 public:
  void MakeDeposit(std::string username, std::string asset,
                   int amount);
  void PrintUserPortfolios(std::ostream &os);
  bool MakeWithdrawal(std::string username, std::string asset,
                      int amount);
  bool AddOrder(Order order);
  void PrintUsersOrders(std::ostream &os);
  void PrintTradeHistory(std::ostream &os);
  void PrintBidAskSpread(std::ostream &os);

  private:
    std::map<std::string, UserAccount> users_;
    std::vector<Order> open_orders_;
    std::vector<Trade> trade_history_;
};