#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

// // round_to_cent takes a double and results a double
// // The value returned should be rounded to the nearest cent 
// // (and work for negative values too)
// CHECK(round_to_cent(12) == 12);
// CHECK(round_to_cent(12.34) == 12.34);
// CHECK(round_to_cent(12.34567) == 12.35); // Rounds up
// CHECK(round_to_cent(12.34456) == 12.34); // Rounds down
// CHECK(round_to_cent(-12.34567) == -12.35);
double round_to_cent(double input) {
    double scaled = input * 100;

    if (scaled >= 0) {
        scaled = static_cast<int>(scaled + .5);
    }
    else {
        scaled = static_cast<int>(scaled - .5);
    }

    return scaled / 100;
}


// // Balances in this program are represented as doubles (externally). 
// // The "deposit" function should take a reference to a double (the balance) 
// // and a double (the amount to be deposited). The function should modify 
// // the balance to reflect the deposit. The function should not return anything.
// double balance = 13.49;
// double amount = 23.10;
// deposit(balance, amount);
// CHECK(balance == 36.59);
// deposit(balance, 0.11);
// CHECK(balance == 36.70);
void deposit(double& balance, double amount_deposited) {
    balance += amount_deposited;
    balance = round_to_cent(balance);
}


// // The "withdraw" function should take a reference to a double 
// // (the balance) and a double (the amount to be withdrawn). 
// // The function should modify the balance to reflect the withdrawal 
// // (if there is a balance larger than the amount requested). 
// // The function should return a bool indicating if the withdraw succeeded 
// // (that the balance was reduced).
// double balance = 13.49;
// double amount = 23.10;
// bool result = withdraw(balance, amount);
// CHECK(!result, "Balance not high enough!");
// CHECK(balance == 13.49, "Balance shouldn't be unchanged");
// balance = 33.49;
// amount = 23.10;
// result = withdraw(balance, amount);
// CHECK(result, "Balance is high enough!");
// CHECK(balance == 10.39, "Balance should be unchanged");
bool withdraw(double& balance, double amount_withdrawn) {
    bool success{};

    if (amount_withdrawn > balance) {
        success = false;
    }
    else {
        balance -= amount_withdrawn;
        balance = round_to_cent(balance);
        success = true;
    }

    return success;
}


// // The "overdraft" function should take a reference to a double (the balance) 
// // and a double (the amount to be withdrawn). The function should modify 
// // the balance to reflect the withdrawal (regardless of if there is a 
// // balance larger than the amount requested). The function should not return anything. 
// // However, there is a $35 fee for performing an overdraft.
// double balance = 13.49;
// double amount = 23.10;
// overdraft(balance, amount);
// CHECK(balance == -44.61, "Balance reduced by withdraw and $35 fee");
// double balance2 = 133.45;
// double amount2 = 23.10;
// overdraft(balance2, amount2);
// CHECK(balance2 == 75.35, "Balance reduced by withdraw and $35 fee");
void overdraft(double& balance, double amount_withdrawn_uncapped) {
    balance = balance - amount_withdrawn_uncapped - 35;
    balance = round_to_cent(balance);
}


// // The "interest_for_month" function should take double (the balance) 
// // and a double (the apr). The function should return the interest 
// // generated on the balance for one month (one twelfth of the year). 
// // As we learned in Superman III and Office Space 
// // (https://filmschoolrejects.com/getting-rich-with-richard-pryors-banking-scheme-from-superman-iii-7811840a8a0/), 
// // the bank keeps fractions of a penny. So be sure to round down to the
// // nearest cent.
// double balance = 13.49;
// double apr = 12.0;
// double result = interest_for_month(balance, apr);
// CHECK(result, 0.13);
// balance = 133.45;
// apr = 7.8;
// result = interest_for_month(balance, apr);
// CHECK(result == 0.86);
// balance = 1.00;
// apr = 3;
// result = interest_for_month(balance, apr);
// CHECK(result == 0.00);
double interest_for_month(double& balance, double apr) {
    double interest{};
    interest = balance * (apr/100) / 12;
    interest = static_cast<int>(interest * 100) / 100.0;

    return interest;
}


// // The "string_date_to_int" function should take a string 
// // (representing an ISO 8601 date like "2015-11-30") and three 
// // references to ints for the year, month, and day. 
// // The function should not return anything, 
// // but instead assign the parts of the string into those three ints.
// std::string date = "2015-11-30";
// int year, month, day;
// string_date_to_ints(date, year, month, day);
// CHECK(year == 2015);
// CHECK(month == 11);
// CHECK(day == 30);
void string_date_to_ints(std::string date, int& year, int& month, int& day) {
    year = std::stoi(date.substr(0, 4));
    month = std::stoi(date.substr(5, 2));
    day = std::stoi(date.substr(8, 2));
}


// // The "number_of_first_of_months" function is used to help calculate interest. 
// // Interest is accrued on the first of the month. So it is important to know 
// // how many times interest has compounded between two dates. 
// // This function takes two strings (representing a earlier and later date) 
// // and returns the number of times interest will accrue.
// std::string date_early = "2015-05-03";
// std::string date_late = "2015-09-30";
// int result = number_of_first_of_months(date_early, date_late);
// CHECK(result == 4);
// date_early = "2022-10-21";
// date_late = "2022-11-02";
// result = number_of_first_of_months(date_early, date_late);
// CHECK(result == 1);
// date_early = "2022-09-21";
// date_late = "2022-11-01";
// result = number_of_first_of_months(date_early, date_late);
// CHECK(result == 2);
// date_early = "2015-11-03";
// date_late = "2019-03-30";
// result = number_of_first_of_months(date_early, date_late);
// CHECK(result == 40);
// date_early = "2015-11-03";
// date_late = "2015-11-30";
// result = number_of_first_of_months(date_early, date_late);
// CHECK(result == 0);
// date_early = "2015-11-01";
// date_late = "2015-11-01";
// result = number_of_first_of_months(date_early, date_late);
// CHECK(result == 0);
int number_of_first_of_months(std::string date_early, std::string date_late) {
    int year1, month1, day1;
    int year2, month2, day2;

    string_date_to_ints(date_early, year1, month1, day1);
    string_date_to_ints(date_late, year2, month2, day2);

    int months_between = (year2 - year1) * 12 + (month2 - month1);

    return months_between;
}


// // The "interest_earned" function is used to calculate interest. 
// // Interest is accrued on the first of the month.
// // This function has 4 parameters
// // a double (representing the account balance at the begin date),
// // a double (representing the apr (annual percentage rate)),
// // a string (representing a begin date),
// // a string (representing an end date).
// // The function should return a double indicating the amount of interest accrued. 
// // Note that interest compounds, meaning that interest earned in earlier months is 
// // added to the balance prior to earning interest on later months.  
// double balance = 100.00;
// double apr = 12.0;
// std::string date_early = "2015-05-03";
// std::string date_late = "2015-06-30";
// double result = interest_earned(balance, apr, date_early, date_late);
// CHECK(balance == 100.00);
// CHECK(result == 1.00);
// balance = 10.00;
// apr = 12.0;
// date_early = "2015-05-03";
// date_late = "2015-07-30";
// result = interest_earned(balance, apr, date_early, date_late);
// CHECK(result == 0.20);
// balance = 1000.00;
// apr = 12.0;
// date_early = "2015-05-03";
// date_late = "2015-12-30";
// result = interest_earned(balance, apr, date_early, date_late);
// CHECK(result == 72.12);
// balance = 3000.00;
// apr = 14.0;
// date_early = "2015-02-03";
// date_late = "2016-12-30";
// result = interest_earned(balance, apr, date_early, date_late);
// CHECK(result == 871.97);
// balance = 100.00;
// apr = 12.0;
// date_early = "2015-05-03";
// date_late = "2015-06-30";
// result = interest_earned(balance, apr, date_early, date_late);
// CHECK(balance == 100.00);
// CHECK(result == 1.00);
// balance = 10.00;
// apr = 12.0;
// date_early = "2015-05-03";
// date_late = "2015-07-30";
// result = interest_earned(balance, apr, date_early, date_late);
// CHECK(result == 0.20);
// balance = 1000.00;
// apr = 12.0;
// date_early = "2015-05-03";
// date_late = "2019-12-30";
// result = interest_earned(balance, apr, date_early, date_late);
// CHECK(result == 728.23);
double interest_earned(double balance, double apr, std::string date_begin, std::string date_end) {
    int months = number_of_first_of_months(date_begin, date_end);

    double total_interest{};
    double balance_temp = balance;

    for (int i = 0; i < months; i++) {
        double monthly_interest = interest_for_month(balance_temp, apr);
        total_interest += monthly_interest;
        balance_temp += monthly_interest;
        balance_temp = round_to_cent(balance_temp);
    }

    total_interest = round_to_cent(total_interest);

    return total_interest;
}



// // The "process_command" function is the last helper function you need to write. 
// // It processes a single command (as opposed to the "process_commands" that does many). 
// // This function has 4 parameters:
// // a string (representing a line to be processed),
// // a reference to a string (representing the date of the previous line (empty if this is the first time being called)),
// // a reference to a double (representing the previous balance),
// // a double (representing the apr).
// // The function should return a string (possible with multiple lines) 
// // indicating the work done to perform the instruction. 
// // It should also update the balance to reflect any changes. 
// // It should also update the previous_date to the current date of the line it is processing.
// std::string line = "2015-09-03 Deposit $100";
// std::string previous_date = "2015-09-02";
// double balance = 10.00;
// double apr = 12.0;
// std::string expected = "On 2015-09-03: Instructed to perform \"Deposit $100\"\nBalance: 110.00\n";
// std::cout << "Expected: " << std::endl << expected << std::endl;
// std::string result = process_command(line, previous_date, balance, apr);
// std::cout << "Result: " << std::endl << result << std::endl;
// CHECK(balance == 110.00);
// CHECK(previous_date == "2015-09-03");
// CHECK(result == expected);
std::string process_command(std::string line, std::string& previous_date, double& balance, double apr) {
    std::string date = line.substr(0, 10);
    std::string command_line = line.substr(11);
    size_t command_split = command_line.find(' ');
    std::string command = command_line.substr(0, command_split);
    std::string amount_str = command_line.substr(command_split + 2);
    double amount = std::stod(amount_str);

    std::string result = "On " + date + ": Instructed to perform \"" + command_line + "\"\n";

    if (!previous_date.empty() && previous_date != date) {
        int months = number_of_first_of_months(previous_date, date);
        if (months > 0) {
            double interest = 0.0;

            if (balance > 0) {
                interest = interest_earned(balance, apr, previous_date, date);
                balance += interest;
                balance = round_to_cent(balance);
            }

            std::ostringstream interest_str;
            interest_str << std::fixed << std::setprecision(2) << interest;

            result += "Since " + previous_date + ", interest has accrued " + std::to_string(months) + " times.\n";
            result += "$" + interest_str.str() + " interest has been earned.\n";
        }
    }


    if (command == "Deposit") {
        deposit(balance, amount);
    }
    else if (command == "Withdraw") {
        bool success = withdraw(balance, amount);
        if (!success) {
            overdraft(balance, amount);
            result += "Overdraft!\n";
        }
    }

    previous_date = date;

    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << balance;

    result += "Balance: " + out.str() + "\n";

    return result;
}


// // The "process_commands" function is the last function you need to write. 
// // Parameters: 
// // a string (representing a multiline to be processed),
// // a double (representing the apr).
// // The function should return a string (possibly with multiple lines) indicating the result of performing the operations.
// std::string input = 
// "2016-09-02 Deposit $500\n"
// "2016-09-02 Withdraw $23.54\n"
// "2016-09-04 Withdraw $58\n"
// "2016-11-02 Deposit $200\n"
// "2017-03-02 Withdraw $1000\n"
// "2019-11-02 Deposit $5000\n"
// "2020-11-02 Deposit $500\n";
// std::string result = process_commands(input, 7);
// std::string expected = "On 2016-09-02: Instructed to perform \"Deposit $500\"\nBalance: 500.00\nOn 2016-09-02: Instructed to perform \"Withdraw $23.54\"\nBalance: 476.46\nOn 2016-09-04: Instructed to perform \"Withdraw $58\"\nBalance: 418.46\nOn 2016-11-02: Instructed to perform \"Deposit $200\"\nSince 2016-09-04, interest has accrued 2 times.\n$4.89 interest has been earned.\nBalance: 623.35\nOn 2017-03-02: Instructed to perform \"Withdraw $1000\"\nSince 2016-11-02, interest has accrued 4 times.\n$14.65 interest has been earned.\nOverdraft!\nBalance: -397.00\nOn 2019-11-02: Instructed to perform \"Deposit $5000\"\nSince 2017-03-02, interest has accrued 32 times.\n$0.00 interest has been earned.\nBalance: 4603.00\nOn 2020-11-02: Instructed to perform \"Deposit $500\"\nSince 2019-11-02, interest has accrued 12 times.\n$332.69 interest has been earned.\nBalance: 5435.69\n";
// std::cout << "Expected:" << std::endl << expected << std::endl;
// std::cout << "Result:" << std::endl << result << std::endl;
// CHECK(result == expected);
std::string process_commands(std::string input, double apr) {
    std::stringstream ss(input);
    std::string line;
    std::string previous_date = "";
    double balance = 0.0;
    std::string result;

    while (std::getline(ss, line)) {
        if (line.empty()) continue;

        std::string line_result = process_command(line, previous_date, balance, apr);

        result += line_result;
    }

    return result;
}