#include "useraccount.hpp"

// WRITE YOUR CODE HERE

UserAccount::UserAccount(std::string name) {
    username_ = name;
}

void UserAccount::Deposit(std::string asset, int amount) {
    portfolio_[asset] += amount;
}

bool UserAccount::Withdrawal(std::string asset, int amount) {
    // portfolio_[asset] += amount;
    if (portfolio_[asset] >= amount) {
        portfolio_[asset] -= amount;
        return true;
    }
    else {
        return false;
    }
}

bool UserAccount::AddOrder(Order order) {
    if (order.side == "Sell") {
        if (portfolio_[order.asset] < order.amount) {
            return false;
        }
        else {
            portfolio_[order.asset] -= order.amount;
        }
    }
    else if (order.side == "Buy") {
        int total_cost = order.amount * order.price;
        if (portfolio_["USD"] < total_cost) {
            return false;
        }
        else {
            portfolio_["USD"] -= total_cost;
        }
    }

    open_orders_.push_back(order);
    return true;
}

void UserAccount::PerformBuy(Order buy_order, Trade trade) {
    portfolio_[trade.asset] += trade.amount;
}

void UserAccount::PerformSell(Order sell_order, Trade trade) {
    portfolio_["USD"] += trade.amount * trade.price;
}

std::map<std::string, int> UserAccount::GetPortfolio() const {
  return portfolio_;
}

std::vector<Order> UserAccount::GetOpenOrders() {
    return open_orders_;
}

void UserAccount::PrintOrders(std::ostream &os) {
    for (const auto &order : open_orders_) {
        os << order << "\n";
    }
}