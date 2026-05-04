#include <iostream>
#include <string>

class Account;

class Transaction {
private:
    std::string _date;
    double _amount;
    bool _type;

public:
    Transaction() : _date(""), _amount(0), _type(false) {}

    Transaction(const std::string date, double amount, bool type) {
        _date = date;
        _amount = amount;
        _type = type;
    }

    Transaction(const Transaction& other) {
        _date = other._date;
        _amount = other._amount;
        _type = other._type;
    }

    friend std::ostream& operator<<(std::ostream& os, const Transaction& tr) {
        os << " [ " << tr._date << " ] "
            << (tr._type ? "CREDIT" : "DEBIT") << " --- "
            << "Amount: " << tr._amount;
        return os;
    }

    void print() const {
        std::cout << "[" << _date << "] "
            << (_type ? "deposit +" : "withdraw -")
            << _amount << " AZN" << std::endl;
    }
};

class Auditor {
public:
    void generateReport(Account& acc);

    void sendEmail(std::string msg) {
        std::cout << "E-mail sent: " << msg << std::endl;
    }
};


class Account {
private:
    std::string _owner;
    double _balance;
    std::string _accountNumber;
    Transaction _transactions[50];
    int _trCount = 0;

public: 
    Account() : _owner(""), _balance(0), _accountNumber("") {}
     
    Account(const std::string owner, const std::string accNo, double balance) {
        _owner = owner;
        _accountNumber = accNo;
        _balance = balance;
    }

    Account(const Account& other) {
        _owner = other._owner;
        _accountNumber = other._accountNumber;
        _balance = other._balance;
    }
     
    friend std::ostream& operator<<(std::ostream& os, const Account& acc) {
        os << " [ " << acc._accountNumber << " ] "
            << acc._owner << " -> "
            << "Balance: " << acc._balance;
        return os;
    }

    std::string getOwner() const { return _owner; }
    double getBalance() const { return _balance; }
    std::string getAccountNumber() const { return _accountNumber; }

    void deposit(double amount) {
        std::cout << "===== DEPOSIT =====" << std::endl;
        if (amount > 0) {
            _balance += amount; 
            if (_trCount < 50) {
                _transactions[_trCount] = Transaction("2026-05-04", amount, true); 
                _trCount++;
            }
            std::cout << "The operation was successful." << std::endl;
        }
        else {
            std::cout << "Please enter the correct value!" << std::endl;
        }
    }

    void withdraw(double amount) {
        std::cout << "===== WITHDRAW =====" << std::endl;
        if (_balance >= amount) {
            _balance -= amount;
            std::cout << "The operation was successful." << std::endl;
        }
        else {
            std::cout << "The operation was unsuccessful.Please check your balance." << std::endl;
        }
    }

    void transfer(Account& target, double amount) {
        if (_balance >= amount) {
            this->withdraw(amount);
            target.deposit(amount);
            std::cout << "The transfer was completed successfully." << std::endl;
        }
        else {
            std::cout << "ERROR: Insufficient balance for transfer!" << std::endl;
        }
    }

    friend std::istream& operator>>(std::istream& is, Account& acc) {
        std::cout << "Enter Owner Name: ";
        std::getline(is >> std::ws, acc._owner);
        std::cout << "Enter Account Number: ";
        is >> acc._accountNumber;
        std::cout << "Enter Initial Balance: ";
        is >> acc._balance;
        return is;
    }

    friend class Bank;
    friend void Auditor::generateReport(Account& acc);
};



class Bank {
public:
    void printAllAccounts(Account accounts[], int n) {
        for (int i = 0; i < n; i++)
            std::cout << accounts[i]._accountNumber << " - " << accounts[i]._balance << " AZN" << std::endl;
    }

    void applyInterest(Account& acc, double rate) {
        acc._balance += (acc._balance * rate / 100);
    }

    void printHistory(Account& acc) {
        std::cout << "\n=== " << acc._accountNumber << " EXECUTE HISTORY ===" << std::endl;
        for (int i = 0; i < acc._trCount; i++) acc._transactions[i].print();
        std::cout << "Total execute: " << acc._trCount << "\n================================" << std::endl;
    }

    double getTotalBalance(Account accounts[], int n) {
        double total = 0;
        for (int i = 0; i < n; ++i) total += accounts[i]._balance;
        return total;
    }

    Account* findRichest(Account accounts[], int n) {
        if (n == 0) return nullptr;
        Account* richest = &accounts[0];
        for (int i = 1; i < n; i++) {
            if (accounts[i]._balance > richest->_balance) richest = &accounts[i];
        }
        return richest;
    }
};

void Auditor::generateReport(Account& acc) {
    std::cout << "\n=== Audit Report ===" << std::endl;
    std::cout << "Account: " << acc._accountNumber << std::endl;
    std::cout << "Owner: " << acc._owner << std::endl;
    std::cout << "Balance: " << acc._balance << " AZN" << std::endl;
    std::cout << "Status: Active" << std::endl;
    std::cout << "=====================" << std::endl;
}

int main() {  
    Account account1("Mark", "ACC-1001", 550.5);
    Account account2("Colt", "ACC-1002", 2000.0);
    std::cout << account1 << std::endl;
    std::cout << account2 << std::endl; 

    std::cout << "\n---- Account1 ----" << std::endl;
    std::cout << "Enter the money: ";
    double money1; std::cin >> money1;
    account1.deposit(money1); std::cout << std::endl;
    std::cout << "---- Account2 ----" << std::endl;
    std::cout << "Enter the money: ";
    double money2; std::cin >> money2;
    account2.deposit(money2); std::cout << std::endl;

    std::cout << "\n---- Account1 ----" << std::endl;
    account1.withdraw(600); std::cout << std::endl;
    std::cout << "---- Account2 ----" << std::endl;
    account2.withdraw(600); std::cout << std::endl;

    account1.transfer(account2, 300);

    Transaction transaction1("03.05.2026", 200.0, false);
    Transaction transaction2("23.04.2026", 600.0, true); 
    std::cout << transaction1 << std::endl;
    std::cout << transaction2 << std::endl;

    Auditor auditor;
    auditor.generateReport(account1);

    Bank bank;
    bank.printHistory(account1);
    bank.printHistory(account2);

    Account myAcc;
    std::cout << "--- Create your account ---" << std::endl;
    std::cin >> myAcc;  

    std::cout << "\nAccount created successfully!" << std::endl;
    std::cout << myAcc << std::endl;

    return 0;
}