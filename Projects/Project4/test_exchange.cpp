#include <iostream>
#include <sstream>
#include "exchange.hpp"
#include "useraccount.hpp"
#include "utility.hpp"

int main() {
    Exchange e;

    // The exact setup from the grader test
    e.MakeDeposit("Nahum", "BTC", 10);
    e.MakeDeposit("Nahum", "USD", 8500);
    e.MakeDeposit("Dolson", "USD", 600);
    e.MakeDeposit("Nahum", "USD", 500);
    e.MakeDeposit("Dolson", "ETH", 60);
    e.MakeDeposit("Nahum", "ETH", 4);
    e.MakeDeposit("Ofria", "BTC", 100);
    e.MakeDeposit("Dolson", "ETH", 10);  // total ETH = 70

    std::ostringstream oss;
    e.PrintUserPortfolios(oss);

    std::cout << "=== Your PrintUserPortfolios output ===\n";
    std::cout << oss.str() << "\n";

    std::string expected =
        "User Portfolios (in alphabetical order):\n"
        "Dolson's Portfolio: 70 ETH, 600 USD, \n"
        "Nahum's Portfolio: 10 BTC, 4 ETH, 9000 USD, \n"
        "Ofria's Portfolio: 100 BTC, \n";

    if (oss.str() == expected)
        std::cout << "✅ PASS: Output matches expected string!\n";
    else
        std::cout << "❌ FAIL: Output differs from expected.\n";
}