#include <iostream>
#include <sstream>
#include "exchange.hpp"
#include "useraccount.hpp"
#include "utility.hpp"

int main() {
    Exchange e;
    std::ostringstream oss;

    // --- Setup deposits ---
    e.MakeDeposit("Nahum", "BTC", 10);
    e.MakeDeposit("Dolson", "USD", 5555);

    // --- Nahum sells 5 BTC for 100 USD each ---
    e.AddOrder({"Nahum", "Sell", "BTC", 5, 100});

    // --- Dolson buys 5 BTC at 100 USD each ---
    e.AddOrder({"Dolson", "Buy", "BTC", 5, 100});

    // --- Check portfolio results ---
    oss.str("");
    e.PrintUserPortfolios(oss);
    std::cout << "=== User Portfolios ===\n" << oss.str();

    std::string expected_portfolio =
        "User Portfolios (in alphabetical order):\n"
        "Dolson's Portfolio: 5 BTC, 5055 USD, \n"
        "Nahum's Portfolio: 5 BTC, 500 USD, \n";

    if (oss.str() == expected_portfolio)
        std::cout << "✅ Portfolios match expected!\n";
    else {
        std::cout << "❌ Portfolios differ!\nExpected:\n"
                  << expected_portfolio
                  << "Got:\n" << oss.str() << "\n";
    }

    // --- Check order history ---
    oss.str("");
    e.PrintUsersOrders(oss);
    std::cout << "\n=== Users Orders ===\n" << oss.str();

    std::string expected_orders =
        "Users Orders (in alphabetical order):\n"
        "Dolson's Open Orders (in chronological order):\n"
        "Dolson's Filled Orders (in chronological order):\n"
        "Buy 5 BTC at 100 USD by Dolson\n"
        "Nahum's Open Orders (in chronological order):\n"
        "Nahum's Filled Orders (in chronological order):\n"
        "Sell 5 BTC at 100 USD by Nahum\n";

    if (oss.str() == expected_orders)
        std::cout << "✅ Orders match expected!\n";
    else {
        std::cout << "❌ Orders differ!\nExpected:\n"
                  << expected_orders
                  << "Got:\n" << oss.str() << "\n";
    }

    return 0;
}
