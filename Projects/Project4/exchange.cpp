#include "exchange.hpp"

void Exchange::MakeDeposit(std::string username, std::string asset, int amount) {
    if (users_.find(username) == users_.end()) {
        users_.emplace(username, UserAccount(username));
    }

    users_[username].Deposit(asset, amount);
}

void Exchange::PrintUserPortfolios(std::ostream &os) {
  for (auto &[username, account] : users_) {
    os << username << ":\n";

    auto portfolio = account.GetPortfolio();
    for (auto &[asset, amount] : portfolio) {
      if (amount > 0) {
        os << "  " << asset << ": " << amount << "\n";
      }
    }
  }
}

bool Exchange::MakeWithdrawal(std::string username, std::string asset, int amount) {
  auto it = users_.find(username);
  if (it == users_.end()) {
    return false;
  }

  return (*it).second.Withdrawal(asset, amount);
}

bool Exchange::AddOrder(Order order) {
  if (users_.find(order.username) == users_.end()) {
    users_.emplace(order.username, UserAccount(order.username));
  }

  if (!users_[order.username].AddOrder(order)) {
    return false;
  }

  std::vector<Order> updated_open_orders;

  for (auto &existing : open_orders_) {
    if (existing.asset != order.asset || existing.username == order.username) {
      updated_open_orders.push_back(existing);
      continue;
    }

    if (order.side == "Buy" && existing.side == "Sell" &&
        existing.price <= order.price) {
      int traded = std::min(order.amount, existing.amount);
      Trade t{order.username, existing.username, order.asset, traded, order.price};
      trade_history_.push_back(t);

      users_[order.username].PerformBuy(order, t);
      users_[existing.username].PerformSell(existing, t);

      order.amount -= traded;
      existing.amount -= traded;
    }

    else if (order.side == "Sell" && existing.side == "Buy" &&
             existing.price >= order.price) {
      int traded = std::min(order.amount, existing.amount);
      Trade t{existing.username, order.username, order.asset, traded, order.price};
      trade_history_.push_back(t);

      users_[existing.username].PerformBuy(existing, t);
      users_[order.username].PerformSell(order, t);

      order.amount -= traded;
      existing.amount -= traded;
    }

    if (existing.amount > 0) {
      updated_open_orders.push_back(existing);
    }
    if (order.amount == 0) {
      break;
    }
  }

  open_orders_ = updated_open_orders;

  if (order.amount > 0) {
    open_orders_.push_back(order);
  }

  return true;
}

void Exchange::PrintUsersOrders(std::ostream &os) {
  for (auto &[username, account] : users_) {
    os << username << ":\n";
    account.PrintOrders(os);
  }
}

void Exchange::PrintTradeHistory(std::ostream &os) {
  for (const auto &t : trade_history_) {
    os << t.buyer_username << " bought "
       << t.amount << " " << t.asset
       << " from " << t.seller_username
       << " for " << t.price << " USD\n";
  }
}

void Exchange::PrintBidAskSpread(std::ostream &os) {
  std::map<std::string, std::pair<int, int>> spread;

  for (const auto &order : open_orders_) {
    auto &pair = spread[order.asset];

    if (order.side == "Buy") {
      pair.first = std::max(pair.first, order.price);
    } else if (order.side == "Sell") {
      if (pair.second == 0)
        pair.second = order.price;
      else
        pair.second = std::min(pair.second, order.price);
    }
  }

  for (const auto &[asset, prices] : spread) {
    os << asset << " Bid: " << prices.first
       << " Ask: " << prices.second << "\n";
  }
}