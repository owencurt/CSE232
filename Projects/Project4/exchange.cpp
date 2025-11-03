#include "exchange.hpp"

void Exchange::MakeDeposit(std::string username, std::string asset, int amount) {
    if (users_.find(username) == users_.end()) {
        users_.emplace(username, UserAccount(username));
    }

    users_[username].Deposit(asset, amount);
}

void Exchange::PrintUserPortfolios(std::ostream &os) {
  os << "User Portfolios (in alphabetical order):\n";

  for (auto it = users_.begin(); it != users_.end(); ++it) {
    const std::string &username = it->first;
    const UserAccount &account = it->second;
    auto portfolio = account.GetPortfolio();

    os << username << "'s Portfolio: ";

    for (auto a = portfolio.begin(); a != portfolio.end(); ++a) {
      const std::string &asset = a->first;
      int amount = a->second;
      if (amount > 0) {
        os << amount << " " << asset << ", ";
      }
    }
    os << "\n";
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
  os << "Users Orders (in alphabetical order):\n";

  for (auto &pair : users_) {
    const std::string &username = pair.first;
    UserAccount &account = pair.second;

    os << username << "'s Open Orders (in chronological order):\n";
    auto open_orders = account.GetOpenOrders();
    for (auto &o : open_orders) {
      os << o.side << " " << o.amount << " " << o.asset
         << " at " << o.price << " USD by " << o.username << "\n";
    }

    os << username << "'s Filled Orders (in chronological order):\n";
    auto filled_orders = account.GetFilledOrders();
    for (auto &o : filled_orders) {
      os << o.side << " " << o.amount << " " << o.asset
         << " at " << o.price << " USD by " << o.username << "\n";
    }
  }
}


void Exchange::PrintTradeHistory(std::ostream &os) {
  os << "Trade History (in chronological order):\n";

  for (const auto &t : trade_history_) {
    os << t.buyer_username << " Bought "
       << t.amount << " of " << t.asset
       << " From " << t.seller_username
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