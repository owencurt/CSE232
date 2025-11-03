#include "useraccount.hpp"

// WRITE YOUR CODE HERE

UserAccount::UserAccount(std::string name) {
    username_ = name;
}

void UserAccount::Deposit(std::string asset, int amount) {
    portfolio_[asset] += amount;
}

bool UserAccount::Withdrawal(std::string asset, int amount) {
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

void UserAccount::PerformBuy(Order &buy_order, const Trade &trade) {
    for (auto it = open_orders_.begin(); it != open_orders_.end(); ++it) {
        if (it->username == buy_order.username &&
            it->asset == buy_order.asset &&
            it->side == buy_order.side &&
            it->price == buy_order.price) {

            it->amount -= trade.amount;

            if (it->amount <= 0) {
                open_orders_.erase(it);
            }
            break;
        }
    }

    portfolio_[trade.asset] += trade.amount;

    filled_orders_.push_back({buy_order.username, buy_order.side, trade.asset, trade.amount, trade.price});
}


void UserAccount::PerformSell(Order &sell_order, const Trade &trade) {
    for (auto it = open_orders_.begin(); it != open_orders_.end(); ++it) {
        if (it->username == sell_order.username &&
            it->asset == sell_order.asset &&
            it->side == sell_order.side &&
            it->price == sell_order.price) {

            it->amount -= trade.amount;
            if (it->amount <= 0) {
                open_orders_.erase(it);
            }
            break;
        }
    }

    portfolio_["USD"] += trade.amount * trade.price;

    filled_orders_.push_back({sell_order.username, sell_order.side, trade.asset, trade.amount, trade.price});
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

std::vector<Order> UserAccount::GetFilledOrders() const {
  return filled_orders_;
}

